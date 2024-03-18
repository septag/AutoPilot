#include "TaskMan.h"

#include "Main.h"
#include "NodeGraph.h"
#include "Workspace.h"

#include "Core/Log.h"

#include "External/sjson/sjson.h"

#include <time.h>

struct TskEventItem
{
    StringId text;
    TskEventType::Enum type;
};

struct TskEvent
{
    String<256> title;
    uint64 startTm;
    float duration;
    time_t tm;
    TskGraphHandle parentGraphHandle;
    TskEventHandle parentEventHandle;
    TskEventHandle tmpEvent;
    Array<TskEventItem> items;
};

struct TskGraph
{
    String<256> name;
    WksFileHandle graphFileHandle;
    uint32 refCount;
    HandlePool<TskEventHandle, TskEvent> events;
    Array<TskSummary> history;
    TskCallbacks* callbacks;
    TskEventHandle mainEvent;

    uint64_t startTmHires;
    time_t startTm;
    bool inExecute;
};

struct TskContext
{
    HandlePool<TskGraphHandle, TskGraph> graphs;
    Mutex graphsMutex;
};

static TskContext gTsk;

TskEventType::Enum TskEventType::FromString(const char* estr)
{     
    for (uint32 i = 0; i < _Count; i++) {
        if (strIsEqual(estr, mStrs[i]))
        return (Enum)i;
    }
    ASSERT(0);
    return _Count;
}

bool tskInitialize()
{
    gTsk.graphsMutex.Initialize();
    
    return true;
}

void tskRelease()
{
    gTsk.graphsMutex.Release();

    for (TskGraph& tsk : gTsk.graphs) {
        for (TskEvent& ev : tsk.events)
            ev.items.Free();
        tsk.events.Free();
        tsk.history.Free();
    }
    gTsk.graphs.Free();
}

const char* tskGetName(TskGraphHandle handle)
{
    MutexScope mtx(gTsk.graphsMutex);
    TskGraph& graphTask = gTsk.graphs.Data(handle);
    
    return graphTask.name.CStr();
}

static inline Path tskGetTaskFilePath(WksFileHandle graphFileHandle)
{
    Path graphFilepath = wksGetFullFilePath(GetWorkspace(), graphFileHandle);
    Path taskFilepath = Path::Join(graphFilepath.GetDirectory(), graphFilepath.GetFileName());
    taskFilepath.Append(".task");
    return taskFilepath;
}

TskGraphHandle tskLoadGraphTask(WksFileHandle graphFileHandle)
{
    Path filepath = tskGetTaskFilePath(graphFileHandle);
    MutexScope mtx(gTsk.graphsMutex);
    for (uint32 i = 0; i < gTsk.graphs.Count(); i++) {
        TskGraphHandle handle = gTsk.graphs.HandleAt(i);
        TskGraph& graphTask = gTsk.graphs.Data(handle);
        if (graphTask.graphFileHandle == graphFileHandle) {
            ++graphTask.refCount;
            return handle;
        }
    }

    TskGraphHandle handle = gTsk.graphs.Add({
        .name = filepath.GetFileName().CStr(),
        .graphFileHandle = graphFileHandle,
        .refCount = 1
    });
    
    File f;
    if (!f.Open(filepath.CStr(), FileOpenFlags::Read | FileOpenFlags::SeqScan) || f.GetSize() == 0)
        return handle;
    
    TskGraph& taskGraph = gTsk.graphs.Data(handle);
    MemTempAllocator tmpAlloc;
    size_t fileSize = f.GetSize();
    char* jsonText = (char*)tmpAlloc.Malloc(fileSize + 1);
    f.Read<char>(jsonText, (uint32)fileSize);
    jsonText[fileSize] = '\0';
    f.Close();

    sjson_context* jctx = sjson_create_context(0, 0, &tmpAlloc);
    ASSERT_ALWAYS(jctx, "Out of memory?");
    sjson_node* jroot = sjson_decode(jctx, jsonText);
    if (!jroot) {
        logWarning("Parsing json failed: %s", filepath.CStr());
        return handle;
    }

    sjson_node* jevents = sjson_find_member(jroot, "Events");
    if (jevents) {
        sjson_node* jevent = sjson_first_child(jevents);
        while (jevent) {
            TskEventHandle eventHandle = taskGraph.events.Add(TskEvent {
                .title = sjson_get_string(jevent, "Title", ""),
                .duration = sjson_get_float(jevent, "Duration", 0),
                .tm = static_cast<time_t>(sjson_get_int64(jevent, "Time", 0))
            });
            TskEvent& event = taskGraph.events.Data(eventHandle);

            sjson_node* jitems = sjson_find_member(jevent, "Items");
            if (jitems) {
                sjson_node* jitem = sjson_first_child(jitems);
                while (jitem) {
                    event.items.Push(TskEventItem {
                        .text = CreateString(sjson_get_string(jitem, "Text", "")),
                        .type = TskEventType::FromString(sjson_get_string(jitem, "Type", ""))
                    });
                    jitem = jitem->next;
                }
            }

            jevent = jevent->next;
        }
    }

    sjson_node* jhistory = sjson_find_member(jroot, "History");
    if (jhistory) {
        sjson_node* jsummary = sjson_first_child(jhistory);
        while (jsummary) {
            taskGraph.history.Push(TskSummary {
                .duration = sjson_get_float(jsummary, "Duration", 0),
                .startTm = sjson_get_int64(jsummary, "StartTime", 0),
                .metaData = sjson_get_string(jsummary, "MetaData", "")
            });
            jsummary = jsummary->next;
        }
    }

    sjson_destroy_context(jctx);
    return handle;
}

