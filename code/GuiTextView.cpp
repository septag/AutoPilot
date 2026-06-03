#include "Core.h"

#include "GuiTextView.h"

#include "ImGui/ImGuiAll.h"

#include "Main.h"

bool TextContent::Initialize(size_t reserveSize, size_t pageSize)
{
    mAlloc.Initialize(reserveSize, pageSize);
    mBlob.SetAllocator(&mAlloc);
    mBlob.SetGrowPolicy(Blob::GrowPolicy::Linear, 32*SIZE_KB);
    return true;
}

void TextContent::Release()
{
    mBlob.Free();
    mLines.Free();
}
    
void TextContent::ParseLines()
{
    if (!mLastLinePtr)
        mLastLinePtr = (const char*)mBlob.Data();
    ASSERT(mLastLinePtr);

    const char* startPtr = (const char*)mBlob.Data();
    const char* str = mLastLinePtr;
    const char* line = str;
    while (uintptr_t(str - startPtr) < mBlob.Size()) {
        if (*str == '\n' || *str == '\0') {
            uint32 end = (uint32)uintptr_t(str - startPtr);
            if (*(str - 1) == '\r')
                --end;
            uint32 start = (uint32)uintptr_t(line - startPtr);

            SpinLockMutexScope lock(mLock);
            mLines.Push({start, end});

            if (*str == '\0')
                break;

            line = str + 1;
            mLastLinePtr = line;
        }
        ++str;
    }

    if (mRedirectContent)
        mRedirectContent->ParseLines();
}

void TextContent::WriteData(const void* src, size_t size)
{
    mBlob.Write(src, size);
    if (mRedirectContent) {
        SpinLockMutexScope redirectLock(mRedirectContent->mLock);
        mRedirectContent->mBlob.Write(src, size);
    }
}

void TextContent::Reset()
{
    mLines.Clear();
    mBlob.ResetRead();
    mBlob.SetSize(0);
    mLastLinePtr = nullptr;
    Atomic::ExchangeExplicit(&mResetFlag, 1, AtomicMemoryOrder::Release);
}

GuiTextView::~GuiTextView()
{
    mLines.Free();
    Mem::Free(mEditableText);
}

void GuiTextView::Reset()
{
    mLines.Clear();
    Mem::Free(mEditableText);
    mEditableText = nullptr;
    mLastUpdateLineCount = 0;
    mLastUpdateContentWidth = 0;
    mEditableLine = 0;
    mEditableLineCount = 0;
    mEditableTextSize = 0;
}

