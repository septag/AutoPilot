#pragma once

#include "Core/Base.h"

enum class LogLevel;
struct LogEntry;

enum class GuiMessageBoxButtons : uint32 
{
    None = 0x0,
    Ok = 0x1,
    Cancel = 0x2,
    Yes = 0x4,
    No = 0x8
};
ENABLE_BITMASK(GuiMessageBoxButtons);

enum class GuiMessageBoxFlags
{
    None = 0,
    InfoIcon = 0x1,
    ErrorIcon = 0x2,
    WarningIcon = 0x4,
    SmallFont = 0x8
};
ENABLE_BITMASK(GuiMessageBoxFlags);

enum class GuiFileDialogFlags
{
    None = 0,
    BrowseDirectories = 0x1
};
ENABLE_BITMASK(GuiFileDialogFlags);

using GuiMessageBoxCallback = void(*)(GuiMessageBoxButtons result, void* userData);
using GuiFileDialogCallback = void(*)(const char* path, void* userData);

void guiMessageBox(GuiMessageBoxButtons buttons, GuiMessageBoxFlags flags, GuiMessageBoxCallback callback, void* callbackUser,
                   const char* fmt, ...);

void guiFileDialog(const char* name, const char* cwd, GuiFileDialogFlags flags, GuiFileDialogCallback callback, void* callbackUser);

void guiUpdate();

void guiStatus(LogLevel level, const char* fmt, ...);

namespace _private
{
    void guiLog(const LogEntry& entry, void*);
}