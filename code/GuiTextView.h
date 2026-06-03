#pragma once

struct TextSegment
{
    uint32 begin;
    uint32 end;
};

struct TextContent
{
    MemBumpAllocatorVM mAlloc;   // Allocator for the blob. we need to keep all the text persistent and do not invalidate pointers
    Blob mBlob;
    Array<TextSegment> mLines; // holds references to blob data
    SpinLockMutex mLock;
    const char* mLastLinePtr = nullptr;
    TextContent* mRedirectContent = nullptr;
    uint32 mResetFlag = 0;

    bool Initialize(size_t reserveSize = SIZE_MB*256, size_t pageSize = SIZE_KB*512);
    void Release();
    void WriteData(const void* src, size_t size);
    template <typename _T> void WriteData(const _T& v) { WriteData(&v, sizeof(v)); }
    void ParseLines();
    void Reset();
};

struct GuiTextView
{
    struct Line
    {
        uint32 lineNo;
        TextSegment text;
    };

    Array<Line> mLines;
    uint32 mLastUpdateLineCount = 0;
    float mLastUpdateContentWidth = 0;
    uint32 mEditableLine = 0;
    uint32 mEditableLineCount = 0;
    uint32 mEditableTextSize = 0;
    char* mEditableText = nullptr;
    bool mAutoScroll = true;
    bool mFirstTimeShow = false;

    void Render(TextContent* content, const char* windowId);
    ~GuiTextView();
    void Reset();
};
