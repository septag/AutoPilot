#pragma once

#include "Core/Base.h"
#include "Core/System.h"

#include "Common.h"

#define CONFIG_IMGUI_SETTINGS_FILENAME "imgui.ini"

struct GuiNodeGraph;
struct NodeGraph;
struct WksWorkspace;

struct BuildSettings
{
    Path visualStudioPath;
    Path vcVarsCmdPath;
};

struct ToolsSettings
{
    Path adbPath;
};

struct LayoutSettings
{
    Path lastWorkspacePath;
    uint16 windowWidth;
    uint16 windowHeight;
    uint16 windowX;
    uint16 windowY;    
};

struct Settings
{
    BuildSettings build;
    ToolsSettings tools;
    LayoutSettings layout;
};

struct FocusedWindow
{
    enum class Type {
        None = 0,
        Workspace,
        Output
    };

    Type type;
    void* obj;
};

bool Initialize();
void Release();
void Update();
Settings& GetSettings();

void* CreateRGBATexture(uint32 width, uint32 height, const void* data);
void  DestroyTexture(void* handle);

void SetTextViewDockId(uint32 id);
uint32 GetTextViewDockId();

struct Blob;
void WaitForProcessAndReadOutputText(const SysProcess& proc, Blob* outputBlob, uint32 updateIterval = 16);

StringId CreateString(const char* str);
StringId DuplicateString(StringId handle);
void DestroyString(StringId handle);
const char* GetString(StringId handle);
void ShowOpenWorkspace();

void DestroyNodeGraphUI(GuiNodeGraph* uiGraph);
void SetFocusedGraph(GuiNodeGraph* uiGraph);

bool HasUnsavedChanges();
bool HasRunningSessions();
void QuitRequested(void(*closeCallback)());

using ShortcutCallback = void(*)(void* userData);
bool RegisterShortcut(const char* shortcut, ShortcutCallback shortcutFn, void* userData);
void UnregisterShortcut(const char* shortcut);

void SetFocusedWindow(const FocusedWindow& focused);
WksWorkspace* GetWorkspace();

bool SetClipboardString(const char* text);
bool GetClipboardString(char* textOut, uint32 textSize);

void MakeTimeFormat(float tmSecs, char* outText, uint32 textSize);

const char* GetWorkspaceSettingByCategoryName(const char* category, const char* name);

