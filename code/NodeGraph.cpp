#include "NodeGraph.h"

#include "Core/Log.h"
#include "Core/Jobs.h"
#include "Core/System.h"
#include "Core/Atomic.h"

#include "Main.h"
#include "BuiltinProps.h"
#include "BuiltinNodes.h"
#include "TaskMan.h"
#include "Workspace.h"
#include "GuiTextView.h"

#include "ImGui/ImGuiAll.h"

#include "External/sjson/sjson.h"
#include "Core/External/minicoro/minicoro.h"

enum class NodeGraphProgressEventType
{
    NodeResetIdle,
    NodeResetStranded,
    NodeExecuteBegin,
    NodeExecuteSuccess,
    NodeExecuteError,
    LinkComplete
};

struct NodeGraphProgressEvent
{
    NodeGraphProgressEventType type;
    union {
        NodeHandle nodeHandle;
        LinkHandle linkHandle;
    };
};

struct NodeGraphDep
{
    WksFileHandle fileHandle;
    uint32 count;
};

struct NodeGraph
{
    HandlePool<PinHandle, Pin> pinPool;
    HandlePool<NodeHandle, Node> nodePool;
    HandlePool<LinkHandle, Link> linkPool;
    HandlePool<PropertyHandle, Property> propPool;
    Allocator* alloc;
    NodeGraphEvents* events;
    Mutex progressEventsMutex;
    Array<NodeGraphProgressEvent> progressEventsQueue;
    PropertyHandle executePropHandle;
    Array<NodeGraphDep> childGraphs;
    WksFileHandle fileHandle;
    TskGraphHandle taskHandle;
    TskGraphHandle parentTaskHandle;
    TskEventHandle parentEventHandle;
    Blob errorString;
    PinData outputResult;
    PinData metaData;
    atomicUint32 stop;
    bool saveTaskFile;
};

struct NodeGraphTask
{
    NodeGraph* graph;
    const NodeHandle* nodes;
    bool* errorNodes;
    uint32 numNodes;
};

struct NodeGraphNodeTemplate
{
    NodeDesc desc;
    NodeImpl* impl;
};

struct NodeGraphPropertyTemplate
{
    PropertyDesc desc;
    PropertyImpl* impl;
};

struct NodeGraphContext
{
    Array<NodeGraphNodeTemplate> nodeTemplates;
    Array<NodeGraphPropertyTemplate> propTemplates;
    
};

static NodeGraphContext gNodeGraph;
static thread_local const char* gParentFilepath;     // Temp value that is only valid during the bgLoadChild. To check for circular dependencies

bool ngInitialize()
{
    Allocator* alloc = memDefaultAlloc();   // TODO: add the option to use any allocator
    gNodeGraph.nodeTemplates.SetAllocator(alloc);
    gNodeGraph.propTemplates.SetAllocator(alloc);

    RegisterBuiltinProps();
    RegisterBuiltinNodes();

    return true;
}

void ngRelease()
{
}

void ngRegisterNode(const NodeDesc& desc, NodeImpl* impl)
{
    ASSERT(impl);
    ASSERT(desc.name);
    
    if (gNodeGraph.nodeTemplates.FindIf([desc](const NodeGraphNodeTemplate& templ)
                                    { return strIsEqualNoCase(desc.name, templ.desc.name);}) != INVALID_INDEX)
    {
        ASSERT_MSG(0, "Node cannot be registered with the name '%s'. Registered name already exists.", desc.name);
        return;
    }
    
    gNodeGraph.nodeTemplates.Push(NodeGraphNodeTemplate {
        .desc = desc,
        .impl = impl
    });
}

void ngUnregisterNode(const char* name)
{
    uint32 index = gNodeGraph.nodeTemplates.FindIf([name](const NodeGraphNodeTemplate& templ)
                                               { return strIsEqualNoCase(name, templ.desc.name);});
    ASSERT(index != INVALID_INDEX);

    gNodeGraph.nodeTemplates.Pop(index);
}

Array<NodeGraphCatName> ngGetRegisteredNodes(Allocator* alloc)
{
    Array<NodeGraphCatName> nodes(alloc);
    for (NodeGraphNodeTemplate& templ : gNodeGraph.nodeTemplates)
        nodes.Push(NodeGraphCatName { templ.desc.category, templ.desc.name });
    return nodes;
}

void ngRegisterProperty(const PropertyDesc& desc, PropertyImpl* impl)
{
    ASSERT(impl);
    ASSERT(desc.name);

    if (gNodeGraph.propTemplates.FindIf([desc](const NodeGraphPropertyTemplate& templ)
                                        { return strIsEqualNoCase(desc.name, templ.desc.name); }) != INVALID_INDEX)
    {
        ASSERT_MSG(0, "Property cannot be registered with the name '%s'. Registered name already exists.", desc.name);
        return;
    }

    gNodeGraph.propTemplates.Push(NodeGraphPropertyTemplate {
        .desc = desc,
        .impl = impl
    });
}

void ngUnregisterProperty(const char* name)
{
    uint32 index = gNodeGraph.propTemplates.FindIf([name](const NodeGraphPropertyTemplate& templ)
                                                   { return strIsEqualNoCase(name, templ.desc.name);});
    ASSERT(index != INVALID_INDEX);
    gNodeGraph.propTemplates.Pop(index);
}

Array<const char*> ngGetRegisteredProperties(Allocator* alloc)
{
    Array<const char*> props(alloc);
    for (NodeGraphPropertyTemplate& templ : gNodeGraph.propTemplates)
        props.Push(templ.desc.name);
    return props;
}

NodeGraph* ngCreate(Allocator* alloc, NodeGraphEvents* events)
{
    NodeGraph* graph = memAllocZeroTyped<NodeGraph>();
    graph->pinPool.SetAllocator(alloc);
    graph->nodePool.SetAllocator(alloc);
    graph->linkPool.SetAllocator(alloc);
    graph->propPool.SetAllocator(alloc);
    graph->childGraphs.SetAllocator(alloc);
    graph->progressEventsQueue.SetAllocator(alloc);
    graph->alloc = alloc;
    graph->events = events;
    graph->progressEventsMutex.Initialize();
    graph->errorString.SetAllocator(alloc);
    graph->errorString.SetGrowPolicy(Blob::GrowPolicy::Linear);

    {
        PinDesc pinDesc {
            .name = "Execute",
            .description = "Execute a node"
        };

        Pin pin {
            .type = PinType::Param,
            .desc = pinDesc,
            .data = {
                .type = PinDataType::Void
            },
            .ready = true,
        };
        PinHandle pinHandle = graph->pinPool.Add(pin);

        // We always have one property to run nodes that doesn't have any input
        graph->executePropHandle = graph->propPool.Add(Property {
            .desc = {
                .name = "Execute",
                .description = "Execute a node"
            },
            .pin = pinHandle,
            .impl = _private::GetVoidPropImpl(),
            .started = true
        });
    }
    
    return graph;
}

void ngDestroy(NodeGraph* graph)
{
    if (graph) {
        if (graph->taskHandle.IsValid() && graph->saveTaskFile)
            tskSaveGraphTask(graph->taskHandle);
        
        for (Pin& pin : graph->pinPool)
            pin.data.Free();

        // TODO:
        // while (graph->nodePool.Count())
        //    ngDestroyNode(graph, graph->nodePool.HandleAt(0));

        graph->metaData.Free();
        graph->outputResult.Free();

        graph->pinPool.Free();
        graph->nodePool.Free();
        graph->linkPool.Free();
        graph->propPool.Free();
        graph->childGraphs.Free();
        graph->errorString.Free();
        graph->progressEventsQueue.Free();
        graph->progressEventsMutex.Release();
        memFree(graph, graph->alloc);
    }
}

NodeHandle ngCreateNode(NodeGraph* graph, const char* name, const SysUUID* uuid)
{
    uint32 index = gNodeGraph.nodeTemplates.FindIf([name](const NodeGraphNodeTemplate& templ)
                                               { return strIsEqualNoCase(name, templ.desc.name);});
    if (index == INVALID_INDEX) {
        ASSERT_MSG(0, "Node with name '%s' not found", name);
        return NodeHandle {};
    }
    
    NodeGraphNodeTemplate& nodeTempl = gNodeGraph.nodeTemplates[index];
    NodeHandle handle = graph->nodePool.Add(Node {
        .desc = nodeTempl.desc,
        .impl = nodeTempl.impl
    });
        
    Node& node = graph->nodePool.Data(handle);
    if (uuid) 
        node.uuid = *uuid;
    else
        sysUUIDGenerate(&node.uuid);
    
    if (!nodeTempl.impl->Initialize(graph, handle)) {
        logError("Failed to create node '%s'", nodeTempl.desc.name);
        logError("\t%s", nodeTempl.impl->GetLastError(graph, handle));
        return NodeHandle {};
    }
    
    node.inPins.SetAllocator(graph->alloc);
    node.outPins.SetAllocator(graph->alloc);
    
    if (node.desc.captureOutput) {
        node.outputText = NEW(memDefaultAlloc(), TextContent);
        node.outputText->Initialize();
    }
    
    const NodeDesc& desc = nodeTempl.desc;
    if (desc.dynamicInPins)
        node.dynamicInPinIndex = desc.numInPins - 1;
    if (desc.dynamicOutPins)
        node.dynamicOutPinIndex = desc.numOutPins - 1;

    for (uint32 i = 0; i < desc.numInPins; i++) {
        const PinDesc& pinDesc = nodeTempl.impl->GetInputPin(i);
        if (desc.dynamicInPins && i == desc.numInPins - 1)
            continue;

        Pin pin {
            .type = PinType::Input,
            .desc = pinDesc,
            .data = {
                .type = pinDesc.data.type
            },
            .owner = handle
        };
        PinHandle pinHandle = graph->pinPool.Add(pin);
        node.inPins.Push(pinHandle);
    }
    
    for (uint32 i = 0; i < desc.numOutPins; i++) {
        const PinDesc& pinDesc = nodeTempl.impl->GetOutputPin(i);
        if (desc.dynamicOutPins && i == desc.numOutPins - 1)
            continue;

        Pin pin {
            .type = PinType::Output,
            .desc = nodeTempl.impl->GetOutputPin(i),
            .data = {
                .type = pinDesc.data.type
            },
            .owner = handle
        };
        PinHandle pinHandle = graph->pinPool.Add(pin);
        node.outPins.Push(pinHandle);
    }
    
    return handle;
}

