#include "GuiTasksView.h"

#include "ImGui/ImGuiAll.h"

#include "Core/System.h"
#include "Core/Log.h"
#include "Core/MathTypes.h"

#include "Main.h"
#include "Workspace.h"

struct GuiTaskViewData
{
    enum class ItemState
    {
        None = 0,
        Running,
        Finished,
        Failed
    };

    struct Item
    {
        char* text;
        uint32 textLen;
        ItemState state;
        TskGraphHandle graphHandle;
        TskEventHandle eventHandle;
        Item* firstChild;
        Item* next;
    };

    Mutex mutex;
    Array<Item*> items;
    MemBumpAllocatorVM alloc;
    Item** itemsCopy = nullptr;
    uint32 numItems = 0;
    bool dataChanged = false;
    Item* selectedItem = nullptr;
    Item* hoveredItem = nullptr;
    bool hoveredItemIsChild = false;
    bool showOverview = false;
};

static void RenderGraphOverview(TskGraphHandle graphHandle)
{
    auto CloseModal = []() {
        ImGui::CloseCurrentPopup();
    };

    MemTempAllocator tmpAlloc;
    ImGui::SetNextWindowSizeConstraints(ImVec2(450, 300), ImVec2(1024, 1024));
    if (ImGui::BeginPopupModal("TaskOverview")) {
        Span<TskSummary> history = tskGetHistory(graphHandle, &tmpAlloc);

        Path graphPath = wksGetWorkspaceFilePath(GetWorkspace(), tskGetFileHandle(graphHandle));
        ImGui::LabelText("##GraphPath", graphPath.CStr());

        auto PlotGetter = [](void* data, int index, float* outValue, time_t* outTm, const char** outMeta)
        {
            Span<TskSummary>* history = (Span<TskSummary>*)data;
            const TskSummary& summary = (*history)[index];
            *outValue = summary.duration;
            *outTm = summary.startTm;
            *outMeta = summary.metaData.CStr();
        };

        ImGui::Separator();
        if (history.Count()) {
            imguiPlotDateDuration("##TaskTimes", PlotGetter, &history, history.Count(), 0, nullptr, FLT_MAX, FLT_MAX, ImVec2(-1, 120));
            imguiAlignRight([graphHandle]() { if (ImGui::Button("Clear")) { tskClearHistory(graphHandle); }});
        }
        else {
            ImGui::TextUnformatted("[No history available]");
        }

        ImGui::Separator();
        if (ImGui::Button("OK", ImVec2(120, 0)))
            CloseModal();

        ImGui::EndPopup();
    }
}

void GuiTaskView::Render(const char* windowId)
{
    if (!mData)
        return;

    if (mData->dataChanged && mData->mutex.TryEnter()) {
        mData->itemsCopy = memReallocTyped<GuiTaskViewData::Item*>(mData->itemsCopy, mData->items.Count());
        memcpy(mData->itemsCopy, mData->items.Ptr(), mData->items.Count()*sizeof(GuiTaskViewData::Item*));
        mData->numItems = mData->items.Count();
        mData->dataChanged = false;
        mData->mutex.Exit();
    }

    char spinnerId[32];
    ImGui::SetNextWindowSizeConstraints(ImVec2(450, 300), ImVec2(1024, 1024));
    if (ImGui::Begin(windowId, nullptr, ImGuiWindowFlags_HorizontalScrollbar)) {

        {
            if (mData->hoveredItem && mData->hoveredItem->graphHandle.IsValid())
                RenderGraphOverview(mData->hoveredItem->graphHandle);

            if (mData->showOverview) {
                ImGui::OpenPopup("TaskOverview");
                mData->showOverview = false;
            }

            ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0, 0, 0, 1.0f));
            if (ImGui::BeginPopupContextItem("TaskEventContextMenu"))
            {
                ASSERT(mData->hoveredItem);

                if (!mData->hoveredItemIsChild) {
                    char overviewText[256];
                    strPrintFmt(overviewText, sizeof(overviewText), "Overview \"%s\"", tskGetName(mData->hoveredItem->graphHandle));
                    if (ImGui::MenuItem(overviewText)) {
                        mData->showOverview = true;
                    }
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Copy text")) {
                    SetClipboardString(mData->hoveredItem->text);
                    logInfo("Item copied to clipboard");
                }

                ImGui::EndPopup();
            }
            ImGui::PopStyleColor();
        }   

        for (uint32 i = 0; i < mData->numItems; i++) {
            GuiTaskViewData::Item* item = mData->itemsCopy[i];

            ImGuiTreeNodeFlags flags = item->firstChild ? 0 : ImGuiTreeNodeFlags_Leaf;

            if (item->state == GuiTaskViewData::ItemState::Running) {
                strPrintFmt(spinnerId, sizeof(spinnerId), "spinner_%u", i);
                imguiSpinnerAng(spinnerId, 5.5f, 4.0f, ImColor(0, 200, 0), ImColor(255, 255, 255, 0), 6.0f, 0.75f*kPI2, 0);
            }
            else if (item->state == GuiTaskViewData::ItemState::Finished) {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0.8f, 0, 1.0f));
                ImGui::TextUnformatted(ICON_FA_CHECK);
                ImGui::PopStyleColor();
            }
            else if (item->state == GuiTaskViewData::ItemState::Failed) {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0, 0, 1.0f));
                ImGui::TextUnformatted(ICON_FA_EXCLAMATION_TRIANGLE);
                ImGui::PopStyleColor();
            }

            ImGui::SameLine();
            ImGui::PushID(int(i));
            bool anySubItemHovered = false;
            if (ImGui::TreeNodeEx(item->text, flags)) {
                item = item->firstChild;
                while (item) {
                    bool selected = item == mData->selectedItem;
                    ImGui::Dummy(ImVec2(32, 0));
                    ImGui::SameLine();
                    if (ImGui::Selectable(item->text, &selected, ImGuiSelectableFlags_AllowDoubleClick)) {
                        mData->selectedItem = item;
                        if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
                            SetClipboardString(item->text);
                            logInfo("Item copied to clipboard");
                        }
                    }

                    if (ImGui::IsItemHovered()) {
                        anySubItemHovered = true;
                        mData->hoveredItem = item;
                        mData->hoveredItemIsChild = true;
                    }

                    item = item->next;
                }
                ImGui::TreePop();
            }
            ImGui::PopID();

            if (ImGui::IsItemHovered() || anySubItemHovered) {
                if (!anySubItemHovered) {
                    mData->hoveredItem = mData->itemsCopy[i];
                    mData->hoveredItemIsChild = false;
                }
                if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
                    ImGui::OpenPopup("TaskEventContextMenu");
                }
            }
        }
    }
    ImGui::End();
}