void GuiTextView::Render(TextContent* content, const char* windowId)
{
    auto CreateEditable = [this](const char* str, int lineIndex, uint32 lineNo) {
        if (mEditableText) {
            Mem::Free(mEditableText);
            mEditableText = nullptr;
        }

        for (int i = lineIndex; i >= 0; --i) {
            if (mLines[i].lineNo == lineNo)
                lineIndex = i;
            else 
                break;
        }

        uint32 totalTextSize = 0;
        mEditableLineCount = 0;
        for (int i = lineIndex; i < int(mLines.Count()); i++) {
            const GuiTextView::Line& line = mLines[i];
            if (line.lineNo == lineNo) {
                uint32 textSize = line.text.end - line.text.begin;
                mEditableText = Mem::ReallocTyped<char>(mEditableText, totalTextSize + textSize + 1);
                memcpy(mEditableText + totalTextSize, str + line.text.begin, textSize);
                mEditableText[totalTextSize + textSize] = '\n';
                totalTextSize += (textSize + 1);
                ++mEditableLineCount;
            }
            else {
                mEditableText = Mem::ReallocTyped<char>(mEditableText, totalTextSize + 1);
                if (totalTextSize) {
                    if (mEditableText[totalTextSize-1] == '\n')
                        mEditableText[totalTextSize-1] = 0;
                }
                mEditableText[totalTextSize] = '\0';
                break;
            }
        }

        mEditableLine = lineNo;        
        mEditableTextSize = totalTextSize;
    };

    Docking& dock = imguiGetDocking();
    if (dock.dockIdForOutputs && !mFirstTimeShow) {
        ImGui::SetNextWindowDockID(dock.dockIdForOutputs);
        mFirstTimeShow = true;
    }

    ImGui::SetNextWindowSize(ImVec2(500, 300), ImGuiCond_FirstUseEver);
    if (ImGui::Begin(windowId, nullptr, ImGuiWindowFlags_AlwaysVerticalScrollbar)) {
        bool updated = false;
        float contentWidth = ImGui::GetContentRegionAvail().x;        
        bool widgetResized = M::Abs(contentWidth - mLastUpdateContentWidth) >= 1.0f;
        bool contentChanged = mLastUpdateLineCount != content->mLines.Count();
        if ((widgetResized || contentChanged) && content->mLock.TryEnter()) 
        {
            uint32 startIndex = mLastUpdateLineCount;
            mLastUpdateLineCount = content->mLines.Count();
            mLastUpdateContentWidth = contentWidth;

            MemTempAllocator tempAlloc;
            Array<TextSegment> tempContentLines(&tempAlloc);
            content->mLines.CopyTo(&tempContentLines);
            content->mLock.Exit();
            
            AtomicUint32 kOne = 1;
            if (Atomic::CompareExchange_Weak(&content->mResetFlag, &kOne, 0) || widgetResized) {
                mLines.Clear();
                startIndex = 0;
            }

            ImFont* font = imguiGetFonts().monoFont;
            float fontScale = ImGui::GetIO().FontGlobalScale;
            const char* strPtr = (const char*)content->mBlob.Data();
        
            uint32 lineNo = startIndex + 1;
            
            for (uint32 i = startIndex; i < tempContentLines.Count(); i++) {
                const TextSegment& line = tempContentLines[i];
                uint32 beginPos = line.begin;
                while (true) {
                    const char* wrapped = font->CalcWordWrapPositionA(fontScale, strPtr + beginPos, strPtr + line.end, contentWidth);
                    uint32 wrappedPos = (uint32)uintptr_t(wrapped - strPtr);
                    mLines.Push(GuiTextView::Line {
                        .lineNo = lineNo,
                        .text = {beginPos, wrappedPos}
                    });

                    beginPos = wrappedPos;
                    if (wrappedPos == line.end)
                        break;                
                }

                lineNo++;
            }

            mAutoScroll = true;
            updated = true;
        }

        ImGui::PushFont(imguiGetFonts().monoFont);

        // TEMP: We need to be able to select multiple lines with Shift pressed
        //       We also can have a max number of lines selected like 64
        static uint32 selectedLine = 0;
        static uint32 selectedLine2 = 0;
        const char* strPtr = (const char*)content->mBlob.Data();
        char id[32];
        float lineHeight = ImGui::GetTextLineHeightWithSpacing();

        ImGuiListClipper clipper;
        clipper.Begin((int)mLines.Count());
        while (clipper.Step()) {
            for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++) {
                const GuiTextView::Line& line = mLines[i];
                Str::PrintFmt(id, sizeof(id), "##Line_%d", i);

                if (mEditableLine != line.lineNo) {
                    if (ImGui::Selectable(id, line.lineNo == selectedLine || line.lineNo == selectedLine2, ImGuiSelectableFlags_AllowDoubleClick)) {
                        if (ImGui::GetIO().KeyCtrl) {
                            if (selectedLine == 0)
                                selectedLine = line.lineNo;
                            else if (selectedLine2 == 0)
                                selectedLine2 = line.lineNo;
                        }
                        else {
                            selectedLine = 0;
                            selectedLine2 = 0;
                        }
    

                        if (ImGui::IsMouseDoubleClicked(0))
                            CreateEditable(strPtr, i, line.lineNo);
                        else
                            mEditableLine = 0;
                    }
                    ImGui::SameLine();
                    ImGui::TextUnformatted(strPtr + line.text.begin, strPtr + line.text.end);
                }
                else {
                    ASSERT(mEditableText);
                    ImGui::InputTextMultiline(id, mEditableText, mEditableTextSize,
                                              ImVec2(-1, mEditableLineCount*lineHeight + 5), 
                                              ImGuiInputTextFlags_ReadOnly|ImGuiInputTextFlags_AutoSelectAll|
                                              ImGuiInputTextFlags_NoHorizontalScroll);
                    i += mEditableLineCount - 1;
                }
            }
        }

        ImGui::PopFont();

        if (mAutoScroll)
            ImGui::SetScrollY(ImGui::GetScrollMaxY());
        if (!updated && mAutoScroll)
            mAutoScroll = false;
    }

    if (ImGui::IsWindowDocked())
        dock.dockIdForOutputs = ImGui::GetWindowDockID();
    else 
        dock.dockIdForOutputs = 0;

    if (ImGui::IsWindowFocused())
        SetFocusedWindow(FocusedWindow { .type = FocusedWindow::Type::Output, .obj = this });

    ImGui::End();
}