void ngDestroyNode(NodeGraph* graph, NodeHandle handle)
{
    Node& node = graph->nodePool.Data(handle);
    
    if (node.desc.captureOutput) {
        node.outputText->Release();
        node.outputText = nullptr;
    }
    node.impl->Release(graph, handle);

    MemTempAllocator tmpAlloc;
    for (uint32 i = 0; i < node.inPins.Count(); i++) {
        PinHandle pinHandle = node.inPins[i];
        Pin& pin = graph->pinPool.Data(pinHandle);
        pin.data.Free();
        
        Array<LinkHandle> foundLinks = ngFindLinksWithPin(graph, pinHandle, &tmpAlloc);
        for (LinkHandle linkHandle : foundLinks) {
            if (graph->events)
                graph->events->DeleteLink(linkHandle);
            ngDestroyLink(graph, linkHandle);
        }

        if (node.desc.dynamicInPins && i <= node.dynamicInPinIndex)
            DestroyString(pin.dynName);

        graph->pinPool.Remove(pinHandle);
    }
    
    for (uint32 i = 0; i < node.outPins.Count(); i++) {
        PinHandle pinHandle = node.outPins[i];

        graph->pinPool.Data(pinHandle).data.Free();
        Pin& pin = graph->pinPool.Data(pinHandle);
        pin.data.Free();

        Array<LinkHandle> foundLinks = ngFindLinksWithPin(graph, pinHandle, &tmpAlloc);
        for (LinkHandle linkHandle : foundLinks) {
            if (graph->events)
                graph->events->DeleteLink(linkHandle);
            ngDestroyLink(graph, linkHandle);
        }

        if (node.desc.dynamicOutPins && i <= node.dynamicOutPinIndex) 
            DestroyString(pin.dynName);

        graph->pinPool.Remove(pinHandle);
    }

    node.inPins.Free();
    node.outPins.Free();
    
    graph->nodePool.Remove(handle);
}

NodeHandle ngDuplicateNode(NodeGraph* graph, NodeHandle dupHandle)
{
    Node& srcNode = graph->nodePool.Data(dupHandle);
    
    NodeHandle handle = graph->nodePool.Add(Node {
        .desc = srcNode.desc,
        .impl = srcNode.impl
    });

    Node& node = graph->nodePool.Data(handle);
    sysUUIDGenerate(&node.uuid);
    node.inPins.SetAllocator(graph->alloc);
    node.outPins.SetAllocator(graph->alloc);
    node.dynamicInPinIndex = srcNode.dynamicInPinIndex;
    
    if (!node.impl->InitializeDuplicate(graph, handle, srcNode.data)) {
        logError("Failed to create node '%s'", srcNode.desc.name);
        const char* errorMsg = node.impl->GetLastError(graph, handle);
        ASSERT_MSG(errorMsg, "GetLastError not properly implemented for node: %s", node.desc.name);
        logError("\t%s", errorMsg);
        return NodeHandle {};
    }
    
    if (node.desc.captureOutput) {
        node.outputText = NEW(memDefaultAlloc(), TextContent);
        node.outputText->Initialize();
    }
    
    for (uint32 i = 0; i < srcNode.inPins.Count(); i++) {
        Pin& srcPin = graph->pinPool.Data(srcNode.inPins[i]);
        const PinDesc& pinDesc = srcPin.desc;
        Pin pin {
            .type = PinType::Input,
            .desc = pinDesc,
            .data = {
                .type = pinDesc.data.type
            },
            .owner = handle
        };

        if (srcPin.dynName)
            pin.dynName = DuplicateString(srcPin.dynName);
        
        PinHandle pinHandle = graph->pinPool.Add(pin);
        node.inPins.Push(pinHandle);
    }
    
    for (uint32 i = 0; i < srcNode.outPins.Count(); i++) {
        Pin& srcPin = graph->pinPool.Data(srcNode.outPins[i]);
        const PinDesc& pinDesc = srcPin.desc;
        Pin pin {
            .type = PinType::Output,
            .desc = node.impl->GetOutputPin(i),
            .data = {
                .type = pinDesc.data.type
            },
            .owner = handle
        };

        if (srcPin.dynName)
            pin.dynName = DuplicateString(srcPin.dynName);

        PinHandle pinHandle = graph->pinPool.Add(pin);
        node.outPins.Push(pinHandle);
    }

    return handle;
}

PinHandle ngInsertDynamicPinIntoNode(NodeGraph* graph, NodeHandle handle, PinType type, const char* name)
{
    ASSERT(type != PinType::Param);

    Node& node = graph->nodePool.Data(handle);
    uint32 dynPinIndex;
    Array<PinHandle>* pins;
    const PinDesc* dynPinDesc;

    if (type == PinType::Input) {
        ASSERT_MSG(node.desc.dynamicInPins, "Only nodes with dynamic last pin flags can use this function");
        dynPinIndex = node.dynamicInPinIndex;
        pins = &node.inPins;
        dynPinDesc = &node.impl->GetInputPin(dynPinIndex);
    }
    else {
        ASSERT_MSG(node.desc.dynamicOutPins, "Only nodes with dynamic last pin flags can use this function");
        dynPinIndex = node.dynamicOutPinIndex;
        pins = &node.outPins;
        dynPinDesc = &node.impl->GetOutputPin(dynPinIndex);
    }

    Pin dynPinCopy {
        .type = type,
        .desc = *dynPinDesc,
        .data = {
            dynPinDesc->data.type
        },
        .owner = handle
    };

    // Modify the last pin's name and add an index
    if (name == nullptr) {
        
        String<64> newName(dynPinDesc->name);
        uint32 num = pins->Count() - dynPinIndex + 1;
        String<32> numStr(String<32>::Format("%u", num));
        newName.Append(numStr.CStr());
        dynPinCopy.dynName = CreateString(newName.CStr());
    }
    else {
        dynPinCopy.dynName = CreateString(name);
    }

    PinHandle newHandle = graph->pinPool.Add(dynPinCopy);
    pins->Push(newHandle);

    return newHandle;
}

LinkHandle ngCreateLink(NodeGraph* graph, PinHandle pinA, PinHandle pinB)
{
    ASSERT(graph->pinPool.IsValid(pinA));
    ASSERT(graph->pinPool.IsValid(pinB));

    const Pin& pinAData = graph->pinPool.Data(pinA);
    const Pin& pinBData = graph->pinPool.Data(pinB);

    if ((pinAData.type != PinType::Output && pinAData.type != PinType::Param) || pinBData.type != PinType::Input) {
        logWarning("Cannot connect pin '%s' to pin '%s'", pinAData.desc.name, pinBData.desc.name);
        return LinkHandle {};
    }
    
    LinkHandle handle = graph->linkPool.Add(Link {
        .pinA = pinA,
        .pinB = pinB,
        .nodeA = pinAData.owner,
        .nodeB = pinBData.owner
    });
    
    return handle;
}

void ngDestroyLink(NodeGraph* graph, LinkHandle handle)
{
    ASSERT(graph->linkPool.IsValid(handle));
    graph->linkPool.Remove(handle);
}

PropertyHandle ngCreateProperty(NodeGraph* graph, const char* name, const SysUUID* uuid)
{
    uint32 index = gNodeGraph.propTemplates.FindIf([name](const NodeGraphPropertyTemplate& templ)
                                                   { return strIsEqualNoCase(name, templ.desc.name);});
    if (index == INVALID_INDEX) {
        ASSERT_MSG(0, "Property with name '%s' not found", name);
        return PropertyHandle();
    }

    if (uuid) {
        if (graph->propPool.FindIf([&uuid](const Property& p)->bool { return p.uuid == *uuid; }).IsValid()) {
            char uuidStr[64];
            sysUUIDToString(*uuid, uuidStr, sizeof(uuidStr));
            logWarning("Property with uuid '%s' (name: '%s') already exists", uuidStr, name);
            return PropertyHandle();
        }
    }
    
    NodeGraphPropertyTemplate& propTempl = gNodeGraph.propTemplates[index];
    Property prop {
        .desc = propTempl.desc,
        .impl = propTempl.impl
    };
    if (uuid) 
        prop.uuid = *uuid;
    else
        sysUUIDGenerate(&prop.uuid);
    PropertyHandle handle = graph->propPool.Add(prop);
    
    if (!propTempl.impl->Initialize(graph, handle)) {
        logError("Failed to create property '%s'", propTempl.desc.name);
        return PropertyHandle {};
    }

    return handle;
}

bool ngStartProperty(NodeGraph* graph, PropertyHandle handle, const PinData& initialData, StringId pinName, StringId pinDescText, const void* internalData)
{
    Property& prop = graph->propPool.Data(handle);
    ASSERT(!prop.started);
    
    PinDataType dataType = prop.desc.dataType;
    ASSERT(initialData.type == dataType);
    ASSERT(pinName);

    // Check for duplicates
    const char* pinNameStr = GetString(pinName);
    for (Property& prop : graph->propPool) {
        if (!prop.started)
            continue;
        if (strIsEqualNoCase(GetString(prop.pinName), pinNameStr))
            return false;
    }

    // initialize internal data referenced by the optional pointer
    if (internalData)
        prop.impl->CopyInternalData(graph, handle, internalData);

    Pin pin {
        .type = PinType::Param,
        .desc = {
            .name = GetString(pinName),
            .description = GetString(pinDescText),
            .data = initialData
        },
        .data = {
            .type = prop.desc.dataType
        },
        .ready = true,
    };
    pin.data.CopyFrom(initialData);

    prop.pin = graph->pinPool.Add(pin);
    prop.pinName  = pinName;
    prop.pinDesc = pinDescText;

    prop.started = true;
    return true;
}

