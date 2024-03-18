#pragma once

#include "Core/StringUtil.h"
#include "Core/System.h"

#include "Common.h"

struct NodeGraph;
typedef struct mco_coro mco_coro;   // minicoro.h
struct TextContent;

enum class PinType : uint32
{
    Input,
    Output,
    Param
};

enum class PinDataType : uint32
{
    Void = 0,
    Boolean,
    Float,
    Integer,
    String,
    Buffer
};

inline const char* PinDataType_Str(PinDataType type)
{
    switch (type) {
        case PinDataType::Void: return "Void";
        case PinDataType::Boolean: return "Boolean";
        case PinDataType::Float: return "Float";
        case PinDataType::Integer: return "Integer";
        case PinDataType::String: return "String";
        case PinDataType::Buffer: return "Buffer";
    }
    return "";
}

struct PinData
{
    PinDataType type;
    size_t size;    // Length of string or size of the buffer

    union {
        bool b;
        float f;
        int n;
        char* str;
        void* buff;
    };
    
    void SetString(const char* _str, uint32 _len = 0);
    void SetBuffer(const void* _buff, size_t _size); 
    void CopyFrom(const PinData& pin);
    void Free();
};

struct PinDesc
{
    const char* name;
    const char* description;
    PinData data;
    bool optional;
    bool hasDefaultData;
};
inline constexpr PinDesc kEmptyPin {};

struct Pin
{
    PinType type;
    PinDesc desc;
    PinData data;
    NodeHandle owner;
    bool ready;
    bool loop;   // Indicate that there is still more passes. For loops and iterative nodes
    StringId dynName;   // Name for dynamic pins
};

struct NodeDesc
{
    const char* name;
    const char* description;
    const char* category;
    uint32 numInPins;
    uint32 numOutPins;
    bool captureOutput;     // Enables capturing the output in the GUI 
    bool dynamicInPins;     // Last input pin is dynamic, so you can add duplicates of the last pin 
    bool dynamicOutPins;    // Last output pin is dynamic, so you can add duplicates of the last pin
    bool loop;
    bool absorbsLoop;       // Nodes that hold partial data in and does not pass them over. Eg. string concat node
    bool editable;          // Nodes that have the edit button
    bool constant;          // Constant nodes are special nodes that are evaluated at the start of the graph
    bool drawsData;         // Indicates that the node actually has a valid 'DrawData' implementation, otherwise the UI acts as if there is no data rendering 
};

typedef struct sjson_context sjson_context;
typedef struct sjson_node sjson_node;

struct NO_VTABLE NodeImpl
{
    // Initializes/allocates any internal/custom data 
    // (Node::data) member should be assigned to a valid pointer in case if the node has any custom data
    virtual bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) = 0;

    // Same as 'Initialize' but is called when we are duplicating a node
    // 'srcData' is a pointer to the source node's custom data
    virtual bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) = 0;

    // Release any custom data that was allocated in 'Initialize'
    virtual void Release(NodeGraph* graph, NodeHandle nodeHandle) = 0;

    // Executes the node. Return true if execute was successful, otherwise false. Returning false will abort the graph as well
    virtual bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) = 0;

    // Aborts the execution. This is an optional implementation. mainly used for nodes that do long processes
    virtual void Abort(NodeGraph* graph, NodeHandle nodeHandle) = 0;

    // Draw nodes internal/custom data to ImGui. 
    // Make sure to set 'drawsData' flag in 'NodeDesc' to tell the UI system that we have something to draw
    // This is used when either debugging a node, so we want to visualize the internal data.
    // Or when we just want to visualize the data. mainly useful for Periodic/triggered graphs
    virtual void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) = 0;

    // Returns any possible error messages while executing. This is only effective when 'Execute' returns false.
    // You can return nullptr if there are is no specific error description
    virtual const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) = 0;

    // Render ImGui controls to edit internal/custom data when the edit box is opened. \
    // This only works when 'editable' flag is set in 'NodeDesc'
    virtual bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) = 0;

    // Returns the title to the node. It either can return nullptr which assumes node's name is the title in UI
    // Or return a custom value for any node title
    virtual const char* GetTitleUI(NodeGraph* graph, NodeHandle nodeHandle) = 0;

    // Return the input pin description by index. Index should corrospond to 'numInPins' in 'NodeDesc'
    virtual const PinDesc& GetInputPin(uint32 index) = 0;

    // Return the output pin description by index. Index should corrospond to 'numOutPins' in 'NodeDesc'
    virtual const PinDesc& GetOutputPin(uint32 index) = 0;

    // Save/Load the internal/custom data only to json DOM format. You can do nothing if there is no custom data. built-in node properties will be handles automatically
    // 'jparent' is the root header for the node, you should put/get data only from that scope
    virtual void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) = 0;
    virtual bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) = 0;
};

