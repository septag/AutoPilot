#pragma once

#include <time.h>

#include "imgui.h"
#include "IconsFontAwesome4.h"
#include "imnodes.h"

bool imguiInitialize();
void imguiRelease();

struct Fonts
{
    ImFont* uiFont;
    ImFont* uiLargeFont;
    ImFont* monoFont;
    float uiFontSize;
    float uiLargeFontSize;
    float monoFontSize;
};

bool imguiLoadFonts(float dpiScale);
const Fonts& imguiGetFonts();
void imguiSaveState();
void imguiBeginFrame();
void imguiSetSkipItems(bool skip);

struct Docking
{
    ImGuiID main;
    ImGuiID left;
    ImGuiID right;

    ImGuiID dockIdForGraphs;
    ImGuiID dockIdForOutputs;
};

Docking& imguiGetDocking();
void imguiUnpinLeft();
void imguiPinLeft();
bool imguiBeginMainToolbar(float height);
void imguiEndMainToolbar();

template <typename F> void imguiAlign(float align, const F& f) 
{
    const ImVec2 containerSize = ImGui::GetContentRegionAvail();
    const ImVec2 cp = ImGui::GetCursorScreenPos();
    ImGuiStyle& style = ImGui::GetStyle();
    float alpha_backup = style.DisabledAlpha;
    style.DisabledAlpha = 0;
    ImGui::BeginDisabled();
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse |
        ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing |
        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoDocking;
    const char* id = "imgui_measure__";
    ImGui::Begin(id, nullptr, flags);
    imguiSetSkipItems(false);
    //
    ImGui::BeginGroup();
    f();
    ImGui::EndGroup();
    const ImVec2 size = ImGui::GetItemRectSize();
    ImGui::End();
    ImGui::EndDisabled();
    style.DisabledAlpha = alpha_backup;
    ImGui::SetCursorScreenPos(ImVec2(cp.x + (containerSize.x - size.x) * align, cp.y));
    f();
}

template <typename F> void imguiAlignRight(const F& f) { imguiAlign(1, f); }
template <typename F> void imguiAlignCenter(const F& f) { imguiAlign(0.5f, f); }

void imguiSpinnerAng(const char *label, float radius, float thickness, const ImColor &color, const ImColor &bg, float speed, float angle, int mode);

int imguiPlotDateDuration(const char* label, void (*values_getter)(void* data, int idx, float* outValue, time_t* outTm, const char** outMeta), 
                          void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, const ImVec2& size_arg);