bool ngEditProperty(NodeGraph* graph, PropertyHandle handle, StringId pinName, StringId pinDescText)
{
    Property& prop = graph->propPool.Data(handle);
    ASSERT(prop.started);
    ASSERT(pinName);

    // Check for duplicates
    const char* pinNameStr = GetString(pinName);
    for (uint32 i = 0; i < graph->propPool.Count(); i++) {
        PropertyHandle h = graph->propPool.HandleAt(i);
        Property& prop = graph->propPool.Data(h);
        if (!prop.started)
            continue;
        if (h != handle && strIsEqualNoCase(GetString(prop.pinName), pinNameStr))
            return false;
    }

    if (prop.pinName && prop.pinName != pinName)
        DestroyString(prop.pinName);
    if (prop.pinDesc && prop.pinDesc != pinDescText)
        DestroyString(prop.pinDesc);
    prop.pinName = pinName;
    prop.pinDesc = pinDescText;

    return true;
}

void ngDestroyProperty(NodeGraph* graph, PropertyHandle handle)
{
    Property& prop = graph->propPool.Data(handle);
    prop.impl->Release(graph, handle);

    if (prop.pin.IsValid()) {
        Pin& pin = graph->pinPool.Data(prop.pin);

        MemTempAllocator tmpAlloc;
        Array<LinkHandle> links = ngFindLinksWithPin(graph, prop.pin, &tmpAlloc);
        for (LinkHandle linkHandle : links) {
            if (graph->events)
                graph->events->DeleteLink(linkHandle);
            ngDestroyLink(graph, linkHandle);
        }

        pin.desc.data.Free();
        pin.data.Free();

        graph->pinPool.Remove(prop.pin);
    }

    if (prop.pinName)
        DestroyString(prop.pinName);
    if (prop.pinDesc)
        DestroyString(prop.pinDesc);

    graph->propPool.Remove(handle);
}

static void ngExecuteNodesTask(uint32 index, void* userData)
{
    NodeGraphTask* task = reinterpret_cast<NodeGraphTask*>(userData);
    
    ASSERT(index < task->numNodes);
    ASSERT(task->errorNodes);

    NodeHandle handle = task->nodes[index];
    Node& node = task->graph->nodePool.Data(handle);

    bool inputsHasLoop = false;

    // Propogate partialData flag from input pins to output pins
    // Nodes that absorbLoops, never propogate data arrays
    if (!node.desc.absorbsLoop) {
        for (PinHandle pinHandle : node.inPins) {
            Pin& pin = ngGetPinData(task->graph, pinHandle);
            inputsHasLoop |= (pin.ready & pin.loop);
        }
    }

    node.isRunning = true;
    task->errorNodes[index] = !node.impl->Execute(task->graph, handle, node.inPins, node.outPins);
    node.isRunning = false;

    if (inputsHasLoop) {
        for (PinHandle pinHandle : node.outPins) {
            Pin& pin = ngGetPinData(task->graph, pinHandle);
            pin.loop = true;
        }
    }
    else if (!node.desc.loop) {
        for (PinHandle pinHandle : node.outPins) {
            Pin& pin = ngGetPinData(task->graph, pinHandle);
            pin.loop = false;
        }
    }
}

static inline void ngPushProgressEvent(NodeGraph* graph, const NodeGraphProgressEvent& e)
{
    MutexScope mtx(graph->progressEventsMutex);
    graph->progressEventsQueue.Push(e);
}