struct Node
{
    SysUUID uuid;
    Array<PinHandle> inPins;
    Array<PinHandle> outPins;
    NodeDesc desc;
    NodeImpl* impl;
    void* data;
    uint32 numRuns;
    uint32 dynamicInPinIndex;
    uint32 dynamicOutPinIndex;
    TextContent* outputText;
    double runningTime;
    bool isRunning;

    bool IsFirstTimeRun() const { return numRuns == 1; }
};

struct Link
{
    PinHandle pinA;
    PinHandle pinB;
    NodeHandle nodeA;
    NodeHandle nodeB;
};

// Callbacks used for GUI syncing
struct NO_VTABLE NodeGraphEvents
{
    virtual void CreateNode(NodeHandle handle) = 0;
    virtual void CreateLink(LinkHandle handle) = 0;
    virtual void DeleteLink(LinkHandle handle) = 0;
    virtual void NodeIdle(NodeHandle handle, bool stranded) = 0;
    virtual void NodeStarted(NodeHandle handle) = 0;
    virtual void NodeFinished(NodeHandle handle, bool withError) = 0;
    virtual void LinkFinished(LinkHandle handle) = 0;
};

struct PropertyDesc
{
    const char* name;
    const char* description;
    PinDataType dataType;
};

struct NO_VTABLE PropertyImpl
{
    virtual bool Initialize(NodeGraph* graph, PropertyHandle propHandle) = 0;
    virtual void Release(NodeGraph* graph, PropertyHandle propHandle) = 0;
    virtual void ShowUI(NodeGraph* graph, PropertyHandle propHandle, float maxWidth) = 0;
    virtual bool ShowCreateUI(NodeGraph* graph, PropertyHandle propHandle, PinData& initialDataInOut) = 0;
    virtual void InitializeDataFromPin(NodeGraph* graph, PropertyHandle propHandle) = 0;
    virtual void SaveDataToJson(NodeGraph* graph, PropertyHandle propHandle, sjson_context* jctx, sjson_node* jparent) = 0;
    virtual bool LoadDataFromJson(NodeGraph* graph, PropertyHandle propHandle, sjson_context* jctx, sjson_node* jparent) = 0;
    virtual void CopyInternalData(NodeGraph* graph, PropertyHandle propHandle, const void* data) = 0;
};

struct Property
{
    SysUUID uuid;
    PropertyDesc desc;
    PinHandle pin;
    PropertyImpl* impl;
    StringId pinName;
    StringId pinDesc;
    void* data;
    bool started;
};

using NodeGraphCatName = Pair<const char*, const char*>;

API bool ngInitialize();
API void ngRelease();

API void ngRegisterNode(const NodeDesc& desc, NodeImpl* impl);
API void ngUnregisterNode(const char* name);
API Array<NodeGraphCatName> ngGetRegisteredNodes(Allocator* alloc);

API void ngRegisterProperty(const PropertyDesc& desc, PropertyImpl* impl);
API void ngUnregisterProperty(const char* name);
API Array<const char*> ngGetRegisteredProperties(Allocator* alloc);

API NodeGraph* ngCreate(Allocator* alloc, NodeGraphEvents* events = nullptr);
API void ngDestroy(NodeGraph* graph);
API bool ngLoad(NodeGraph* graph, WksFileHandle fileHandle, char* errMsg = nullptr, uint32 errMsgSize = 0);
API bool ngSave(NodeGraph* graph, WksFileHandle fileHandle = WksFileHandle());
API const char* ngGetName(NodeGraph* graph);
API WksFileHandle ngGetFileHandle(NodeGraph* graph);