bool tskSaveGraphTask(TskGraphHandle handle)
{
    MutexScope mtx(gTsk.graphsMutex);
    TskGraph& graphTask = gTsk.graphs.Data(handle);
    Path filepath = tskGetTaskFilePath(graphTask.graphFileHandle);

    MemTempAllocator tmpAlloc;
    sjson_context* jctx = sjson_create_context(0, 0, &tmpAlloc);
    ASSERT_ALWAYS(jctx, "Out of memory?");
    sjson_node* jroot = sjson_mkobject(jctx);

    sjson_node* jevents = sjson_put_array(jctx, jroot, "Events");
    for (TskEvent& event : graphTask.events) {
        sjson_node* jevent = sjson_mkobject(jctx);
        sjson_put_string(jctx, jevent, "Title", event.title.CStr());
        sjson_put_float(jctx, jevent, "Duration", event.duration);
        sjson_put_int64(jctx, jevent, "Time", static_cast<int64>(event.tm));

        if (event.items.Count()) {
            sjson_node* jitems = sjson_put_array(jctx, jevent, "Items");
            for (TskEventItem& item : event.items) {
                sjson_node* jitem = sjson_mkobject(jctx);
                sjson_put_string(jctx, jitem, "Text", GetString(item.text));
                sjson_put_string(jctx, jitem, "Type", TskEventType::ToString(item.type));
                sjson_append_element(jitems, jitem);
            }
        }

        sjson_append_element(jevents, jevent);
    }

    sjson_node* jhistory = sjson_put_array(jctx, jroot, "History");
    for (TskSummary& summary : graphTask.history) {
        sjson_node* jsummary = sjson_mkobject(jctx);
        sjson_put_float(jctx, jsummary, "Duration", summary.duration);
        sjson_put_int64(jctx, jsummary, "StartTime", summary.startTm);
        sjson_put_string(jctx, jsummary, "MetaData", summary.metaData.CStr());

        sjson_append_element(jhistory, jsummary);
    }

    char* jsonText = sjson_stringify(jctx, jroot, "\t");
    File f;
    if (!f.Open(filepath.CStr(), FileOpenFlags::Write)) {
        logError("Cannot open file for writing: %s", filepath.CStr());
        return false;
    }

    f.Write(jsonText, strLen(jsonText));
    f.Close();

    sjson_free_string(jctx, jsonText);
    sjson_destroy_context(jctx);
    return true;
}