bool ngExecute(NodeGraph* graph, bool debugMode, mco_coro* coro, TextContent* redirectContent, TskEventHandle parentEventHandle)
{
    if (debugMode) {
        ASSERT_MSG(coro, "coroutine must be provided in debugMode");
    }

    Array<NodeHandle> nodes;
    Array<LinkHandle> links;
    Array<NodeHandle> runNodes;

    auto NodeIsStranded = [graph](const Node& node)->bool {
        for (PinHandle pinHandle : node.inPins) {
            for (Link& link : graph->linkPool) {
                if (link.pinB == pinHandle)
                    return false;
            }
        }
        return true;
    };

    // All input pins should have data ready 
    auto NodeReadyToExecute = [graph, &links](const Node& node)->bool {
        uint32 i = 0;
        for (PinHandle pinHandle : node.inPins) {
            Pin& inPin = graph->pinPool.Data(pinHandle);

            // Note: There can be multiple links per project. one might be ready and other might not.. 
            // TODO: test this more thoroughly
            bool foundLink = false;
            bool hasReadyConnection = false;
            for (LinkHandle linkHandle : links) {
                Link& link = graph->linkPool.Data(linkHandle);
                if (link.pinB == pinHandle) {
                    foundLink = true;
                    hasReadyConnection |= graph->pinPool.Data(link.pinA).ready;
                }
            }

            if ((!foundLink && !inPin.desc.optional) || (foundLink && !hasReadyConnection)) 
                return false;

            i++;
        }
        return true;
    };

    auto NodeIsRoot = [graph, &NodeReadyToExecute](const Node& node)->bool {
        for (PinHandle pinHandle : node.inPins) {
            for (Link& link : graph->linkPool) {
                if (link.pinB == pinHandle && 
                    graph->pinPool.Data(link.pinA).type == PinType::Output &&
                    !graph->nodePool.Data(link.nodeA).desc.constant)
                {
                    return false;
                }
            }
        }
        return NodeReadyToExecute(node);
    };

    auto TransferData = [graph](Pin& pinA, Pin& pinB) {
        PinData& sourceData = pinA.ready ? pinA.data : pinA.desc.data;
        PinData& destData = pinB.data;
        destData.CopyFrom(sourceData);
    };
    
    // Go through all the links and bring the Source pin (from Executed Node) data to Destination
    // Flag destination pins as ready
    auto ProcessLink = [graph, &TransferData](Array<LinkHandle>& links, PinHandle inPinHandle) {
        // Note: there can be multiple connected pins on each input pin
        for (uint32 i = 0; i < links.Count(); i++) {
            Link& link = graph->linkPool.Data(links[i]);
            if (link.pinB == inPinHandle) {
                Pin& pinA = graph->pinPool.Data(link.pinA);
                Pin& pinB = graph->pinPool.Data(link.pinB);

                if (pinA.ready) {
                    // Do not destroy/finish links that has partial data
                    if (pinA.loop) {
                        if (!graph->nodePool.Data(link.nodeA).desc.absorbsLoop) {
                            TransferData(pinA, pinB);
                            pinB.ready = true;
                            pinB.loop = true;
                        }
                    }
                    else {
                        TransferData(pinA, pinB);
                        pinB.ready = true;
                        pinB.loop = false;
    
                        ngPushProgressEvent(graph, NodeGraphProgressEvent {
                            .type = NodeGraphProgressEventType::LinkComplete,
                            .linkHandle = links[i]
                        });
    
                    }
                }
            }
        }
    };

    auto ProcessParamLinks = [graph, &TransferData](Array<LinkHandle>& links) {
        for (uint32 i = 0; i < links.Count(); i++) {
            Link& link = graph->linkPool.Data(links[i]);
            Pin& pinA = graph->pinPool.Data(link.pinA);
            if (pinA.type == PinType::Param) {
                Pin& pinB = graph->pinPool.Data(link.pinB);
                ASSERT(pinB.type == PinType::Input);

                // edge case ?
                if (pinA.data.type == PinDataType::String && pinA.data.str == nullptr) {
                    pinA.data.SetString("");
                }

                TransferData(pinA, pinB);
                pinB.ready = true;
                
                ngPushProgressEvent(graph, NodeGraphProgressEvent {
                    .type = NodeGraphProgressEventType::LinkComplete,
                    .linkHandle = links[i]
                });

            }
        }
    };
    
    auto NodeHasLoop = [graph](NodeHandle handle)->bool {
        Node& node = graph->nodePool.Data(handle);
        for (PinHandle pinHandle : node.inPins) {
            Pin& pin = graph->pinPool.Data(pinHandle);
            if (pin.loop) 
                return true;
        }

        for (PinHandle pinHandle : node.outPins) {
            Pin& pin = graph->pinPool.Data(pinHandle);
            if (pin.loop) 
                return true;
        }
        return false;
    };

    auto DispatchNodes = [graph, &links, &ProcessLink, &NodeHasLoop, &redirectContent](Array<NodeHandle>& nodes)->bool {
        bool redirectSet = false;
        for (NodeHandle nodeHandle : nodes) {
            Node& node = graph->nodePool.Data(nodeHandle);
            ++node.numRuns;

            // Reset all output pin states only on the first run
            if (node.IsFirstTimeRun()) {
                if (node.desc.captureOutput)
                    node.outputText->mRedirectContent = nullptr;
                for (PinHandle pinHandle : node.outPins) {
                    Pin& pin = graph->pinPool.Data(pinHandle);
    
                    pin.ready = false;    
                    pin.loop = false;
                }
            }

            // TODO: For now, we only set redirectContent only to the first node and discard others
            // Haven't found a way to properly show several content in redirected text viewer
            if (node.desc.captureOutput && !redirectSet && redirectContent) {
                node.outputText->mRedirectContent = redirectContent;
                if (redirectContent->mBlob.Size())
                    redirectContent->mBlob.SetSize(redirectContent->mBlob.Size() - 1);    // Remove the last null-terminator
                redirectSet = true;
            }


            // Prepare data for input pins
            // Either get them from it's link or get from default data
            for (PinHandle pinHandle : node.inPins) {
                Pin& pin = graph->pinPool.Data(pinHandle);

                ProcessLink(links, pinHandle);

                // Fill inPins without connection with default data
                if (!pin.ready && pin.desc.optional && pin.desc.hasDefaultData) {
                    pin.data.CopyFrom(pin.desc.data);
                    pin.ready = true;
                }
            }

            ngPushProgressEvent(graph, NodeGraphProgressEvent {
                .type = NodeGraphProgressEventType::NodeExecuteBegin,
                .nodeHandle = nodeHandle
            });
        }

        #if CONFIG_ENABLE_ASSERT
            for (NodeHandle nodeHandle : nodes) {
                Node& node = graph->nodePool.Data(nodeHandle);
                for (PinHandle pinHandle : node.inPins) {
                    Pin& pin = graph->pinPool.Data(pinHandle);
                    if (pin.ready || pin.desc.optional)
                        continue;
                    ASSERT_MSG(links.FindIf([graph, pinHandle](const LinkHandle hdl) {return graph->linkPool.Data(hdl).pinB == pinHandle;}) == INVALID_INDEX,
                            "Node: %s. Pin (%s) data is not ready, but it's not optional and is connected.", node.desc.name, pin.desc.name);
                }
            }
        #endif

        NodeGraphTask task = {
            .graph = graph,
            .nodes = nodes.Ptr(),
            .errorNodes = memAllocZeroTyped<bool>(nodes.Count()),   // temp: ouch! we can't use tempalloc and dispatch
            .numNodes = nodes.Count()
        };
        JobsHandle handle = jobsDispatch(JobsType::LongTask, ngExecuteNodesTask, &task, nodes.Count());
        jobsWaitForCompletion(handle);

        graph->errorString.Reset();
        bool errorOccured = false;
        for (uint32 i = 0; i < nodes.Count();) {
            NodeHandle nodeHandle = nodes[i];

            if (!task.errorNodes[i]) {
                ngPushProgressEvent(graph, NodeGraphProgressEvent {
                    .type = NodeGraphProgressEventType::NodeExecuteSuccess,
                    .nodeHandle = nodeHandle
                });

                // If node is executed successfully and doesn't have any partial data, then it's safe to remove it from the runNodes
                if (!NodeHasLoop(nodeHandle)) {
                    Swap<bool>(task.errorNodes[i], task.errorNodes[nodes.Count()-1]);
                    nodes.RemoveAndSwap(i);
                    continue;
                }
            }
            else {
                ngPushProgressEvent(graph, NodeGraphProgressEvent {
                    .type = NodeGraphProgressEventType::NodeExecuteError,
                    .nodeHandle = nodeHandle
                });

                Node& node = graph->nodePool.Data(nodeHandle);
                const char* errText = node.impl->GetLastError(graph, nodeHandle);

                graph->errorString.Write(node.desc.name, strLen(node.desc.name));
                if (errText && errText[0]) {
                    graph->errorString.Write<char>(':');
                    graph->errorString.Write<char>(' ');
                    graph->errorString.Write(errText, strLen(errText));
                }
                graph->errorString.Write<char>('\n');

                errorOccured = true;
            }

            i++;
        }

        if (errorOccured)
            graph->errorString.Write<char>(0);

        memFree(task.errorNodes);
        return !errorOccured;
    };

    auto CleanUp = [graph, &runNodes, &nodes, &links](bool error) {
        runNodes.Free();
        nodes.Free();
        links.Free();
        tskEndGraphExecute(graph->taskHandle, graph->metaData.str, error);
        graph->parentEventHandle = TskEventHandle();
    };

    //--------------------------------------------------------------------------------------
    atomicStore32Explicit(&graph->stop, 0, AtomicMemoryOrder::Release);

    graph->outputResult.SetString(nullptr);
    graph->metaData.SetString(nullptr);
    graph->parentEventHandle = parentEventHandle;
    graph->saveTaskFile = true;

    tskBeginGraphExecute(graph->taskHandle, graph->parentTaskHandle, parentEventHandle);
    
    // Collect all the links
    for (uint32 i = 0; i < graph->linkPool.Count(); i++)
        links.Push(graph->linkPool.HandleAt(i));
    
    // Collect all the nodes except the stranded ones
    // Stranded ones are not connected to any output/param
    for (uint32 i = 0; i < graph->nodePool.Count(); i++) {
        NodeHandle nodeHandle = graph->nodePool.HandleAt(i);
        Node& node = graph->nodePool.Data(nodeHandle);
        if (node.desc.constant || !NodeIsStranded(node)) {
            nodes.Push(nodeHandle);
        }
        else {
            ngPushProgressEvent(graph, NodeGraphProgressEvent {
                .type = NodeGraphProgressEventType::NodeResetStranded,
                .nodeHandle = nodeHandle
            });
        }
    }

    // Reset all the pins and nodes (except param pins)
    for (Pin& pin : graph->pinPool) {
        if (pin.type != PinType::Param) {
            pin.ready = false;
            pin.loop = false;
        }
    }

    for (NodeHandle nodeHandle : nodes)  {
        Node& node = graph->nodePool.Data(nodeHandle);
        node.numRuns = 0;
        node.runningTime = 0;
        node.isRunning = false;

        ngPushProgressEvent(graph, NodeGraphProgressEvent {
            .type = NodeGraphProgressEventType::NodeResetIdle,
            .nodeHandle = nodeHandle
        });
    }

    // Run all constant nodes immediately
    for (uint32 i = 0; i < nodes.Count();) {
        Node& node = graph->nodePool.Data(nodes[i]);
        if (node.desc.constant) {
            uint64 tick = timerGetTicks();
            node.numRuns = 1;
            if (!node.impl->Execute(graph, nodes[i], node.inPins, node.outPins)) {
                logError("Executing constant node failed: %s", node.impl->GetTitleUI(graph, nodes[i]));
                ngPushProgressEvent(graph, NodeGraphProgressEvent {
                    .type = NodeGraphProgressEventType::NodeExecuteError,
                    .nodeHandle = nodes[i]
                });
                CleanUp(true);
                return false;
            }
            node.runningTime = timerToSec(timerDiff(timerGetTicks(), tick));
            nodes.RemoveAndSwap(i);
        }
        else {
            i++;
        }
    }
   
    // Find the nodes to begin execution
    // Starting nodes and the ones that only input param pins
    for (uint32 i = 0; i < nodes.Count();) {
        Node& node = graph->nodePool.Data(nodes[i]);
        if (NodeIsRoot(node)) {
            runNodes.Push(nodes[i]);
            nodes.RemoveAndSwap(i);
        } else {
            i++;
        }
    }

    if (runNodes.Count() == 0) {
        logError("There are no root nodes to run the graph. Connect 'Execute' pin to Nodes");
        CleanUp(true);
        return false;
    }

    // Transfer all input parameters into the initial nodes and dispatch them
    ProcessParamLinks(links);
    if (!DispatchNodes(runNodes)) {
        CleanUp(true);
        return false;
    }

    if (debugMode)
        mco_yield(coro);

    // Put back nodes that are not yet finished
    for (NodeHandle nodeHandle : runNodes) 
        nodes.Push(nodeHandle);
    runNodes.Clear();

    // Now dispatch nodes, until there is none left, or some fatal error happens
    while (nodes.Count() && atomicLoad32Explicit(&graph->stop, AtomicMemoryOrder::Acquire) == 0) {
        for (uint32 i = 0; i < nodes.Count();) {
            if (NodeReadyToExecute(graph->nodePool.Data(nodes[i]))) {
                runNodes.Push(nodes[i]);
                nodes.RemoveAndSwap(i);
            }
            else {
                i++;
            }
        }
        
        if (runNodes.Count() == 0)
            break;
        
        // Dispatch runNodes and wait for them
        if (!DispatchNodes(runNodes)) {
            CleanUp(true);
            return false;
        }
        if (debugMode)
            mco_yield(coro);

        // Put back nodes that are not yet finished
        for (NodeHandle nodeHandle : runNodes) 
            nodes.Push(nodeHandle);
        runNodes.Clear();
    }
    
    CleanUp(false);
    return true;
}

NodeHandle ngFindNodeById(NodeGraph* graph, SysUUID uuid)
{
    return graph->nodePool.FindIf([&uuid](const Node& n) { return n.uuid == uuid; });
}

PropertyHandle ngFindPropertyById(NodeGraph* graph, SysUUID uuid)
{
    return graph->propPool.FindIf([&uuid](const Property& p) { return p.uuid == uuid; });
}

Node& ngGetNodeData(NodeGraph* graph, NodeHandle handle)
{
    return graph->nodePool.Data(handle);
}

Pin& ngGetPinData(NodeGraph* graph, PinHandle handle)
{
    return graph->pinPool.Data(handle);
}

Link& ngGetLinkData(NodeGraph* graph, LinkHandle handle)
{
    return graph->linkPool.Data(handle);
}

Property& ngGetPropertyData(NodeGraph* graph, PropertyHandle handle)
{
    return graph->propPool.Data(handle);
}

Array<LinkHandle> ngFindLinksWithPin(NodeGraph* graph, PinHandle pinHandle, Allocator* alloc)
{
    Array<LinkHandle> links(alloc);

    for (uint32 i = 0; i < graph->linkPool.Count(); i++) {
        LinkHandle handle = graph->linkPool.HandleAt(i);
        const Link& link = graph->linkPool.Data(i);
        if (link.pinA == pinHandle || link.pinB == pinHandle) 
            links.Push(handle);
    }

    return links;
}

