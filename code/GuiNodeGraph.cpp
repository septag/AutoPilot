#include "GuiNodeGraph.h"

#include "Core/Log.h"
#include "Core/MathScalar.h"
#include "Core/BlitSort.h"
#include "Core/Hash.h"

#include "GuiUtil.h"
#include "Main.h"
#include "BuiltinNodes.h"
#include "Workspace.h"
#include "GuiTextView.h"


#include "ImGui/imnodes.h"

#include "External/sjson/sjson.h"

struct NewPropData
{
    const char* propName;
    char name[64];
    char description[512];
    PropertyHandle handle;
    PinData initialData;
};

struct EditPropData
{
    PropertyHandle handle;
    char name[64];
    char description[512];
};

struct EditNodeData
{
    NodeHandle handle;
};

struct ImportPropertiesData
{
    NodeGraph* graph;
    NodeHandle nodeHandle;
    uint32 numProps;
    PropertyHandle* props;
    bool* propFlags;
    bool addToCurrentGraphProps;
};

void GuiNodeGraph::Initialize()
{
    mCtx = ImNodes::CreateContext();
    mEditorCtx = ImNodes::EditorContextCreate();
}

void GuiNodeGraph::Release()
{
    mNodes.Free();
    mLinks.Free();
    mSelectedNodes.Free();

    if (mEditorCtx)
        ImNodes::EditorContextFree(mEditorCtx);
    if (mCtx) 
        ImNodes::DestroyContext(mCtx);
}

static void GuiNodeGraph_OpenProperties(GuiNodeGraph* uigraph)
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
    if (ImGui::BeginPopupContextItem("PropsMenu")) {
        MemTempAllocator tmpAlloc;
        Array<const char*> propNames = ngGetRegisteredProperties(&tmpAlloc);
        for (uint32 i = 0; i < propNames.Count(); i++) {
            if (ImGui::MenuItem(propNames[i])) {
                NewPropData* data = memAllocZeroTyped<NewPropData>();
                data->propName = propNames[i];

                uigraph->mModalData = data;
                uigraph->mToggleModal = "New Property";
            }
        }

        ImGui::EndPopup();
    }
    ImGui::PopStyleVar();
}

static void GuiNodeGraph_OpenNodeDebugger(GuiNodeGraph* uigraph)
{
    auto ShowPinData = [uigraph](const char* name, const Pin& pin) {
        char idStr[64];
        strPrintFmt(idStr, sizeof(idStr), "##%s__value", name);
        char valueStr[64];
        
        switch (pin.data.type) {
        case PinDataType::String:
            if (pin.data.size)
                ImGui::InputText(idStr, pin.data.str, pin.data.size, ImGuiInputTextFlags_ReadOnly);
            else 
                ImGui::NewLine();
            break;
        case PinDataType::Float:
            strPrintFmt(valueStr, sizeof(valueStr), "%f", pin.data.f);
            ImGui::InputText(idStr, valueStr, sizeof(valueStr), ImGuiInputTextFlags_ReadOnly);
            break;
        case PinDataType::Integer: 
            strPrintFmt(valueStr, sizeof(valueStr), "%u", pin.data.n);
            ImGui::InputText(idStr, valueStr, sizeof(valueStr), ImGuiInputTextFlags_ReadOnly);
            break;
        case PinDataType::Boolean: 
            ImGui::TextUnformatted(pin.data.b ? "True" : "False");   
            break;
        case PinDataType::Void:
            ImGui::TextUnformatted(pin.ready ? "Ready" : "Not Ready");   
            break;
        default:    
            break;
        }
    };

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
    ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0, 0, 0, 1.0));
    if (ImGui::BeginPopupContextItem("NodeDebug")) {
        
        Node& node = ngGetNodeData(uigraph->mGraph, uigraph->mDebugNodeHandle);
        ImGui::TextUnformatted("Inputs:");
        ImGui::BeginChild("InputPinsWnd", ImVec2(500, 120));
        for (uint32 pinIndex = 0; pinIndex < node.inPins.Count(); pinIndex++) {
            PinHandle pinHandle = node.inPins[pinIndex];
            Pin& pin = ngGetPinData(uigraph->mGraph, pinHandle);
                
            const char* pinName;
            uint32 dynPinIndex = INVALID_INDEX;
            if (node.desc.dynamicInPins && pinIndex >= node.dynamicInPinIndex) {
                pinName = GetString(pin.dynName);
                dynPinIndex = pinIndex;
            } 
            else {
                pinName = pin.desc.name;
            }

            ImGui::Text("%s: ", pinName);
            ImGui::SameLine();
            ShowPinData(pinName, pin);
        }
        ImGui::EndChild();

        ImGui::Separator();

        ImGui::TextUnformatted("Outputs:");
        ImGui::BeginChild("OutputPinsWnd", ImVec2(500, 120));
        for (uint32 pinIndex = 0; pinIndex < node.outPins.Count(); pinIndex++) {
            PinHandle pinHandle = node.outPins[pinIndex];
            Pin& pin = ngGetPinData(uigraph->mGraph, pinHandle);

            const char* pinName;
            uint32 dynPinIndex = INVALID_INDEX;
            if (node.desc.dynamicOutPins && pinIndex >= node.dynamicOutPinIndex) {
                pinName = GetString(pin.dynName);
                dynPinIndex = pinIndex;
            } 
            else {
                pinName = pin.desc.name;
            }

            ImGui::Text("%s: ", pinName);
            ImGui::SameLine();
            ShowPinData(pin.desc.name, pin);
        }
        ImGui::EndChild();


        ImGui::EndPopup();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}