void tskDestroyTask(TskGraphHandle handle)
{
    MutexScope mtx(gTsk.graphsMutex);
    TskGraph& graphTask = gTsk.graphs.Data(handle);
    --graphTask.refCount;
    if (graphTask.refCount == 0) {
        graphTask.events.Free();
        gTsk.graphs.Remove(handle);
    }
}

TskEventHandle tskBeginEvent(TskGraphHandle graphHandle, const char* name, TskGraphHandle redirectGraph, TskEventHandle redirectEvents)
{
    MutexScope mtx(gTsk.graphsMutex);
    TskGraph& graphTask = gTsk.graphs.Data(graphHandle);
    
    TskEventHandle eventHandle = graphTask.events.Add(TskEvent {
        .title = name,
        .startTm = timerGetTicks(),
        .tm = time(nullptr),
        .parentGraphHandle = redirectGraph,
        .parentEventHandle = redirectEvents
    });

    TskEvent& event = graphTask.events.Data(eventHandle);
    if (graphTask.callbacks) 
        graphTask.callbacks->OnBeginEvent(graphHandle, eventHandle, event.title.CStr(), event.tm);
        
    if (redirectGraph.IsValid() && redirectEvents.IsValid()) {
        ASSERT(redirectGraph != graphHandle);
        TskGraph& rGraph = gTsk.graphs.Data(redirectGraph);
        TskEvent& rEvent = rGraph.events.Data(redirectEvents);
        ASSERT(!rEvent.tmpEvent.IsValid());
        TskEventHandle tmpEvent = tskBeginEvent(redirectGraph, name, rEvent.parentGraphHandle, rEvent.parentEventHandle);

        // NOTE: we cannot use the old reference to the event, since the buffer might get resized and we get a new pointer
        rGraph.events.Data(redirectEvents).tmpEvent = tmpEvent;
    }
    
    return eventHandle;
}

void tskEndEvent(TskGraphHandle graphHandle, TskEventHandle eventHandle)
{
    MutexScope mtx(gTsk.graphsMutex);
    TskGraph& graphTask = gTsk.graphs.Data(graphHandle);
        
    TskEvent& event = graphTask.events.Data(eventHandle);
    event.duration = (float)timerToSec(timerDiff(timerGetTicks(), event.startTm));

    if (graphTask.callbacks)
        graphTask.callbacks->OnEndEvent(graphHandle, eventHandle, event.duration);
    
    if (event.parentGraphHandle.IsValid() && event.parentEventHandle.IsValid()) {
        ASSERT(event.parentGraphHandle != graphHandle);
        TskGraph& rGraph = gTsk.graphs.Data(event.parentGraphHandle);
        TskEvent& rEvent = rGraph.events.Data(event.parentEventHandle);
        ASSERT(rEvent.tmpEvent.IsValid());  // See tskBeginEvent redirection
        
        tskEndEvent(event.parentGraphHandle, rEvent.tmpEvent);
        rEvent.tmpEvent = TskEventHandle();
    }
}

void tskPushEvent(TskGraphHandle graphHandle, TskEventHandle eventHandle, TskEventType::Enum type, const char* text)
{
    ASSERT(text);
    
    MutexScope mtx(gTsk.graphsMutex);
    TskGraph& graphTask = gTsk.graphs.Data(graphHandle);
    
    TskEvent& event = graphTask.events.Data(eventHandle);
    TskEventItem item {
        .text = CreateString(text),
        .type = type
    };
    event.items.Push(item);

    if (graphTask.callbacks)
        graphTask.callbacks->OnNewEvent(graphHandle, eventHandle, type, text);

    if (event.parentGraphHandle.IsValid() && event.parentEventHandle.IsValid()) {
        ASSERT(event.parentGraphHandle != graphHandle);
        TskGraph& rGraph = gTsk.graphs.Data(event.parentGraphHandle);
        TskEvent& rEvent = rGraph.events.Data(event.parentEventHandle);
        ASSERT(rEvent.tmpEvent.IsValid());  // See tskBeginEvent redirection
        
        tskPushEvent(event.parentGraphHandle, rEvent.tmpEvent, type, text);
    }
}