void ngUpdateEvents(NodeGraph* graph)
{
    if (!graph->events)
        return;

    MutexScope mtx(graph->progressEventsMutex);
    for (NodeGraphProgressEvent& ev : graph->progressEventsQueue) {
        switch (ev.type) {
        case NodeGraphProgressEventType::NodeResetIdle:
            graph->events->NodeIdle(ev.nodeHandle, false);
            break;
        case NodeGraphProgressEventType::NodeResetStranded:
            graph->events->NodeIdle(ev.nodeHandle, true);
            break;
        case NodeGraphProgressEventType::NodeExecuteBegin:
            graph->events->NodeStarted(ev.nodeHandle);
            break;
        case NodeGraphProgressEventType::NodeExecuteSuccess:
            graph->events->NodeFinished(ev.nodeHandle, false);
            break;
        case NodeGraphProgressEventType::NodeExecuteError:
            graph->events->NodeFinished(ev.nodeHandle, true);
            break;
        case NodeGraphProgressEventType::LinkComplete:
            graph->events->LinkFinished(ev.linkHandle);
            break;
        }
    }
    graph->progressEventsQueue.Clear();

    // Increase running time for each node in execution
    float dt = 1.0f/ImGui::GetIO().Framerate;
    for (Node& node : graph->nodePool) {
        if (node.isRunning)
            node.runningTime += dt;
    }
}

void PinData::CopyFrom(const PinData& pin)
{
    if (pin.type == PinDataType::String) {
        switch (this->type) {
        case PinDataType::String:  this->SetString(pin.str, uint32(pin.size));  break;
        case PinDataType::Boolean: this->b = strToBool(pin.str);    break;
        case PinDataType::Integer: this->n = strToInt(pin.str); break;
        case PinDataType::Float:   this->f = (float)strToDouble(pin.str);  break;
        case PinDataType::Void:    break;
        default: ASSERT_MSG(0, "Not implemented");
        }
    }
    else if (pin.type == PinDataType::Boolean) {
        switch (this->type) {
        case PinDataType::Boolean: this->b = pin.b; break;
        case PinDataType::String:  this->SetString(pin.b ? "1" : "0");  break;
        case PinDataType::Integer: this->n = pin.b ? 1 : 0; break;
        case PinDataType::Float:   this->f = pin.b ? 1.0f : 0;  break;
        case PinDataType::Void:    break;
        default: ASSERT_MSG(0, "Not implemented");
        }
    }
    else if (pin.type == PinDataType::Integer) {
        switch (this->type) {
        case PinDataType::Boolean: this->b = pin.n > 0; break;
        case PinDataType::String:  { char str[32]; strPrintFmt(str, sizeof(str), "%u", pin.n);  this->SetString(str); break; }
        case PinDataType::Integer: this->n = pin.n; break;
        case PinDataType::Float:   this->f = float(pin.n);  break;
        case PinDataType::Void:    break;
        default: ASSERT_MSG(0, "Not implemented");
        }
    }
    else if (pin.type == PinDataType::Float) {
        switch (this->type) {
        case PinDataType::Boolean: this->b = pin.f > 0; break;
        case PinDataType::String:  { char str[32]; strPrintFmt(str, sizeof(str), "%f", pin.f);  this->SetString(str); break; }
        case PinDataType::Integer: this->n = int(pin.f); break;
        case PinDataType::Float:   this->f = pin.f;  break;
        case PinDataType::Void:    break;
        default: ASSERT_MSG(0, "Not implemented");
        }
    }
    else if (pin.type == PinDataType::Void) {
        switch (this->type) {
        case PinDataType::Void: break;
        case PinDataType::String:  this->SetString(""); break;
        case PinDataType::Boolean: this->b = true; break;
        case PinDataType::Integer: this->n = 1; break;
        case PinDataType::Float:   this->f = 1.0f;  break;
        default: ASSERT_MSG(0, "Not implemented");
        }
    }
    else if (pin.type == PinDataType::Buffer) {
        if (this->type == PinDataType::Buffer) {
            this->SetBuffer(pin.buff, pin.size);
        }
        else {
            ASSERT_MSG(0, "Cannot translate Buffer types to opaque ones");
        }
    }
    else {
        ASSERT_MSG(0, "Not implemented");
    }
}

void PinData::SetString(const char* _str, uint32 _len)
{
    if (this->str) {
        memFree(this->str);
        this->str = nullptr;
        this->size = 0;
    }
    
    if (_str) {
        if (_len == 0)
            _len = strLen(_str);

        this->str = memAllocCopyRawBytes<char>(_str, _len + 1);
        this->size = _len;
    }
}

void PinData::SetBuffer(const void* _buff, size_t _size)
{
    if (this->buff) {
        memFree(this->buff);
        this->buff = nullptr;
    }

    if (_buff) {
        this->buff = memAllocCopyRawBytes<void>(_buff, _size);
        this->size = _size;
    }
}

void PinData::Free()
{
    if (this->type == PinDataType::Buffer || this->type == PinDataType::String) {
        memFree(this->buff);
        this->buff = nullptr;
        this->size = 0;
    }
}

Array<PropertyHandle> ngGetProperties(NodeGraph* graph, Allocator* alloc)
{
    Array<PropertyHandle> props(alloc);
    for (uint32 i = 0; i < graph->propPool.Count(); i++)
        props.Push(graph->propPool.HandleAt(i));
    return props;
}

static PinData ngLoadPinData(sjson_node* jdata)
{
    if (!jdata)
        return PinData {};

    PinData data {};
    const char* typeStr = sjson_get_string(jdata, "Type", "");
    if (strIsEqual(typeStr, "Boolean")) {
        data.type = PinDataType::Boolean;
        data.b = sjson_get_bool(jdata, "Value", false);
    }
    else if (strIsEqual(typeStr, "Float")) {
        data.type = PinDataType::Float;
        data.f = sjson_get_float(jdata, "Value", 0);
    }
    else if (strIsEqual(typeStr, "Integer")) {
        data.type = PinDataType::Integer;
        data.n = sjson_get_int(jdata, "Value", 0);
    }
    else if (strIsEqual(typeStr, "String")) {
        data.type = PinDataType::String;
        data.SetString(sjson_get_string(jdata, "Value", ""));
    }
    else if (strIsEqual(typeStr, "Void")) {
        data.type = PinDataType::Void;
    }
    else if (strIsEqual(typeStr, "Buffer")) {
        ASSERT(0);
        // TODO
    }

    return data;
};