API bool ngSaveNode(const char* filepath, NodeGraph* graph, NodeHandle nodeHandle);
API NodeHandle ngLoadNode(const char* filepath, NodeGraph* graph, bool genId);

API NodeHandle ngCreateNode(NodeGraph* graph, const char* name, const SysUUID* uuid = nullptr);
API void ngDestroyNode(NodeGraph* graph, NodeHandle handle);
API PinHandle ngInsertDynamicPinIntoNode(NodeGraph* graph, NodeHandle handle, PinType type, const char* name = nullptr);
API void ngRemoveDynamicPin(NodeGraph* graph, NodeHandle handle, PinType type, uint32 pinIndex);
API NodeHandle ngDuplicateNode(NodeGraph* graph, NodeHandle handle);

API LinkHandle ngCreateLink(NodeGraph* graph, PinHandle pinA, PinHandle pinB);
API void ngDestroyLink(NodeGraph* graph, LinkHandle handle);

API PropertyHandle ngCreateProperty(NodeGraph* graph, const char* name, const SysUUID* uuid = nullptr);
API bool ngStartProperty(NodeGraph* graph, PropertyHandle handle, const PinData& initialData, StringId pinName, StringId pinDescText, const void* internalData = nullptr);
API bool ngEditProperty(NodeGraph* graph, PropertyHandle handle, StringId pinName, StringId pinDescText);
API void ngDestroyProperty(NodeGraph* graph, PropertyHandle handle);

API void ngLoadPropertiesFromJson(NodeGraph* graph, sjson_node* jprops);
API bool ngLoadPropertiesFromFile(NodeGraph* graph, const char* jsonFilepath);
API void ngSavePropertiesToJson(NodeGraph* graph, sjson_context* jctx, sjson_node* jprops);
API bool ngSavePropertiesToFile(NodeGraph* graph, const char* jsonFilepath);

API bool ngExecute(NodeGraph* graph, bool debugMode = false, mco_coro* coro = nullptr, TextContent* redirectContent = nullptr,
                   TskEventHandle parentEvents = TskEventHandle());
API void ngUpdateEvents(NodeGraph* graph);
API void ngStop(NodeGraph* graph);
API const char* ngGetLastError(NodeGraph* graph);

API NodeHandle ngFindNodeById(NodeGraph* graph, SysUUID uuid);
API PropertyHandle ngFindPropertyById(NodeGraph* graph, SysUUID uuid);

API Node& ngGetNodeData(NodeGraph* graph, NodeHandle handle);
API Pin& ngGetPinData(NodeGraph* graph, PinHandle handle);
API Link& ngGetLinkData(NodeGraph* graph, LinkHandle handle);
API Property& ngGetPropertyData(NodeGraph* graph, PropertyHandle handle);
API Array<LinkHandle> ngFindLinksWithPin(NodeGraph* graph, PinHandle pinHandle, Allocator* alloc = memDefaultAlloc());
API Array<PropertyHandle> ngGetProperties(NodeGraph* graph, Allocator* alloc = memDefaultAlloc());

API NodeGraph* ngLoadChild(NodeGraph* graph, WksFileHandle childGraphFile, char* errMsg, uint32 errMsgSize, bool checkForCircularDep = false);
API void ngUnloadChild(NodeGraph* graph, WksFileHandle childGraphFile);
API bool ngHasChild(NodeGraph* graph, WksFileHandle childGraphFile);
API bool ngReloadChildNodes(NodeGraph* graph, WksFileHandle childGraphFile);

API void ngSetOutputResult(NodeGraph* graph, const PinData& pinData);
API const PinData& ngGetOutputResult(NodeGraph* graph);

API void ngSetMetaData(NodeGraph* graph, const PinData& pinData);
API const PinData& ngGetMetaData(NodeGraph* graph);

API TskGraphHandle ngGetTaskHandle(NodeGraph* graph);
API TskGraphHandle ngGetParentTaskHandle(NodeGraph* graph);
API TskEventHandle ngGetParentEventHandle(NodeGraph* graph);