void TskEventScope::SuccessFmt(const char* fmt, ...)
{
    MemTempAllocator tmpAlloc;
    va_list args;
    va_start(args, fmt);
    char* text = strPrintFmtAllocArgs(&tmpAlloc, fmt, args);
    va_end(args);

    tskPushEvent(mGraphHandle, mHandle, TskEventType::Success, text);
    mResultSet = true;
}

void TskEventScope::ErrorFmt(const char* fmt, ...)
{
    MemTempAllocator tmpAlloc;
    va_list args;
    va_start(args, fmt);
    char* text = strPrintFmtAllocArgs(&tmpAlloc, fmt, args);
    va_end(args);

    tskPushEvent(mGraphHandle, mHandle, TskEventType::Error, text);
    mResultSet = true;
}

void TskEventScope::InfoFmt(const char* fmt, ...)
{
    MemTempAllocator tmpAlloc;
    va_list args;
    va_start(args, fmt);
    char* text = strPrintFmtAllocArgs(&tmpAlloc, fmt, args);
    va_end(args);

    tskPushEvent(mGraphHandle, mHandle, TskEventType::Info, text);
}

void tskSetCallbacks(TskGraphHandle graphHandle, TskCallbacks* callbacks)
{
    MutexScope mtx(gTsk.graphsMutex);
    TskGraph& graphTask = gTsk.graphs.Data(graphHandle);
    
    graphTask.callbacks = callbacks;
}

void tskBeginGraphExecute(TskGraphHandle graphHandle, TskGraphHandle redirectGraph, TskEventHandle redirectEvents)
{
    MutexScope mtx(gTsk.graphsMutex);
    TskGraph& graphTask = gTsk.graphs.Data(graphHandle);

    ASSERT_MSG(!graphTask.inExecute, "Graph is still in the middle of execution, finish it first");
    graphTask.inExecute = true;
    graphTask.startTmHires = timerGetTicks();
    graphTask.startTm = time(nullptr);

    ASSERT(!graphTask.mainEvent.IsValid());
    graphTask.mainEvent = tskBeginEvent(graphHandle, "Run");
}

void tskEndGraphExecute(TskGraphHandle graphHandle, const char* metaData, bool withError)
{
    MutexScope mtx(gTsk.graphsMutex);
    TskGraph& graphTask = gTsk.graphs.Data(graphHandle);

    // TODO: for now, we skip saving the history if task fails. Might want to change this behavior later
    if (!withError) {
        graphTask.history.Push(TskSummary {
            .duration = (float)timerToSec(timerDiff(timerGetTicks(), graphTask.startTmHires)),
            .startTm = graphTask.startTm,
            .metaData = metaData ? metaData : ""
        });    
    }

    ASSERT(graphTask.mainEvent.IsValid());
    tskPushEvent(graphHandle, graphTask.mainEvent, withError ? TskEventType::Error : TskEventType::Success, "");
    tskEndEvent(graphHandle, graphTask.mainEvent);
    graphTask.mainEvent = TskEventHandle();
    graphTask.inExecute = false;
}

Span<TskSummary> tskGetHistory(TskGraphHandle graphHandle, Allocator* alloc)
{
    MutexScope mtx(gTsk.graphsMutex);
    TskGraph& graphTask = gTsk.graphs.Data(graphHandle);

    if (graphTask.history.Count()) {
        TskSummary* summary = memAllocCopy<TskSummary>(graphTask.history.Ptr(), graphTask.history.Count(), alloc);
        return Span<TskSummary>(summary, graphTask.history.Count());
    }
    else {
        return Span<TskSummary>();
    }
}

WksFileHandle tskGetFileHandle(TskGraphHandle graphHandle)
{
    MutexScope mtx(gTsk.graphsMutex);
    TskGraph& graphTask = gTsk.graphs.Data(graphHandle);
    return graphTask.graphFileHandle;
}

void tskClearHistory(TskGraphHandle graphHandle)
{
    MutexScope mtx(gTsk.graphsMutex);
    TskGraph& graphTask = gTsk.graphs.Data(graphHandle);
    graphTask.history.Clear();
}