static void GuiNodeGraph_RenderModals(GuiNodeGraph* uigraph)
{
    auto CloseModal = [uigraph]() {
        memFree(uigraph->mModalData);
        uigraph->mModalData = nullptr;
        ImGui::CloseCurrentPopup();
    };

    // Property
    if (ImGui::BeginPopupModal("New Property", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        NewPropData* data = reinterpret_cast<NewPropData*>(uigraph->mModalData);
        if (!data->handle.IsValid()) {
            data->handle = ngCreateProperty(uigraph->mGraph, data->propName);
        }
        Property& prop = ngGetPropertyData(uigraph->mGraph, data->handle);
        data->initialData.type = prop.desc.dataType;       // TODO: fix this!

        ImGui::InputText("Name", data->name, sizeof(data->name), ImGuiInputTextFlags_CharsNoBlank);
        ImGui::InputTextMultiline("Description", data->description, sizeof(data->description), ImVec2(0, 50));

        ImGui::Separator();

        bool allowClose = prop.impl->ShowCreateUI(uigraph->mGraph, data->handle, data->initialData);

        ImGui::Separator();

        if (ImGui::Button("OK", ImVec2(120, 0))) { 
            if (data->name[0] && allowClose) {
                if (ngStartProperty(uigraph->mGraph, data->handle, data->initialData, 
                                    CreateString(data->name), CreateString(data->description))) 
                {
                    uigraph->mParamsNodeWidth = 0;
                    uigraph->mUnsavedChanges = true;
                    CloseModal(); 
                }
                else {
                    guiStatus(LogLevel::Warning, "Paramter name already exists: %s", data->name);
                }
            }
            else {
                guiStatus(LogLevel::Warning, "Parameters are not filled out correctly");
            }
        }

        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();

        if (ImGui::Button("Cancel", ImVec2(120, 0))) {
            data->initialData.Free();
            ngDestroyProperty(uigraph->mGraph, data->handle);
            CloseModal();
        }

        ImGui::EndPopup();
    }

    if (ImGui::BeginPopupModal("Edit Property", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        EditPropData* data = reinterpret_cast<EditPropData*>(uigraph->mModalData);
        Property& prop = ngGetPropertyData(uigraph->mGraph, data->handle);

        ImGui::InputText("Name", data->name, sizeof(data->name), ImGuiInputTextFlags_CharsNoBlank);
        ImGui::InputTextMultiline("Description", data->description, sizeof(data->description), ImVec2(0, 50));

        ImGui::Separator();

        bool allowClose = prop.impl->ShowCreateUI(uigraph->mGraph, data->handle, ngGetPinData(uigraph->mGraph, prop.pin).desc.data);

        ImGui::Separator();

        if (ImGui::Button("OK", ImVec2(120, 0))) { 
            if (data->name[0] && allowClose) {
                if (ngEditProperty(uigraph->mGraph, data->handle, CreateString(data->name), CreateString(data->description))) {
                    uigraph->mParamsNodeWidth = 0;
                    uigraph->mUnsavedChanges = true;
                    CloseModal();
                }
                else {
                    guiStatus(LogLevel::Warning, "Parameter name already exists: %s", data->name);
                }
            }
            else {
                guiStatus(LogLevel::Warning, "Parameters are not filled out correctly");
            }
        }
        ImGui::SetItemDefaultFocus();

        ImGui::EndPopup();
    }

    if (ImGui::BeginPopupModal("Edit Node", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        EditNodeData* data = reinterpret_cast<EditNodeData*>(uigraph->mModalData);
        Node& node = ngGetNodeData(uigraph->mGraph, data->handle);

        bool allowClose = node.impl->ShowEditUI(uigraph->mGraph, data->handle);
        ImGui::Separator();

        if (ImGui::Button("OK", ImVec2(120, 0))) { 
            if (allowClose) {
                CloseModal();
                uigraph->mUnsavedChanges = true;
            }
            else {
                guiStatus(LogLevel::Warning, "Node paramters are not filled out correctly");
            }
        }

        ImGui::SetItemDefaultFocus();

        ImGui::EndPopup();
    }

    if (ImGui::BeginPopupModal("Import properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImportPropertiesData* data = reinterpret_cast<ImportPropertiesData*>(uigraph->mModalData);
        MemTempAllocator tmpAlloc;

        Path graphPath = wksGetWorkspaceFilePath(GetWorkspace(), ngGetFileHandle(data->graph));
        ImGui::LabelText("Graph", graphPath.CStr());
        ImGui::TextUnformatted("Choose properties to import");
        ImGui::BeginChild("PropertyList", ImVec2(0, 150.0f), true, 0);

        for (uint32 i = 1; i < data->numProps; i++) {
            PropertyHandle handle = data->props[i];
            Property& prop = ngGetPropertyData(data->graph, handle);
            ImGui::Checkbox(prop.pinName ? GetString(prop.pinName) : prop.desc.name, &data->propFlags[i]);
        }

        ImGui::EndChild();

        ImGui::Checkbox("Add to current graph properties", &data->addToCurrentGraphProps);
        if (ImGui::Button("OK", ImVec2(120, 0))) { 
            {
                for (uint32 i = 1; i < data->numProps; i++) {
                    if (data->propFlags[i]) {
                        Property& prop = ngGetPropertyData(data->graph, data->props[i]);
                        const char* name = prop.pinName ? GetString(prop.pinName) : prop.desc.name;
                        ngInsertDynamicPinIntoNode(uigraph->mGraph, data->nodeHandle, PinType::Input, name);

                        if (data->addToCurrentGraphProps) {                            
                            PropertyHandle propHandle = ngCreateProperty(uigraph->mGraph, prop.desc.name, &prop.uuid);
                            if (!propHandle.IsValid() ||
                                !ngStartProperty(uigraph->mGraph, propHandle, ngGetPinData(data->graph, prop.pin).data, 
                                                 DuplicateString(prop.pinName), DuplicateString(prop.pinDesc), prop.data))
                            {
                                logWarning("Cannot add property '%s' to the current graph");
                            }
                            else {
                                prop.impl->InitializeDataFromPin(uigraph->mGraph, propHandle);
                                uigraph->mParamsNodeWidth = 0;
                            }
                        }
                    }
                }
            }

            memFree(data->props);
            memFree(data->propFlags);
            CloseModal();
            uigraph->mUnsavedChanges = true;
        }

        ImGui::EndPopup();
    }
}

static uint32 GuiNodeGraph_GetStateColor(GuiNodeGraphNode& node)
{
    switch (node.state) {
    case GuiNodeGraphNode::State::Idle:
        return 0xff0066cc;
    case GuiNodeGraphNode::State::Stranded:
        return 0xff8f96a3;
    case GuiNodeGraphNode::State::Failed:
        return 0xff2828c6;
    case GuiNodeGraphNode::State::Success:
        return 0xff336600;
    case GuiNodeGraphNode::State::Started:
        return 0xffcc9900;
    default:
        return 0x0;
    }
}

void GuiNodeGraph::Render()
{
    MemTempAllocator tmpAlloc;

    bool debugMode = mDebugMode;
    bool readOnly = debugMode || mDisableEdit;

    ImNodes::SetCurrentContext(mCtx);
    ImNodes::EditorContextSet(mEditorCtx);

    Docking& dock = imguiGetDocking();
    if (dock.right && !mFirstTimeShow) {
        ImGui::SetNextWindowDockID(dock.right);
        mFirstTimeShow = true;
    }

    char name[64];
    const char* unsavedStr = mUnsavedChanges ? "*" : "";
    Path wpath = wksGetWorkspaceFilePath(GetWorkspace(), ngGetFileHandle(mGraph));
    strPrintFmt(name, sizeof(name), "%s%s###Graph_%x", ngGetName(mGraph), unsavedStr, hashFnv32Str(wpath.CStr()));
    ImGui::SetNextWindowSize(ImVec2(1024, 1024), ImGuiCond_FirstUseEver);

    if (mRefocus) {
        ImGui::SetWindowFocus(name);
        mRefocus = false;
    }
    
    if (ImGui::Begin(name)) {
        int hoveredNodeId = -1;
        bool nodeHovered = ImNodes::IsNodeHovered(&hoveredNodeId);

        if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows)) {
            SetFocusedGraph(this);
        }

        GuiNodeGraph_RenderModals(this);

        // OpenPopup does not work inside NodeEditor
        if (mToggleModal) {
            ImGui::OpenPopup(mToggleModal);
            mToggleModal = nullptr;
        }

        ImNodes::BeginNodeEditor();
        
        mPan = ImNodes::EditorContextGetPanning();
        
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Right, ImGui::GetItemID())) {
            if (nodeHovered) {
                mContextMenu = GuiNodeGraphContextMenu::Node;
                mSelectedNode = hoveredNodeId;
            }
            else {
                mContextMenu = GuiNodeGraphContextMenu::EmptyArea;
            }
        }
    
        if (ImGui::IsWindowHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Middle))
            ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

        ngUpdateEvents(mGraph);

        // -------------------------------------------------------------------------------------------------------------
        // Double click on the node: Focus on to any existing context or text views
        if (nodeHovered && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) && hoveredNodeId != mParamsNode) {
            NodeHandle nodeHandle = NodeHandle(uint32(hoveredNodeId));
            Node& node = ngGetNodeData(mGraph, nodeHandle);
            if (node.desc.captureOutput && node.outputText) {
                uint32 index = mNodes.FindIf([nodeHandle](const GuiNodeGraphNode& n) { return n.handle == nodeHandle;});
                if (index != INVALID_INDEX) {
                    GuiNodeGraphNode& uiNode = mNodes[index];
                    if (uiNode.textView) 
                        uiNode.refocusOutput = true;
                }
            }
        }

        // -------------------------------------------------------------------------------------------------------------
        // Context Menus
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));

        if (ImGui::BeginPopupContextWindow("GraphContextMenu")) {
            if (mContextMenu == GuiNodeGraphContextMenu::Node) {
                // Multiple nodes are selected.
                if (mSelectedNodes.Count() > 1) {
                    if (ImGui::MenuItem("Delete", nullptr, nullptr, !readOnly)) {
                        for (NodeHandle handle : mSelectedNodes) {
                            if (int(uint32(handle)) != mParamsNode) {
                                uint32 nodeIdx = mNodes.FindIf([handle](const GuiNodeGraphNode& n) { return n.handle == handle; });
                                ASSERT(nodeIdx != INVALID_INDEX);
                                mNodes.RemoveAndSwap(nodeIdx);
                                ngDestroyNode(mGraph, handle);
                            }
                        }
                        mSelectedNodes.Clear();
                    }
                }
                // When a single node is selected and it's not the paramsNode
                else if (mSelectedNode != mParamsNode) {
                    NodeHandle nodeHandle = NodeHandle(uint32(mSelectedNode));
                    uint32 nodeIdx = mNodes.FindIf([nodeHandle](const GuiNodeGraphNode& n) { return n.handle == nodeHandle; });
                    ASSERT(nodeIdx != INVALID_INDEX);
                    GuiNodeGraphNode& n = mNodes[nodeIdx];

                    if (ImGui::MenuItem("Edit Input Pins", nullptr, n.editInPins, 
                                        ngGetNodeData(mGraph, nodeHandle).desc.dynamicInPins && !readOnly)) {
                        n.editInPins = !n.editInPins;
                    }
                    if (ImGui::MenuItem("Edit Output Pins", nullptr, n.editOutPins, 
                                        ngGetNodeData(mGraph, nodeHandle).desc.dynamicOutPins && !readOnly)) {
                        n.editOutPins = !n.editOutPins;
                    }

                    if (ImGui::MenuItem("Duplicate", nullptr, nullptr, !readOnly)) {
                        NodeHandle newHandle = ngDuplicateNode(mGraph, nodeHandle);
                        mNodes.Push(GuiNodeGraphNode { .handle = newHandle });
                        ImNodes::SetNodeScreenSpacePos(int(uint32(newHandle)), ImGui::GetMousePos());
                        mUnsavedChanges = true;
                    }

                    if (ImGui::MenuItem("Save", nullptr, nullptr, !readOnly)) {
                        if (mEvents)
                            mEvents->OnSaveNode(this, nodeHandle);
                    }

                    ImGui::Separator();
                    if (ImGui::MenuItem("Delete", nullptr, nullptr, !readOnly)) {
                        mNodes.RemoveAndSwap(nodeIdx);
                        ngDestroyNode(mGraph, nodeHandle);
                        mUnsavedChanges = true;
                    }
                }
                else {
                    // Params node
                    if (ImGui::MenuItem("Edit Parameters", nullptr, mEditParams, !readOnly)) {
                        mEditParams = !mEditParams;
                        mParamsNodeWidth = 0;
                    }
                    ImGui::Separator();
                    ImGui::SetNextItemWidth(100.0f);
                    if (ImGui::SliderFloat("Width", &mParamsNodeMaxWidth, 150.0f, 1024.0f, "%.0f"))
                        mParamsNodeWidth = 0;
                }
            }
            else if (mContextMenu == GuiNodeGraphContextMenu::EmptyArea) {
                if (!mContextMenuMousePosSet) {
                    mContextMenuMousePosSet = true;
                    mContextMenuPos = ImGui::GetMousePos();
                }
    
                if (ImGui::BeginMenu("Add Node", !readOnly))
                {
                    Array<NodeGraphCatName> nodeNames = ngGetRegisteredNodes(&tmpAlloc);
                    if (nodeNames.Count()) {
                        BlitSort<NodeGraphCatName>(nodeNames.Ptr(), nodeNames.Count(), 
                            [](const NodeGraphCatName& a, const NodeGraphCatName& b)->int { return strcmp(a.first, b.first); });
                        const char* cat = nodeNames[0].first;
                        uint32 startIdx = 0;
                        Array<Pair<uint32, uint32>> items(&tmpAlloc);
                        
                        while (cat) {
                            for (uint32 i = startIdx; i < nodeNames.Count(); i++) {
                                if (cat != nodeNames[i].first) {
                                    items.Push(Pair<uint32, uint32>(startIdx, i));
                                    cat = nodeNames[i].first;
                                    startIdx = i;
                                    break;
                                }                                

                                if (i == nodeNames.Count() - 1) {
                                    items.Push(Pair<uint32, uint32>(startIdx, nodeNames.Count()));
                                    cat = nullptr;
                                }
                            }
                        }

                        for (Pair<uint32, uint32> b : items) {
                            if (ImGui::BeginMenu(nodeNames[b.first].first)) {
                                for (uint32 i = b.first; i < b.second; i++) {
                                    if (ImGui::MenuItem(nodeNames[i].second)) {
                                        NodeHandle newHandle = ngCreateNode(mGraph, nodeNames[i].second);
                                        mNodes.Push(GuiNodeGraphNode { .handle = newHandle });
                                        ImNodes::SetNodeScreenSpacePos(int(uint32(newHandle)), mContextMenuPos);
                                        mUnsavedChanges = true;
                                        mContextMenuMousePosSet = false;
                                    }
                                }
                                ImGui::EndMenu();
                            }
                        }
                    }
                    ImGui::EndMenu();
                }
                
                ImGui::Separator();
                if (ImGui::MenuItem("Minimap", nullptr, mShowMiniMap)) {
                    mShowMiniMap = !mShowMiniMap;
                }
            }

            ImGui::EndPopup();
        }

        ImGui::PopStyleVar();

        // Graph style and properties
        ImNodes::GetStyle().Flags |= ImNodesStyleFlags_GridSnapping;

        // -------------------------------------------------------------------------------------------------------------
        // Parameters
        {
            ImNodes::PushColorStyle(ImNodesCol_TitleBar, 0xff009933);
            ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, 0xff009933);
            ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered, 0xff009933);
            ImNodes::PushColorStyle(ImNodesCol_NodeBackgroundHovered, ImNodes::GetStyle().Colors[ImNodesCol_NodeBackground]);
            
            ImNodes::BeginNode(mParamsNode);
            ImNodes::BeginNodeTitleBar();
            ImGui::TextUnformatted("Parameters");

            GuiNodeGraph_OpenProperties(this);

            if (!readOnly) {
                ImGui::SameLine(mParamsNodeWidth > 0 ? (mParamsNodeWidth - imguiGetFonts().uiFontSize) : 0);
                if (ImGui::Button(ICON_FA_PLUS_SQUARE)) {
                    ImGui::OpenPopup("PropsMenu");
                }
            }
            ImNodes::EndNodeTitleBar();

            Array<PropertyHandle> props = ngGetProperties(mGraph, &tmpAlloc);
            for (uint32 i = 0; i < props.Count(); i++) {
                PropertyHandle propHandle = props[i];
                Property& prop = ngGetPropertyData(mGraph, propHandle);
                if (prop.started) {
                    ImNodes::BeginOutputAttribute(uint32(prop.pin));
                    prop.impl->ShowUI(mGraph, propHandle, mParamsNodeMaxWidth);

                    if (mEditParams && i > 0) {
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_REFRESH)) {
                            Pin& pin = ngGetPinData(mGraph, prop.pin);
                            pin.data.CopyFrom(pin.desc.data);
                            prop.impl->InitializeDataFromPin(mGraph, propHandle);
                        }

                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_PENCIL_SQUARE)) {
                            EditPropData* data = memAllocZeroTyped<EditPropData>();
                            data->handle = propHandle;
                            strCopy(data->name, sizeof(data->name), GetString(prop.pinName));
                            strCopy(data->description, sizeof(data->description), GetString(prop.pinDesc));

                            mModalData = data;
                            mToggleModal = "Edit Property";
                        }

                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_MINUS_SQUARE)) {
                            ngDestroyProperty(mGraph, propHandle);
                            mUnsavedChanges = true;
                            props.Pop(i--);
                        }
                    }

                    ImNodes::EndOutputAttribute();

                    if (i != props.Count() - 1) {
                        ImGui::Dummy(ImVec2(2, 2));
                    }
                }
            }

            ImNodes::EndNode();

            if (mParamsNodeWidth == 0)
                mParamsNodeWidth = ImNodes::GetNodeDimensions(mParamsNode).x;
            mParamsNodePos = ImNodes::GetNodeGridSpacePos(mParamsNode);
            
            ImNodes::PopColorStyle();
            ImNodes::PopColorStyle();
            ImNodes::PopColorStyle();
            ImNodes::PopColorStyle();
        }

        // -------------------------------------------------------------------------------------------------------------    
        // Nodes
        for (GuiNodeGraphNode& uiNode : mNodes) {
            NodeHandle nodeHandle = uiNode.handle;
            Node& node = ngGetNodeData(mGraph, nodeHandle);

            if (uiNode.state != GuiNodeGraphNode::State::Idle && !node.desc.constant) {
                uint32 titleCol = GuiNodeGraph_GetStateColor(uiNode);
                ImNodes::PushColorStyle(ImNodesCol_TitleBar, titleCol);
                ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered, titleCol);
                ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, titleCol);
            }
            else if (node.desc.constant) {
                uint32 titleCol = 0xff004466;
                ImNodes::PushColorStyle(ImNodesCol_TitleBar, titleCol);
                ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered, titleCol);
                ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, titleCol);
            }
            else {
                uint32 titleCol = ImNodes::GetStyle().Colors[ImNodesCol_TitleBar];
                ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered, titleCol);
                ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, titleCol);
                ImNodes::PushColorStyle(ImNodesCol_NodeBackgroundHovered, ImNodes::GetStyle().Colors[ImNodesCol_NodeBackground]);
            }

            if (uiNode.setPos) {
                ImNodes::SetNodeScreenSpacePos(int(uint32(nodeHandle)), uiNode.pos);
                uiNode.setPos = false;
            }

            ImNodes::BeginNode(uint32(nodeHandle));

            if (debugMode)
                GuiNodeGraph_OpenNodeDebugger(this);

            // ---------------------------------------------------------------------------------------------------------
            // Node Title
            ImNodes::BeginNodeTitleBar();
            {
                const char* customTitle = node.impl->GetTitleUI(mGraph, nodeHandle);
                if (!debugMode) {
                    if (customTitle && customTitle[0])
                        ImGui::TextUnformatted(customTitle);
                    else
                        ImGui::TextUnformatted(node.desc.name);
                }
                else {
                    if (customTitle && customTitle[0])
                        ImGui::Text("%s (%u)", customTitle, node.numRuns);
                    else
                        ImGui::Text("%s (%u)", node.desc.name, node.numRuns);

                }
            }

            bool didSameLine = false;

            if (uiNode.state == GuiNodeGraphNode::State::Started) {
                if (!didSameLine)
                    ImGui::SameLine(uiNode.width > 0 ? (uiNode.width - imguiGetFonts().uiFontSize) : 0);
                else
                    ImGui::SameLine();

                static const char* hourglass[] = {
                    ICON_FA_HOURGLASS_START,
                    ICON_FA_HOURGLASS_HALF,
                    ICON_FA_HOURGLASS_END
                };

                uiNode.hourglassTime += 1.0f / ImGui::GetIO().Framerate;
                if (uiNode.hourglassTime >= 0.2f) {
                    int numImages = CountOf(hourglass);
                    uiNode.hourglassIndex = (uiNode.hourglassIndex + 1) % numImages;
                    uiNode.hourglassTime = 0;
                }
                ImGui::TextUnformatted(hourglass[uiNode.hourglassIndex]);
                didSameLine = true;
            }
            else if (uiNode.state == GuiNodeGraphNode::State::Failed) {
                if (!didSameLine)
                    ImGui::SameLine(uiNode.width > 0 ? (uiNode.width - imguiGetFonts().uiFontSize) : 0);
                else
                    ImGui::SameLine();
                
                if (ImGui::Button(ICON_FA_EXCLAMATION_TRIANGLE)) {
                    const char* errorMsg = node.impl->GetLastError(mGraph, nodeHandle);
                    ASSERT_MSG(errorMsg, "GetLastError not implemented correctly for Node: %s", node.desc.name);
                    guiMessageBox(GuiMessageBoxButtons::Ok, GuiMessageBoxFlags::ErrorIcon|GuiMessageBoxFlags::SmallFont, 
                                  nullptr, nullptr, errorMsg);
                }

                didSameLine = true;
            }

            if (debugMode && ngGetNodeData(mGraph, nodeHandle).numRuns) {
                if (!didSameLine)
                    ImGui::SameLine(uiNode.width > 0 ? (uiNode.width - imguiGetFonts().uiFontSize) : 0);
                else
                    ImGui::SameLine();
                didSameLine = true;

                if (ImGui::Button(ICON_FA_INFO)) {
                    mDebugNodeHandle = nodeHandle;
                    ImGui::OpenPopup("NodeDebug");
                }
            }

            if (!readOnly && node.desc.editable) {
                if (!didSameLine)
                    ImGui::SameLine(uiNode.width > 0 ? (uiNode.width - imguiGetFonts().uiFontSize) : 0);
                else
                    ImGui::SameLine();

                didSameLine = true;
                if (ImGui::Button(ICON_FA_BARS)) {
                    EditNodeData* data = memAllocZeroTyped<EditNodeData>();
                    data->handle = nodeHandle;

                    mModalData = data;
                    mToggleModal = "Edit Node";
                }
            }

            if (node.desc.captureOutput) {
                if (!didSameLine)
                    ImGui::SameLine(uiNode.width > 0 ? (uiNode.width - imguiGetFonts().uiFontSize) : 0);
                else
                    ImGui::SameLine();
                
                bool isToggled = false;
                if (uiNode.textView) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonActive));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_ButtonActive));
                    isToggled = true;
                }
                if (ImGui::Button(ICON_FA_TERMINAL)) {
                    if (!uiNode.textView) {
                        uiNode.textView = NEW(memDefaultAlloc(), GuiTextView);
                    }
                    else {
                        uiNode.textView->~GuiTextView();
                        memFree(uiNode.textView);
                        uiNode.textView = nullptr;
                    }
                }
                if (isToggled) {
                    ImGui::PopStyleColor();
                    ImGui::PopStyleColor();
                }
            }
            ImNodes::EndNodeTitleBar();

            // ---------------------------------------------------------------------------------------------------------
            // Input pins
            for (uint32 pinIndex = 0; pinIndex < node.inPins.Count(); pinIndex++) {
                PinHandle pinHandle = node.inPins[pinIndex];
                Pin& pin = ngGetPinData(mGraph, pinHandle);
                
                const char* pinName;
                uint32 dynPinIndex = INVALID_INDEX;
                if (node.desc.dynamicInPins && pinIndex >= node.dynamicInPinIndex) {
                    pinName = GetString(pin.dynName);
                    dynPinIndex = pinIndex;
                } 
                else {
                    pinName = pin.desc.name;
                }

                ImNodesPinShape pinShape = !pin.desc.optional ? ImNodesPinShape_CircleFilled : ImNodesPinShape_TriangleFilled;
                ImNodes::BeginInputAttribute(uint32(pinHandle), pinShape);
                if (debugMode && pin.loop) {
                    ImGui::TextUnformatted(ICON_FA_REPEAT);
                    ImGui::SameLine();
                }

                if (pinHandle == mEditingPinHandle) {
                    ImGui::SetNextItemWidth(100);
                    char idStr[64];
                    strPrintFmt(idStr, sizeof(idStr), "##Pin_%u", uint32(pinHandle));
                    if (ImGui::IsKeyPressed(ImGuiKey_Escape))
                        mEditingPinHandle = PinHandle();

                    ImGui::SetKeyboardFocusHere();
                    if (ImGui::InputText(idStr, mEditingPinName, sizeof(mEditingPinName), 
                                     ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue))
                    {
                        mEditingPinHandle = PinHandle();
                        ASSERT(pin.dynName);
                        DestroyString(pin.dynName);
                        pin.dynName = CreateString(mEditingPinName);
                    }
                }
                else {
                    ImGui::TextUnformatted(pinName);
                }

                if (uiNode.editInPins && node.desc.dynamicInPins && pinIndex >= node.dynamicInPinIndex) {
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_MINUS_SQUARE)) {
                       ngRemoveDynamicPin(mGraph, uiNode.handle, PinType::Input, pinIndex);
                       mUnsavedChanges = true;
                    }
                }
                ImNodes::EndInputAttribute();
            }

            if (node.desc.dynamicInPins && !readOnly) {
                if (ImGui::Button(ICON_FA_PLUS_SQUARE)) {
                    mEditingPinHandle = ngInsertDynamicPinIntoNode(mGraph, nodeHandle, PinType::Input);
                    strCopy(mEditingPinName, sizeof(mEditingPinName), 
                            GetString(ngGetPinData(mGraph, mEditingPinHandle).dynName));
                    mUnsavedChanges = true;
                }
            }
    
            // ---------------------------------------------------------------------------------------------------------
            // Output pins
            for (uint32 pinIndex = 0; pinIndex < node.outPins.Count(); pinIndex++) {
                PinHandle pinHandle = node.outPins[pinIndex];
                Pin& pin = ngGetPinData(mGraph, pinHandle);

                const char* pinName;
                uint32 dynPinIndex = INVALID_INDEX;
                if (node.desc.dynamicOutPins && pinIndex >= node.dynamicOutPinIndex) {
                    pinName = GetString(pin.dynName);
                    dynPinIndex = pinIndex;
                } 
                else {
                    pinName = pin.desc.name;
                }

                ImNodesPinShape pinShape = !pin.desc.optional ? ImNodesPinShape_CircleFilled : ImNodesPinShape_TriangleFilled;
                ImNodes::BeginOutputAttribute(uint32(pinHandle), pinShape);
                ImGui::Indent(100.0f);

                if (pinHandle == mEditingPinHandle) {
                    ImGui::SetNextItemWidth(100);
                    char idStr[64];
                    strPrintFmt(idStr, sizeof(idStr), "##Pin_%u", uint32(pinHandle));
                    if (ImGui::IsKeyPressed(ImGuiKey_Escape))
                        mEditingPinHandle = PinHandle();

                    ImGui::SetKeyboardFocusHere();
                    if (ImGui::InputText(idStr, mEditingPinName, sizeof(mEditingPinName), 
                                         ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue))
                    {
                        mEditingPinHandle = PinHandle();
                        ASSERT(pin.dynName);
                        DestroyString(pin.dynName);
                        pin.dynName = CreateString(mEditingPinName);
                    }
                }
                else {
                    ImGui::TextUnformatted(pinName);
                }

                if (debugMode && pin.loop) {
                    ImGui::SameLine();
                    ImGui::TextUnformatted(ICON_FA_REPEAT);
                }

                if (uiNode.editOutPins && node.desc.dynamicOutPins && pinIndex >= node.dynamicOutPinIndex) {
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_MINUS_SQUARE)) {
                        ngRemoveDynamicPin(mGraph, uiNode.handle, PinType::Output, pinIndex);
                        mUnsavedChanges = true;
                        uiNode.width = 0;
                    }
                }

                ImNodes::EndOutputAttribute();
            }

            if (node.desc.dynamicOutPins && !readOnly) {
                if (ImGui::Button(ICON_FA_PLUS_SQUARE)) {
                    mEditingPinHandle = ngInsertDynamicPinIntoNode(mGraph, nodeHandle, PinType::Output);
                    strCopy(mEditingPinName, sizeof(mEditingPinName), 
                            GetString(ngGetPinData(mGraph, mEditingPinHandle).dynName));
                    mUnsavedChanges = true;
                    uiNode.width = 0;
                }
            }

            ImNodes::EndNode();
            ImNodes::SnapNodeToGrid(uint32(nodeHandle));
            
            if (uiNode.width == 0)
                uiNode.width = ImNodes::GetNodeDimensions(uint32(nodeHandle)).x;
            uiNode.pos = ImNodes::GetNodeGridSpacePos(uint32(nodeHandle));


            ImNodes::PopColorStyle();
            ImNodes::PopColorStyle();
            ImNodes::PopColorStyle();
        }

        // -------------------------------------------------------------------------------------------------------------
        // Links
        for (GuiNodeGraphLink uiLink : mLinks) {
            const Link& link = ngGetLinkData(mGraph, uiLink.handle);

            // Check if link connects to a selected node, then highlight those
            bool highlight = false;
            if (uiLink.finished) {
                ImNodes::PushColorStyle(ImNodesCol_Link, 0xff006633);
            }
            else {
                if (mSelectedNodes.Count()) {
                    highlight |= mSelectedNodes.Find(link.nodeA) != INVALID_INDEX;
                    highlight |= mSelectedNodes.Find(link.nodeB) != INVALID_INDEX;
                    if (highlight)
                        ImNodes::PushColorStyle(ImNodesCol_Link, ImNodes::GetStyle().Colors[ImNodesCol_LinkSelected]);
                }
            }

            ImNodes::Link(uint32(uiLink.handle), uint32(link.pinA), uint32(link.pinB));

            if (highlight || uiLink.finished)
                ImNodes::PopColorStyle();
        }
        
        if (mShowMiniMap) {
            ImNodes::MiniMap(0.2f, ImNodesMiniMapLocation_BottomRight);
        }
    
        ImNodes::EndNodeEditor();

        //--------------------------------------------------------------------------------------------------------------
        // Drag&Drop Nodes
        if (!readOnly && ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("NodeFileDD")) {
                WksFileHandle fileHandle = *((WksFileHandle*)payload->Data);
                ASSERT(payload->DataSize);
                logDebug("Load Node: %s", wksGetWorkspaceFilePath(GetWorkspace(), fileHandle).CStr());

                NodeHandle nodeHandle = ngLoadNode(wksGetFullFilePath(GetWorkspace(), fileHandle).CStr(), mGraph, true);
                if (nodeHandle.IsValid()) {
                    mNodes.Push(GuiNodeGraphNode {
                        .handle = nodeHandle,
                        .pos = ImGui::GetMousePos(),
                        .setPos = true
                    });
                }
            }

            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GraphFileDD")) {
                WksFileHandle fileHandle = *((WksFileHandle*)payload->Data);

                if (fileHandle != ngGetFileHandle(mGraph)) {
                    logDebug("Load Graph: %s", wksGetWorkspaceFilePath(GetWorkspace(), fileHandle).CStr());

                    char errMsg[512];

                    NodeGraph* newGraph = ngLoadChild(mGraph, fileHandle, errMsg, sizeof(errMsg), true);
                    NodeHandle nodeHandle = ngCreateNode(mGraph, "EmbedGraph");
                    ASSERT(nodeHandle.IsValid());
                    Node_EmbedGraph& node = (Node_EmbedGraph&)ngGetNodeData(mGraph, nodeHandle);

                    if (newGraph)
                        node.Set(mGraph, nodeHandle, newGraph, fileHandle);
                    else
                        node.SetLoadError(mGraph, nodeHandle, fileHandle, errMsg);

                    mNodes.Push(GuiNodeGraphNode {
                                .handle = nodeHandle,
                                .pos = ImGui::GetMousePos(),
                                .setPos = true
                    });

                    {
                        ImportPropertiesData* data = memAllocZeroTyped<ImportPropertiesData>();
                        data->graph = newGraph;
                        data->nodeHandle = nodeHandle;
                        Array<PropertyHandle> props = ngGetProperties(newGraph);
                        props.Detach(&data->props, &data->numProps);
                        data->addToCurrentGraphProps = true;

                        if (data->numProps) {
                            data->propFlags = memAllocTyped<bool>(data->numProps);
                            for (uint32 i = 0; i < data->numProps; i++) 
                                data->propFlags[i] = true;
                        }
    
                        mModalData = data;
                        mToggleModal = "Import properties";
                    }
                }
                else {
                    logWarning("Cannot embed the current graph itself");
                }
            }

            ImGui::EndDragDropTarget();
        }
    }

    if (ImGui::IsWindowFocused())
        SetFocusedWindow(FocusedWindow {});
    ImGui::End();

    {
        int numNodes = ImNodes::NumSelectedNodes();
        mSelectedNodes.Clear();

        if (numNodes > 0) {
            int* selected = tmpAlloc.MallocTyped<int>(numNodes);
            ImNodes::GetSelectedNodes(selected);

            for (int i = 0; i < numNodes; i++) 
                mSelectedNodes.Push(NodeHandle(uint32(selected[i])));            
        }
    }

    // Detect link connections
    if (!readOnly) {
        int pinAId, pinBId;
        if (ImNodes::IsLinkCreated(&pinAId, &pinBId)) {
            LinkHandle linkHandle = ngCreateLink(mGraph, PinHandle(uint32(pinAId)), PinHandle(uint32(pinBId)));
            if (linkHandle.IsValid()) {
                mUnsavedChanges = true;
                mLinks.Push(GuiNodeGraphLink { .handle = linkHandle });
            }
        }
    }

    if (!readOnly) {
        int pinId;
        if (ImNodes::IsLinkDropped(&pinId, false)) {
            Array<LinkHandle> foundLinks = ngFindLinksWithPin(mGraph, PinHandle(pinId), &tmpAlloc);
            for (LinkHandle linkHandle : foundLinks) {
                ngDestroyLink(mGraph, linkHandle);
                mUnsavedChanges = true;

                uint32 index = mLinks.FindIf([linkHandle](const GuiNodeGraphLink& l) { return l.handle == linkHandle; });
                if (index != INVALID_INDEX)
                    mLinks.RemoveAndSwap(index);                
            }
            foundLinks.Free();
       }
    }
    
    // Render output text views
    for (GuiNodeGraphNode& uiNode : mNodes) {
        if (uiNode.textView) {
            Node& node = ngGetNodeData(mGraph, uiNode.handle);
            const char* title = node.impl->GetTitleUI(mGraph, uiNode.handle);
            if (title == nullptr || title[0] == 0)
                title = node.desc.name;
            char windowId[64];
            strPrintFmt(windowId, sizeof(windowId), "Output: %s###Output_%x", title, uint32(uiNode.handle));
            if (uiNode.refocusOutput) {
                ImGui::SetWindowFocus(windowId);
                uiNode.refocusOutput = false;
            }
            uiNode.textView->Render(node.outputText, windowId);
        }
    }
}