bool ngLoad(NodeGraph* graph, WksFileHandle fileHandle, char* errMsg, uint32 errMsgSize)
{
    ASSERT(fileHandle.IsValid());

    Path filepath = wksGetFullFilePath(GetWorkspace(), fileHandle);
    Path wfilepath = wksGetWorkspaceFilePath(GetWorkspace(), fileHandle);

    graph->fileHandle = fileHandle;

    // Load task file (optional)
    graph->taskHandle = tskLoadGraphTask(graph->fileHandle);
    ASSERT(graph->taskHandle.IsValid());

    MemTempAllocator tmpAlloc;
    File f;
    if (!f.Open(filepath.CStr(), FileOpenFlags::Read | FileOpenFlags::SeqScan)) {
        logError("Opening file failed: %s", filepath.CStr());
        if (errMsg)
            strPrintFmt(errMsg, errMsgSize, "Opening file failed: %s", wfilepath.CStr());
        return false;
    }

    if (f.GetSize() == 0) {
        logError("Empty file: %s", filepath.CStr());
        if (errMsg)
            strPrintFmt(errMsg, errMsgSize, "Empty file: %s", wfilepath.CStr());
        return false;
    }

    size_t fileSize = f.GetSize();
    char* jsonText = (char*)tmpAlloc.Malloc(fileSize + 1);
    f.Read<char>(jsonText, (uint32)fileSize);
    jsonText[fileSize] = '\0';
    f.Close();

    sjson_context* jctx = sjson_create_context(0, 0, &tmpAlloc);
    ASSERT_ALWAYS(jctx, "Out of memory?");
    sjson_node* jroot = sjson_decode(jctx, jsonText);
    if (!jroot) {
        logError("Parsing json failed: %s", filepath.CStr());
        if (errMsg) 
            strPrintFmt(errMsg, errMsgSize, "Parsing json failed: %s", wfilepath.CStr());
        return false;
    }

    // Dependencies: For now, it is only there to check for circular dependencies
    //               It's data will be populated by child nodes (ngLoadChild)
    if (gParentFilepath) {
        sjson_node* jdeps = sjson_find_member(jroot, "Dependencies");
        sjson_node* jdep = sjson_first_child(jdeps);
        while (jdep) {
            if (strIsEqualNoCase(jdep->string_, gParentFilepath)) {
                logError("Cannot load: %s. circular dependency found: %s", filepath.CStr(), gParentFilepath);
                if (errMsg) 
                    strPrintFmt(errMsg, errMsgSize, "Cannot load: %s. circular dependency found: %s", wfilepath.CStr(), gParentFilepath);
                return false;
            }
            jdep = jdep->next;
        }
    }
    
    // Properties
    {
        sjson_node* jprops = sjson_find_member(jroot, "Properties");
        sjson_node* jprop = sjson_first_child(jprops);
        while (jprop) {
            const char* uuidStr = sjson_get_string(jprop, "Id", "");
            const char* name = sjson_get_string(jprop, "Name", "");
            const char* pinName = sjson_get_string(jprop, "PinName", "");
            const char* pinDesc = sjson_get_string(jprop, "PinDescription", "");
            PinData initialData = ngLoadPinData(sjson_find_member(jprop, "InitialData"));
            
            PropertyHandle handle;
            SysUUID uuid;
            if (initialData.type != PinDataType::Void && sysUUIDFromString(&uuid, uuidStr)) {
                handle = ngCreateProperty(graph, name, &uuid);
                
                Property& prop = ngGetPropertyData(graph, handle);
                ngStartProperty(graph, handle, initialData, CreateString(pinName), CreateString(pinDesc));

                Pin& propPin = ngGetPinData(graph, prop.pin);
                propPin.data = ngLoadPinData(sjson_find_member(jprop, "Data"));
                if (!prop.impl->LoadDataFromJson(graph, handle, jctx, jprop)) {
                    if (errMsg)
                        strPrintFmt(errMsg, errMsgSize, "Loading property data failed: %s (File: %s)", pinName, wfilepath.CStr());
                    return false;
                }

                prop.impl->InitializeDataFromPin(graph, handle);
            }
            else {
                handle = graph->propPool.HandleAt(0);
            }

            jprop = jprop->next;
        }
    }

    // Nodes
    {
        sjson_node* jnodes = sjson_find_member(jroot, "Nodes");
        sjson_node* jnode = sjson_first_child(jnodes);
        while (jnode) {
            const char* uuidStr = sjson_get_string(jnode, "Id", "");
            const char* name = sjson_get_string(jnode, "Name", "");
            sjson_node* jextraInPins = sjson_find_member(jnode, "ExtraInPins");
            sjson_node* jextraOutPins = sjson_find_member(jnode, "ExtraOutPins");

            SysUUID uuid;
            if (sysUUIDFromString(&uuid, uuidStr)) {
                NodeHandle handle = ngCreateNode(graph, name, &uuid);

                Node& node = ngGetNodeData(graph, handle);
                if (node.desc.dynamicInPins && jextraInPins) {
                    sjson_node* jpin = sjson_first_child(jextraInPins);
                    while (jpin) {
                        ngInsertDynamicPinIntoNode(graph, handle, PinType::Input, jpin->string_);
                        jpin = jpin->next;
                    }
                }

                if (node.desc.dynamicOutPins && jextraOutPins) {
                    sjson_node* jpin = sjson_first_child(jextraOutPins);
                    while (jpin) {
                        ngInsertDynamicPinIntoNode(graph, handle, PinType::Output, jpin->string_);
                        jpin = jpin->next;
                    }
                }

                if (!node.impl->LoadDataFromJson(graph, handle, jctx, jnode)) {
                    if (errMsg) {
                        strPrintFmt(errMsg, errMsgSize, "Loading graph '%s' failed while loading node data '%s': %s", 
                                    wfilepath.CStr(), name, 
                                    node.impl->GetLastError(graph, handle) ? node.impl->GetLastError(graph, handle) : "");
                    }
                    return false;
                }

                if (graph->events)
                    graph->events->CreateNode(handle);
            }

            jnode = jnode->next;
        }
    }

    // Links
    {
        sjson_node* jlinks = sjson_find_member(jroot, "Links");
        sjson_node* jlink = sjson_first_child(jlinks);
        while (jlink) {
            const char* nodeAId = sjson_get_string(jlink, "NodeA", "");
            const char* nodeBId = sjson_get_string(jlink, "NodeB", "");
            PinHandle pinA {};
            PinHandle pinB {};
            SysUUID uuidNode;

            if (nodeAId[0] == 0) {
                const char* propId = sjson_get_string(jlink, "PropertyId", "");

                SysUUID uuidProp;
                if (sysUUIDFromString(&uuidProp, propId)) {
                    PropertyHandle handle = graph->propPool.FindIf([uuidProp](const Property& p) { return p.uuid == uuidProp; });
                    if (handle.IsValid())
                        pinA = ngGetPropertyData(graph, handle).pin;
                }
            }
            else {
                int pinId = sjson_get_int(jlink, "PinA", -1);
                ASSERT(pinId != -1);

                if (sysUUIDFromString(&uuidNode, nodeAId)) {
                    NodeHandle handle = graph->nodePool.FindIf([uuidNode](const Node& n) { return n.uuid == uuidNode; });
                    if (handle.IsValid()) 
                        pinA = ngGetNodeData(graph, handle).outPins[pinId];
                }
            }
            ASSERT(pinA.IsValid());

            int pinBId = sjson_get_int(jlink, "PinB", -1);
            ASSERT(pinBId != -1);

            if (sysUUIDFromString(&uuidNode, nodeBId)) {
                NodeHandle handle = graph->nodePool.FindIf([uuidNode](const Node& n) { return n.uuid == uuidNode; });
                Node& nodeB = ngGetNodeData(graph, handle);
                if (pinBId < int(nodeB.inPins.Count()))
                    pinB = nodeB.inPins[pinBId];
            }

            if (!pinA.IsValid() || !graph->pinPool.IsValid(pinA) || !pinB.IsValid() || !graph->pinPool.IsValid(pinB)) {
                logWarning("Invalid pin connection, ignoring.");
            }
            else {
                LinkHandle handle = ngCreateLink(graph, pinA, pinB);
                if (graph->events)
                    graph->events->CreateLink(handle);
            }

            jlink = jlink->next;
        }
    }
    
    sjson_destroy_context(jctx);   
    
    return true;
}

sjson_node* ngSavePinData(sjson_context* jctx, const PinData& data)
{
    sjson_node* jdata = sjson_mkobject(jctx);

    switch (data.type) {
    case PinDataType::Void:
        sjson_put_string(jctx, jdata, "Type", "Void");
        break;
    case PinDataType::Boolean:
        sjson_put_string(jctx, jdata, "Type", "Boolean");
        sjson_put_bool(jctx, jdata, "Value", data.b);
        break;
    case PinDataType::Float:
        sjson_put_string(jctx, jdata, "Type", "Float");
        sjson_put_float(jctx, jdata, "Value", data.f);
        break;
    case PinDataType::Integer:
        sjson_put_string(jctx, jdata, "Type", "Integer");
        sjson_put_int(jctx, jdata, "Value", data.n);
        break;
    case PinDataType::String:
        sjson_put_string(jctx, jdata, "Type", "String");
        if (data.str)
            sjson_put_string(jctx, jdata, "Value", data.str);
        break;
    case PinDataType::Buffer:   ASSERT(0); break; // TODO
    default: break;
    }

    return jdata;
};

NodeHandle ngLoadNode(const char* filepath, NodeGraph* graph, bool genId)
{
    MemTempAllocator tmpAlloc;

    File f;
    if (!f.Open(filepath, FileOpenFlags::Read | FileOpenFlags::SeqScan)) {
        logError("Opening file failed: %s", filepath);
        return NodeHandle();
    }

    if (f.GetSize() == 0) {
        logError("Empty file: %s", filepath);
        return NodeHandle();
    }

    size_t fileSize = f.GetSize();
    char* jsonText = (char*)tmpAlloc.Malloc(fileSize + 1);
    f.Read<char>(jsonText, (uint32)fileSize);
    jsonText[fileSize] = '\0';
    f.Close();

    sjson_context* jctx = sjson_create_context(0, 0, &tmpAlloc);
    ASSERT_ALWAYS(jctx, "Out of memory?");
    sjson_node* jroot = sjson_decode(jctx, jsonText);
    if (!jroot) {
        logError("Parsing json failed: %s", filepath);
        return NodeHandle();
    }

    sjson_node* jnode = jroot;
    const char* uuidStr = sjson_get_string(jnode, "Id", "");
    const char* name = sjson_get_string(jnode, "Name", "");
    sjson_node* jextraInPins = sjson_find_member(jnode, "ExtraInPins");
    sjson_node* jextraOutPins = sjson_find_member(jnode, "ExtraOutPins");

    SysUUID uuid;
    bool hasId = genId ? sysUUIDGenerate(&uuid) : sysUUIDFromString(&uuid, uuidStr);
    NodeHandle handle {};

    if (hasId) {
        handle = ngCreateNode(graph, name, &uuid);
        // TODO: handle possible errors

        Node& node = ngGetNodeData(graph, handle);
        if (node.desc.dynamicInPins && jextraInPins) {
            sjson_node* jpin = sjson_first_child(jextraInPins);
            while (jpin) {
                ngInsertDynamicPinIntoNode(graph, handle, PinType::Input, jpin->string_);
                jpin = jpin->next;
            }
        }

        if (node.desc.dynamicOutPins && jextraOutPins) {
            sjson_node* jpin = sjson_first_child(jextraOutPins);
            while (jpin) {
                ngInsertDynamicPinIntoNode(graph, handle, PinType::Output, jpin->string_);
                jpin = jpin->next;
            }
        }

        if (!node.impl->LoadDataFromJson(graph, handle, jctx, jnode)) {
            // TODO: handle possible errors
            return NodeHandle();
        }
    }

    return handle;
}

