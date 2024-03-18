#pragma once

#include "Common.h"
#include "TaskMan.h"

#include <time.h>

struct GuiTaskViewData;

struct GuiTaskView final : TskCallbacks
{
    GuiTaskViewData* mData = nullptr;
    
    void Reset();
    void Render(const char* windowId);

    bool Initialize();
    void Release();

    void OnBeginEvent(TskGraphHandle graphHandle, TskEventHandle eventHandle, const char* name, time_t startTm) override;
    void OnEndEvent(TskGraphHandle graphHandle, TskEventHandle eventHandle, float duration) override;
    void OnNewEvent(TskGraphHandle graphHandle, TskEventHandle eventHandle, TskEventType::Enum type, const char* text) override;
};