void GuiNodeGraph::ResetTextViews()
{
    for (GuiNodeGraphNode& uiNode : mNodes) {
        if (uiNode.textView)
            uiNode.textView->Reset();
    }
}

void GuiNodeGraph::ResetStates()
{
    for (GuiNodeGraphNode& uiNode : mNodes) {
        uiNode.state = GuiNodeGraphNode::State::Idle;
    }

    for (GuiNodeGraphLink& uiLink : mLinks) {
        uiLink.finished = false;
    }

}

void GuiNodeGraph::DeleteLink(LinkHandle handle)
{
    uint32 index = mLinks.FindIf([handle](const GuiNodeGraphLink& l) { return l.handle == handle; });
    if (index != INVALID_INDEX)
        mLinks.RemoveAndSwap(index);
}

void GuiNodeGraph::NodeIdle(NodeHandle handle, bool stranded)
{
    uint32 index = mNodes.FindIf([handle](const GuiNodeGraphNode& n) { return n.handle == handle; });
    if (index != INVALID_INDEX)
        mNodes[index].state = stranded ? GuiNodeGraphNode::State::Stranded : GuiNodeGraphNode::State::Idle;
}

void GuiNodeGraph::NodeStarted(NodeHandle handle)
{
    uint32 index = mNodes.FindIf([handle](const GuiNodeGraphNode& n) { return n.handle == handle; });
    if (index != INVALID_INDEX) {
        mNodes[index].hourglassTime = 0;
        mNodes[index].hourglassIndex = 0;
        mNodes[index].state = GuiNodeGraphNode::State::Started;
    }
}

