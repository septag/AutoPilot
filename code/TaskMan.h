#pragma once

#include "Core/StringUtil.h"
#include "Common.h"
#include <time.h>

struct NodeGraph;

struct TskEventType
{
    enum Enum {
        Success = 0,
        Error,
        Info,
        _Count
    };

    static inline const char* mStrs[_Count] = {
        "Success",
        "Error",
        "Info"
    };

    static const char* ToString(Enum e) { return mStrs[uint32(e)]; }
    static Enum FromString(const char* estr); 
};

struct TskSummary
{
    float duration;
    time_t startTm;
    String<256> metaData;
};

struct NO_VTABLE TskCallbacks
{
    virtual void OnBeginEvent(TskGraphHandle graphHandle, TskEventHandle eventHandle, const char* name, time_t startTm) = 0;
    virtual void OnEndEvent(TskGraphHandle graphHandle, TskEventHandle eventHandle, float duration) = 0;
    virtual void OnNewEvent(TskGraphHandle graphHandle, TskEventHandle eventHandle, TskEventType::Enum type, const char* text) = 0;
};

bool tskInitialize();
void tskRelease();
void tskSetCallbacks(TskGraphHandle handle, TskCallbacks* callbacks);

TskGraphHandle ngGetTaskHandle(NodeGraph* graph);
TskGraphHandle ngGetParentTaskHandle(NodeGraph* graph);
TskEventHandle ngGetParentEventHandle(NodeGraph* graph);

// do not reload task if it's already loaded (refcount > 1)
// Returns an empty Task object, if the file does not exist
TskGraphHandle tskLoadGraphTask(WksFileHandle graphFileHandle);
bool tskSaveGraphTask(TskGraphHandle handle);

void tskDestroyTask(TskGraphHandle handle); // TODO: must be refcounted (we might have multiple/embedded graphs opened)

TskEventHandle tskBeginEvent(TskGraphHandle graphHandle, const char* name,
                             TskGraphHandle redirectGraph = TskGraphHandle(), TskEventHandle redirectEvents = TskEventHandle());
void tskEndEvent(TskGraphHandle graphHandle, TskEventHandle eventHandle);
void tskPushEvent(TskGraphHandle handle, TskEventHandle eventHandle, TskEventType::Enum type, const char* text);

const char* tskGetName(TskGraphHandle handle);

struct TskEventScope
{
    TskEventScope(NodeGraph* graph, const char* name)
    {
        ASSERT(graph);
        mGraphHandle = ngGetTaskHandle(graph);
        mHandle = tskBeginEvent(mGraphHandle, name, ngGetParentTaskHandle(graph), ngGetParentEventHandle(graph));
        mResultSet = false;
    }
    
    ~TskEventScope() 
    {
        if (!mResultSet)
            Success();

        tskEndEvent(mGraphHandle, mHandle);
    }
    
    void Success(const char* extraMessage = nullptr)
    {
        tskPushEvent(mGraphHandle, mHandle, TskEventType::Success, extraMessage ? extraMessage : "");
        mResultSet = true;
    }
    
    void Error(const char* errorMsg)
    {
        tskPushEvent(mGraphHandle, mHandle, TskEventType::Error, errorMsg);
        mResultSet = true;
    }

    void Info(const char* text)
    {
        tskPushEvent(mGraphHandle, mHandle, TskEventType::Info, text);
    }

    void SuccessFmt(const char* fmt, ...);
    void ErrorFmt(const char* fmt, ...);
    void InfoFmt(const char* fmt, ...);
    
    TskGraphHandle mGraphHandle;
    TskEventHandle mHandle;
    bool mResultSet;
};

void tskBeginGraphExecute(TskGraphHandle graphHandle, TskGraphHandle redirectGraph = TskGraphHandle(), 
                          TskEventHandle redirectEvents = TskEventHandle());
void tskEndGraphExecute(TskGraphHandle graphHandle, const char* metaData, bool withError = false);

WksFileHandle tskGetFileHandle(TskGraphHandle graphHandle);
Span<TskSummary> tskGetHistory(TskGraphHandle graphHandle, Allocator* alloc);
void tskClearHistory(TskGraphHandle graphHandle);