bool ngSaveNode(const char* filepath, NodeGraph* graph, NodeHandle nodeHandle)
{
    MemTempAllocator tmpAlloc;
    
    sjson_context* jctx = sjson_create_context(0, 0, &tmpAlloc);
    ASSERT_ALWAYS(jctx, "Out of memory?");
    sjson_node* jroot = sjson_mkobject(jctx);

    char uuidStr[64];

    Node& node = graph->nodePool.Data(nodeHandle);
    sjson_node* jnode = jroot;
    sysUUIDToString(node.uuid, uuidStr, sizeof(uuidStr));
    sjson_append_member(jctx, jnode, "Id", sjson_mkstring(jctx, uuidStr));
    sjson_append_member(jctx, jnode, "Name", sjson_mkstring(jctx, node.desc.name));

    if (node.desc.dynamicInPins) {
        uint32 numExtraPins = node.inPins.Count() >= node.desc.numInPins ? (node.inPins.Count() - node.desc.numInPins + 1) : 0;
        if (numExtraPins) {
            const char** extraPinNames = tmpAlloc.MallocTyped<const char*>(numExtraPins);
            for (uint32 i = node.dynamicInPinIndex; i < node.inPins.Count(); i++) {
                Pin& pin = ngGetPinData(graph, node.inPins[i]);
                ASSERT(pin.dynName);
                extraPinNames[i - node.dynamicInPinIndex] = GetString(pin.dynName);
            }
            sjson_put_strings(jctx, jnode, "ExtraInPins", extraPinNames, numExtraPins);                
        }
    }

    if (node.desc.dynamicOutPins) {
        uint32 numExtraPins = node.outPins.Count() >= node.desc.numOutPins ? (node.outPins.Count() - node.desc.numOutPins + 1) : 0;
        const char** extraPinNames = tmpAlloc.MallocTyped<const char*>(numExtraPins);
        for (uint32 i = node.dynamicOutPinIndex; i < node.outPins.Count(); i++) {
            Pin& pin = ngGetPinData(graph, node.outPins[i]);
            ASSERT(pin.dynName);
            extraPinNames[i - node.dynamicOutPinIndex] = GetString(pin.dynName);
        }
        sjson_put_strings(jctx, jnode, "ExtraOutPins", extraPinNames, numExtraPins);   
    }

    node.impl->SaveDataToJson(graph, nodeHandle, jctx, jnode);

    char* jsonText = sjson_stringify(jctx, jroot, "\t");
    File f;
    if (!f.Open(filepath, FileOpenFlags::Write)) {
        logError("Cannot open file for writing: %s", filepath);
        return false;
    }

    f.Write(jsonText, strLen(jsonText));
    f.Close();

    sjson_free_string(jctx, jsonText);
    sjson_destroy_context(jctx);

    return true;
}

bool ngSave(NodeGraph* graph, WksFileHandle fileHandle)
{
    if (!fileHandle.IsValid())
        fileHandle = graph->fileHandle;
    ASSERT(fileHandle.IsValid());

    WksWorkspace* wks = GetWorkspace();
    graph->fileHandle = fileHandle;
    Path filepath = wksGetFullFilePath(GetWorkspace(), fileHandle);

    MemTempAllocator tmpAlloc;
    
    sjson_context* jctx = sjson_create_context(0, 0, &tmpAlloc);
    ASSERT_ALWAYS(jctx, "Out of memory?");
    sjson_node* jroot = sjson_mkobject(jctx);

    char uuidStr[64];

    // Dependencies
    {
        sjson_node* jdeps = sjson_mkarray(jctx);
        sjson_append_member(jctx, jroot, "Dependencies", jdeps);

        for (const NodeGraphDep& dep : graph->childGraphs)
            sjson_append_element(jdeps, sjson_mkstring(jctx, wksGetWorkspaceFilePath(wks, dep.fileHandle).CStr()));
    }

    // Properties
    {
        sjson_node* jprops = sjson_mkarray(jctx);
        sjson_append_member(jctx, jroot, "Properties", jprops);

        for (uint32 i = 0; i < graph->propPool.Count(); i++) {
            PropertyHandle handle = graph->propPool.HandleAt(i);
            Property& prop = graph->propPool.Data(handle);
            Pin& pin = graph->pinPool.Data(prop.pin);
            sjson_node* jprop = sjson_mkobject(jctx);
            
            sysUUIDToString(prop.uuid, uuidStr, sizeof(uuidStr));
            sjson_append_member(jctx, jprop, "Id", sjson_mkstring(jctx, uuidStr));
            sjson_append_member(jctx, jprop, "Name", sjson_mkstring(jctx, prop.desc.name));
            sjson_append_member(jctx, jprop, "PinName", sjson_mkstring(jctx, GetString(prop.pinName)));
            sjson_append_member(jctx, jprop, "PinDescription", sjson_mkstring(jctx, GetString(prop.pinDesc)));
            sjson_append_member(jctx, jprop, "InitialData", ngSavePinData(jctx, pin.desc.data));
            sjson_append_member(jctx, jprop, "Data", ngSavePinData(jctx, pin.data));

            prop.impl->SaveDataToJson(graph, handle, jctx, jprop);
            sjson_append_element(jprops, jprop);
        }
    }

    // Node
    {
        sjson_node* jnodes = sjson_mkarray(jctx);
        sjson_append_member(jctx, jroot, "Nodes", jnodes);

        for (uint32 i = 0; i < graph->nodePool.Count(); i++) {
            NodeHandle handle = graph->nodePool.HandleAt(i);
            Node& node = graph->nodePool.Data(handle);
            sjson_node* jnode = sjson_mkobject(jctx);
            sysUUIDToString(node.uuid, uuidStr, sizeof(uuidStr));
            sjson_append_member(jctx, jnode, "Id", sjson_mkstring(jctx, uuidStr));
            sjson_append_member(jctx, jnode, "Name", sjson_mkstring(jctx, node.desc.name));

            if (node.desc.dynamicInPins) {
                uint32 numExtraPins = node.inPins.Count() >= node.desc.numInPins ? (node.inPins.Count() - node.desc.numInPins + 1) : 0;
                if (numExtraPins) {
                    const char** extraPinNames = tmpAlloc.MallocTyped<const char*>(numExtraPins);
                    for (uint32 i = node.dynamicInPinIndex; i < node.inPins.Count(); i++) {
                        Pin& pin = ngGetPinData(graph, node.inPins[i]);
                        ASSERT(pin.dynName);
                        extraPinNames[i - node.dynamicInPinIndex] = GetString(pin.dynName);
                    }
                    sjson_put_strings(jctx, jnode, "ExtraInPins", extraPinNames, numExtraPins);                
                }
            }

            if (node.desc.dynamicOutPins) {
                uint32 numExtraPins = node.outPins.Count() >= node.desc.numOutPins ? (node.outPins.Count() - node.desc.numOutPins + 1) : 0;
                const char** extraPinNames = tmpAlloc.MallocTyped<const char*>(numExtraPins);
                for (uint32 i = node.dynamicOutPinIndex; i < node.outPins.Count(); i++) {
                    Pin& pin = ngGetPinData(graph, node.outPins[i]);
                    ASSERT(pin.dynName);
                    extraPinNames[i - node.dynamicOutPinIndex] = GetString(pin.dynName);
                }
                sjson_put_strings(jctx, jnode, "ExtraOutPins", extraPinNames, numExtraPins);   
            }

            node.impl->SaveDataToJson(graph, handle, jctx, jnode);

            sjson_append_element(jnodes, jnode);
        }
    }

    // Links
    {
        sjson_node* jlinks = sjson_mkarray(jctx);
        sjson_append_member(jctx, jroot, "Links", jlinks);

        for (Link& link : graph->linkPool) {
            sjson_node* jlink = sjson_mkobject(jctx);
            // sjson_append_member(jctx, jlink, "NodeA", sjson_mknumber(jctx, link.nodeA.id));
            // sjson_append_member(jctx, jlink, "NodeB", sjson_mknumber(jctx, link.nodeB.id));
            
            if (link.nodeA.IsValid()) {
                Node& nodeA = graph->nodePool.Data(link.nodeA);
                sysUUIDToString(nodeA.uuid, uuidStr, sizeof(uuidStr));
                sjson_append_member(jctx, jlink, "NodeA", sjson_mkstring(jctx, uuidStr));
                uint32 pinAIndex = nodeA.outPins.Find(link.pinA);
                sjson_append_member(jctx, jlink, "PinA", sjson_mknumber(jctx, pinAIndex != INVALID_INDEX ? pinAIndex : -1));
            }
            else {
                PropertyHandle propHandle = graph->propPool.FindIf([link](const Property& prop) { return prop.pin == link.pinA; });
                Property& prop = graph->propPool.Data(propHandle);
                sysUUIDToString(prop.uuid, uuidStr, sizeof(uuidStr));
                sjson_append_member(jctx, jlink, "PropertyId", sjson_mkstring(jctx, uuidStr));
            }

            Node& nodeB = graph->nodePool.Data(link.nodeB);
            sysUUIDToString(nodeB.uuid, uuidStr, sizeof(uuidStr));
            sjson_append_member(jctx, jlink, "NodeB", sjson_mkstring(jctx, uuidStr));
            uint32 pinBIndex = nodeB.inPins.Find(link.pinB);
            sjson_append_member(jctx, jlink, "PinB", sjson_mknumber(jctx, pinBIndex != INVALID_INDEX ? pinBIndex : -1));

            sjson_append_element(jlinks, jlink);
        }
    }

    char* jsonText = sjson_stringify(jctx, jroot, "\t");
    File f;
    if (!f.Open(filepath.CStr(), FileOpenFlags::Write)) {
        logError("Cannot open file for writing: %s", wksGetWorkspaceFilePath(GetWorkspace(), fileHandle).CStr());
        return false;
    }

    f.Write(jsonText, strLen(jsonText));
    f.Close();

    sjson_free_string(jctx, jsonText);
    sjson_destroy_context(jctx);

    return true;    
}

const char* ngGetName(NodeGraph* graph)
{
    ASSERT(graph->fileHandle.IsValid());
    return wksGetFileInfo(GetWorkspace(), graph->fileHandle).name;
}

WksFileHandle ngGetFileHandle(NodeGraph* graph)
{
    return graph->fileHandle;
}