void GuiNodeGraph::NodeFinished(NodeHandle handle, bool withError)
{
    uint32 index = mNodes.FindIf([handle](const GuiNodeGraphNode& n) { return n.handle == handle; });
    if (index != INVALID_INDEX)
        mNodes[index].state = withError ? GuiNodeGraphNode::State::Failed : GuiNodeGraphNode::State::Success;
}

void GuiNodeGraph::LinkFinished(LinkHandle handle)
{
    uint32 index = mLinks.FindIf([handle](const GuiNodeGraphLink& l) { return l.handle == handle; });
    if (index != INVALID_INDEX)
        mLinks[index].finished = true;    
}

void GuiNodeGraph::CreateNode(NodeHandle handle)
{
    mNodes.Push(GuiNodeGraphNode { .handle = handle });
}

void GuiNodeGraph::CreateLink(LinkHandle handle) 
{
    mLinks.Push(GuiNodeGraphLink { .handle = handle });
}

bool ngSaveLayout(const char* filepath, const GuiNodeGraph& uigraph, bool savePropertyValues)
{
    MemTempAllocator tmpAlloc;
    
    sjson_context* jctx = sjson_create_context(0, 0, &tmpAlloc);
    ASSERT_ALWAYS(jctx, "Out of memory?");
    sjson_node* jroot = sjson_mkobject(jctx);
    char uuidStr[64];

    {
        sjson_node* jprop = sjson_mkobject(jctx);
        sjson_append_member(jctx, jroot, "Parameters", jprop);
        sjson_put_floats(jctx, jprop, "Pos", &uigraph.mParamsNodePos.x, 2);
        sjson_put_float(jctx, jprop, "MaxWidth", uigraph.mParamsNodeMaxWidth);
        
        if (savePropertyValues)
            ngSavePropertiesToJson(uigraph.mGraph, jctx, jprop);
    }

    {
        sjson_node* jnodes = sjson_mkarray(jctx);
        sjson_append_member(jctx, jroot, "Nodes", jnodes);

        for (GuiNodeGraphNode& uiNode : uigraph.mNodes) {
            sjson_node* jnode = sjson_mkobject(jctx);
            Node& node = ngGetNodeData(uigraph.mGraph, uiNode.handle);
            sysUUIDToString(node.uuid, uuidStr, sizeof(uuidStr));
            sjson_put_string(jctx, jnode, "Id", uuidStr);
            sjson_put_floats(jctx, jnode, "Pos", &uiNode.pos.x, 2);
            sjson_append_element(jnodes, jnode);
        }
    }
    
    {
        sjson_node* jsettings = sjson_mkobject(jctx);
        sjson_append_member(jctx, jroot, "Settings", jsettings);
        sjson_put_bool(jctx, jsettings, "Minimap", uigraph.mShowMiniMap);
        sjson_put_floats(jctx, jsettings, "Pan", &uigraph.mPan.x, 2);
    }

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

bool ngLoadLayout(const char* filepath, GuiNodeGraph& uigraph)
{
    MemTempAllocator tmpAlloc;

    ImNodes::EditorContextSet(uigraph.mEditorCtx);

    File f;
    if (!f.Open(filepath, FileOpenFlags::Read | FileOpenFlags::SeqScan)) {
        logError("Opening file failed: %s", filepath);
        return false;
    }

    if (f.GetSize() == 0) {
        logError("Empty file: %s", filepath);
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
        logError("Parsing json failed: %s", filepath);
        return false;
    }

    {
        sjson_node* jprop = sjson_find_member(jroot, "Parameters");
        ASSERT(jprop);
        
        ImVec2 pos;
        sjson_get_floats(&pos.x, 2, jprop, "Pos");
        ImNodes::SetNodeGridSpacePos(uigraph.mParamsNode, pos);
        uigraph.mParamsNodeMaxWidth = sjson_get_float(jprop, "MaxWidth", 150.0f);
        
        ngLoadPropertiesFromJson(uigraph.mGraph, jprop);
    }

    {
        SysUUID uuidNode;

        sjson_node* jnodes = sjson_find_member(jroot, "Nodes");
        ASSERT(jnodes);

        sjson_node* jnode = sjson_first_child(jnodes);
        while (jnode) {
            const char* nodeId = sjson_get_string(jnode, "Id", "");
            if (sysUUIDFromString(&uuidNode, nodeId)) {
                NodeHandle handle = ngFindNodeById(uigraph.mGraph, uuidNode);
                if (handle.IsValid()) {
                    ImVec2 pos;
                    sjson_get_floats(&pos.x, 2, jnode, "Pos");
                    ImNodes::SetNodeGridSpacePos(uint32(handle), pos);
                }
            }

            jnode = jnode->next;
        }
    }
    
    {
        sjson_node* jsettings = sjson_find_member(jroot, "Settings");
        
        if (jsettings) {
            uigraph.mShowMiniMap = sjson_get_bool(jsettings, "Minimap", false);
            sjson_get_floats(&uigraph.mPan.x, 2, jsettings, "Pan");
            ImNodes::EditorContextResetPanning(uigraph.mPan);
        }
    }

    sjson_destroy_context(jctx);
    return true;

}
