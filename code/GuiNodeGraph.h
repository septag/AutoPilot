#pragma once

#include "NodeGraph.h"
#include "ImGui/ImGuiAll.h"

struct GuiTextView;
struct GuiNodeGraph;

struct GuiNodeGraphNode
{
    NodeHandle handle;
    ImVec2 pos;
    float width;
    GuiTextView* textView;
    float hourglassTime;
    int hourglassIndex;
    bool editInPins;
    bool editOutPins;
    bool refocusOutput;
    bool setPos;

    enum class State
    {
        Idle = 0,
        Stranded,
        Started,
        Failed,
        Success
    };

    State state;
};

struct GuiNodeGraphLink
{
    LinkHandle handle;
    bool finished;
};

enum class GuiNodeGraphContextMenu
{
    None = 0,
    EmptyArea,
    Node
};

struct GuiNodeGraphEvents
{
    virtual void OnSaveNode(GuiNodeGraph* uiGraph, NodeHandle nodeHandle) = 0;
};

struct GuiNodeGraph final : NodeGraphEvents
{
    ImNodesContext* mCtx = nullptr;
    ImNodesEditorContext* mEditorCtx = nullptr;
    NodeGraph* mGraph = nullptr;
    Array<GuiNodeGraphNode> mNodes;
    Array<GuiNodeGraphLink> mLinks;
    Array<NodeHandle> mSelectedNodes;
    ImVec2 mContextMenuPos = ImVec2(0, 0);
    GuiNodeGraphContextMenu mContextMenu = GuiNodeGraphContextMenu::None;
    int mParamsNode = -2;
    float mParamsNodeMaxWidth = 150.0f;
    int mSelectedNode = -1;
    float mParamsNodeWidth = 0;
    ImVec2 mParamsNodePos = ImVec2(0, 0);
    ImVec2 mPan = ImVec2(0, 0);
    NodeHandle mDebugNodeHandle = {};
    bool mEditParams = false;
    bool mDebugMode = false;
    bool mDisableEdit = false;
    bool mFirstTimeShow = false;
    bool mRefocus = false;
    bool mContextMenuMousePosSet = false;
    bool mShowMiniMap = false;
    bool mUnsavedChanges = false;
    const char* mToggleModal = nullptr;
    void* mModalData = nullptr;
    PinHandle mEditingPinHandle;
    char mEditingPinName[64];
    GuiNodeGraphEvents* mEvents = nullptr;

    // This is triggered on implicit deletion of links (ngDestroyNode)
    void CreateNode(NodeHandle handle) override;
    void CreateLink(LinkHandle handle) override;
    void DeleteLink(LinkHandle handle) override;
    void NodeIdle(NodeHandle handle, bool stranded) override;
    void NodeStarted(NodeHandle handle) override;
    void NodeFinished(NodeHandle handle, bool withError) override;
    void LinkFinished(LinkHandle handle) override;
    
    void ResetTextViews();
    void ResetStates();
    void Render();
    
    void Initialize();
    void Release();
};

bool ngSaveLayout(const char* filepath, const GuiNodeGraph& uigraph, bool savePropertyValues = false);
bool ngLoadLayout(const char* filepath, GuiNodeGraph& uigraph);