void ngRemoveDynamicPin(NodeGraph* graph, NodeHandle handle, PinType type, uint32 pinIndex)
{
    uint32 dynPinIndex;
    Array<PinHandle>* pins;
    Node& node = graph->nodePool.Data(handle);

    if (type == PinType::Input) {
        ASSERT(node.desc.dynamicInPins);
        dynPinIndex = node.dynamicInPinIndex;
        pins = &node.inPins;
    }
    else {
        ASSERT(node.desc.dynamicOutPins);
        dynPinIndex = node.dynamicOutPinIndex;
        pins = &node.outPins;
    }

    ASSERT(pinIndex >= dynPinIndex);

    PinHandle pinHandle = (*pins)[pinIndex];
    Pin& pin = graph->pinPool.Data(pinHandle);
    ASSERT(pin.dynName);

    DestroyString(pin.dynName);
    pin.data.Free();

    pins->Pop(pinIndex);
    graph->pinPool.Remove(pinHandle);

    // Remove all links with the pin Handle
    MemTempAllocator tmpAlloc;
    Array<LinkHandle> foundLinks = ngFindLinksWithPin(graph, pinHandle, &tmpAlloc);
    for (LinkHandle linkHandle : foundLinks) {
        if (graph->events)
            graph->events->DeleteLink(linkHandle);
        ngDestroyLink(graph, linkHandle);
    }
}

void ngStop(NodeGraph* graph)
{
    for (uint32 i = 0; i < graph->nodePool.Count(); i++) {
        NodeHandle handle = graph->nodePool.HandleAt(i);
        Node& node = graph->nodePool.Data(handle);
        if (node.isRunning)
            node.impl->Abort(graph, handle);
    }
    atomicStore32Explicit(&graph->stop, 1, AtomicMemoryOrder::Release);
}

NodeGraph* ngLoadChild(NodeGraph* graph, WksFileHandle childGraphFile, char* errMsg, uint32 errMsgSize, bool checkForCircularDep)
{
    if (checkForCircularDep)
        gParentFilepath = wksGetWorkspaceFilePath(GetWorkspace(), graph->fileHandle).CStr();

    NodeGraph* childGraph = ngCreate(graph->alloc, nullptr);
    ASSERT(childGraph);
    if (childGraph) {
        if (!ngLoad(childGraph, childGraphFile, errMsg, errMsgSize)) {
            ngDestroy(childGraph);
            childGraph = nullptr;
        }

        Path filepath = wksGetFullFilePath(GetWorkspace(), childGraphFile);        
        Path dir = filepath.GetDirectory();
        Path filename = filepath.GetFileName();

        Path layoutFilepath = Path::Join(dir, filename).Append(".layout");
        if (layoutFilepath.IsFile())
            ngLoadPropertiesFromFile(graph, layoutFilepath.CStr());
        
        layoutFilepath = Path::Join(dir, filename).Append(".user_layout");
        if (layoutFilepath.IsFile())
            ngLoadPropertiesFromFile(graph, layoutFilepath.CStr());

        childGraph->parentTaskHandle = graph->taskHandle;
    }

    if (checkForCircularDep)
        gParentFilepath = nullptr;

    uint32 childIndex = graph->childGraphs.FindIf([childGraphFile](const NodeGraphDep& dep) { return dep.fileHandle == childGraphFile; });
    if (childIndex != INVALID_INDEX) {
        ++graph->childGraphs[childIndex].count;
    }
    else {
        graph->childGraphs.Push(NodeGraphDep {
            .fileHandle = childGraphFile,
            .count = 1
        });
    }
    return childGraph;
}

void ngUnloadChild(NodeGraph* graph, WksFileHandle childGraphFile)
{
    uint32 childIndex = graph->childGraphs.FindIf([childGraphFile](const NodeGraphDep& dep) { return dep.fileHandle == childGraphFile; });
    if (childIndex != INVALID_INDEX) {
        --graph->childGraphs[childIndex].count;
        if (graph->childGraphs[childIndex].count == 0) {
            graph->childGraphs.RemoveAndSwap(childIndex);
        }
    }
}

bool ngHasChild(NodeGraph* graph, WksFileHandle childGraphFile)
{
    uint32 childIndex = graph->childGraphs.FindIf([childGraphFile](const NodeGraphDep& dep) { return dep.fileHandle == childGraphFile; });
    return childIndex != INVALID_INDEX;
}

bool ngReloadChildNodes(NodeGraph* graph, WksFileHandle childGraphFile)
{
    bool r = true;
    for (uint32 i = 0; i < graph->nodePool.Count(); i++) {
        NodeHandle handle = graph->nodePool.HandleAt(i);
        Node& node = graph->nodePool.Data(handle);
        // TODO: had to hardcode the name here. ouch!
        if (strIsEqual(node.desc.name, "EmbedGraph") && 
            ((Node_EmbedGraph*)node.impl)->GetGraphFileHandle(graph, handle) == childGraphFile) 
        {
            logVerbose("Reloading child node '%s' in graph '%s'", 
                       node.impl->GetTitleUI(graph, handle), 
                       wksGetWorkspaceFilePath(GetWorkspace(), graph->fileHandle).CStr());
            r &= ((Node_EmbedGraph*)node.impl)->ReloadGraph(graph, handle);
        }
    }
    return r;
}

void ngLoadPropertiesFromJson(NodeGraph* graph, sjson_node* jprops)
{
    sjson_node* jvalues = sjson_find_member(jprops, "Values");
    if (jvalues) {
        sjson_node* jvalue = sjson_first_child(jvalues);
        SysUUID uuid;
        while (jvalue) {
            const char* uuidStr = sjson_get_string(jvalue, "Id", "");
            if (sysUUIDFromString(&uuid, uuidStr)) {
                PropertyHandle propHandle = ngFindPropertyById(graph, uuid);
                if (propHandle.IsValid()) {
                    Property& prop = ngGetPropertyData(graph, propHandle);
                    if (prop.started && prop.pin.IsValid()) {
                        Pin& pin = ngGetPinData(graph, prop.pin);
                        sjson_node* jdata = sjson_find_member(jvalue, "Data");
                        if (jdata) {
                            pin.data.Free();
                            pin.data = ngLoadPinData(jdata);
                                
                            prop.impl->InitializeDataFromPin(graph, propHandle);
                        } // if "Data" is found
                    } // If property is initialized
                } // if property found
            } // if uuid is value
                
            jvalue = jvalue->next;
        }
    }
}

bool ngLoadPropertiesFromFile(NodeGraph* graph, const char* jsonFilepath)
{
    MemTempAllocator tmpAlloc;
    File f;
    if (!f.Open(jsonFilepath, FileOpenFlags::Read | FileOpenFlags::SeqScan)) {
        logError("Opening file failed: %s", jsonFilepath);
        return false;
    }

    if (f.GetSize() == 0) {
        logError("Empty file: %s", jsonFilepath);
        return false;
    }

    size_t fileSize = f.GetSize();
    char* jsonText = (char*)tmpAlloc.Malloc(fileSize + 1);
    f.Read<char>(jsonText, (uint32)fileSize);
    jsonText[fileSize] = '\0';
    f.Close();

    sjson_context* jctx = sjson_create_context(0, 0, &tmpAlloc);
    ASSERT_ALWAYS(jctx, "Out of memory?");
    sjson_node* jroot = sjson_decode(jctx, jsonText);
    if (!jroot) {
        logError("Parsing json failed: %s", jsonFilepath);
        return false;
    }

    sjson_node* jprop = sjson_find_member(jroot, "Parameters");
    if (jprop) {
        ngLoadPropertiesFromJson(graph, jprop);
        return true;
    }
    else {
        return false;
    }
}

void ngSavePropertiesToJson(NodeGraph* graph, sjson_context* jctx, sjson_node* jprops)
{
    sjson_node* jvalues = sjson_mkarray(jctx);
    sjson_append_member(jctx, jprops, "Values", jvalues);
           
    char uuidStr[64];
    for (Property& prop : graph->propPool) {
        if (prop.started && prop.pin.IsValid()) {
            sjson_node* jvalue = sjson_mkobject(jctx);
                    
            sysUUIDToString(prop.uuid, uuidStr, sizeof(uuidStr));
            sjson_put_string(jctx, jvalue, "Id", uuidStr);
            Pin& pin = ngGetPinData(graph, prop.pin);
            sjson_append_member(jctx, jvalue, "Data", ngSavePinData(jctx, pin.data));
                    
            sjson_append_element(jvalues, jvalue);
        }
    }
}

bool ngSavePropertiesToFile(NodeGraph* graph, const char* jsonFilepath)
{
    MemTempAllocator tmpAlloc;
    sjson_context* jctx = sjson_create_context(0, 0, &tmpAlloc);
    ASSERT_ALWAYS(jctx, "Out of memory?");
    sjson_node* jroot = sjson_mkobject(jctx);

    sjson_node* jprop = sjson_mkobject(jctx);
    sjson_append_member(jctx, jroot, "Parameters", jprop);

    ngSavePropertiesToJson(graph, jctx, jprop);

    char* jsonText = sjson_stringify(jctx, jroot, "\t");
    File f;
    if (!f.Open(jsonFilepath, FileOpenFlags::Write)) {
        logError("Cannot open file for writing: %s", jsonFilepath);
        return false;
    }

    f.Write(jsonText, strLen(jsonText));
    f.Close();

    sjson_free_string(jctx, jsonText);
    sjson_destroy_context(jctx);

    return true;
}

const char* ngGetLastError(NodeGraph* graph)
{
    return graph->errorString.Size() ? (const char*)graph->errorString.Data() : "";
}

void ngSetOutputResult(NodeGraph* graph, const PinData& pinData)
{
    graph->outputResult.CopyFrom(pinData);
}

const PinData& ngGetOutputResult(NodeGraph* graph)
{
    return graph->outputResult;
}
TskGraphHandle ngGetTaskHandle(NodeGraph* graph)
{
    return graph->taskHandle;
}

TskGraphHandle ngGetParentTaskHandle(NodeGraph* graph)
{
    return graph->parentTaskHandle;
}

TskEventHandle ngGetParentEventHandle(NodeGraph* graph)
{
    return graph->parentEventHandle;
}

void ngSetMetaData(NodeGraph* graph, const PinData& pinData)
{
    graph->metaData.CopyFrom(pinData);
}

const PinData& ngGetMetaData(NodeGraph* graph)
{
    return graph->metaData;
}