void GuiTaskView::Reset()
{
    MutexScope mutex(mData->mutex);
    mData->items.Clear();
}

bool GuiTaskView::Initialize()
{
    mData = NEW(memDefaultAlloc(), GuiTaskViewData);
    mData->alloc.Initialize(512*kMB, 64*kKB);
    mData->mutex.Initialize();
    mData->selectedItem = nullptr;

    return true;
}

void GuiTaskView::Release()
{
    if (mData) {
        mData->mutex.Release();
        mData->alloc.Release();
        mData->items.Free();
        memFree(mData);
        mData = nullptr;
    }
}

void GuiTaskView::OnBeginEvent(TskGraphHandle graphHandle, TskEventHandle eventHandle, const char* name, time_t startTm)
{
    const char* graphName = tskGetName(graphHandle);
    uint32 textLen = strLen(name) + strLen(graphName) + 2 /* ": " */ + 64 /* duration */;
    MemSingleShotMalloc<GuiTaskViewData::Item> mallocator;

    // No need to Free, because we will free the VM allocator itself
    GuiTaskViewData::Item* item = mallocator.AddMemberField<char>(offsetof(GuiTaskViewData::Item, text), textLen + 1).Calloc(&mData->alloc);
    strPrintFmt(item->text, textLen + 1, "%s: %s", graphName, name);
    item->textLen = textLen + 1;
    item->state = GuiTaskViewData::ItemState::Running;
    item->graphHandle = graphHandle;
    item->eventHandle = eventHandle;

    MutexScope mutex(mData->mutex);
    mData->items.Push(item);
    mData->dataChanged = true;
}

void GuiTaskView::OnEndEvent(TskGraphHandle graphHandle, TskEventHandle eventHandle, float duration)
{
    MutexScope mutex(mData->mutex);

    GuiTaskViewData::Item* parentItem = nullptr;
    for (uint32 i = mData->items.Count(); i-- > 0; ) {
        GuiTaskViewData::Item* item = mData->items[i];
        if (item->graphHandle == graphHandle && item->eventHandle == eventHandle) {
            parentItem = item;
            break;
        }
    }

    ASSERT(parentItem);

    char durstr[64];
    MakeTimeFormat(duration, durstr, sizeof(durstr));
    strConcat(parentItem->text, parentItem->textLen, " - ");
    strConcat(parentItem->text, parentItem->textLen, durstr);
}

void GuiTaskView::OnNewEvent(TskGraphHandle graphHandle, TskEventHandle eventHandle, TskEventType::Enum type, const char* text)
{
    MutexScope mutex(mData->mutex);

    GuiTaskViewData::Item* parentItem = nullptr;
    for (uint32 i = mData->items.Count(); i-- > 0; ) {
        GuiTaskViewData::Item* item = mData->items[i];
        if (item->graphHandle == graphHandle && item->eventHandle == eventHandle) {
            parentItem = item;
            break;
        }
    }

    ASSERT(parentItem);
    switch (type) {
    case TskEventType::Success:  parentItem->state = GuiTaskViewData::ItemState::Finished;    break;
    case TskEventType::Error:    parentItem->state = GuiTaskViewData::ItemState::Failed;      break;
    default:    break;
    }
    
    if (text[0]) {
        uint32 textLen = strLen(text);
        MemSingleShotMalloc<GuiTaskViewData::Item> mallocator;

        // No need for free, allocating from VM allocator
        GuiTaskViewData::Item* item = mallocator.AddMemberField<char>(offsetof(GuiTaskViewData::Item, text), textLen + 1).Calloc(&mData->alloc);
        memcpy(item->text, text, textLen);
        item->text[textLen] = '\0';

        if (parentItem->firstChild == nullptr) {
            parentItem->firstChild = item;
        }
        else {
            GuiTaskViewData::Item* last = parentItem->firstChild;
            while (last->next)
                last = last->next;
            last->next = item;
        }
    }
}

