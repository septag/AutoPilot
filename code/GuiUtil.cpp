#include "GuiUtil.h"

#include <string.h>

#include "Core/MathScalar.h"
#include "Core/Log.h"
#include "Core/Atomic.h"
#include "ImGui/ImGuiAll.h"

#include "Main.h"

#include "Core/IncludeWin.h"
#include "Core/BlitSort.h"

#if PLATFORM_WINDOWS
    #include "External/dirent/dirent.h"
#else
    #include <dirent.h>
#endif

// https://github.dev/python/cpython/blob/929cc4e4a0999b777e1aa94f9c007db720e67f43/Python/suggestions.c
#define MOVE_COST 2
#define CASE_COST 0
#define LEAST_FIVE_BITS(n) ((n) & 31)
static inline int substitution_cost(char a, char b)
{
    if (LEAST_FIVE_BITS(a) != LEAST_FIVE_BITS(b)) {
        // Not the same, not a case flip.
        return MOVE_COST;
    }
    if (a == b) {
        return 0;
    }
    if ('A' <= a && a <= 'Z') {
        a += ('a' - 'A');
    }
    if ('A' <= b && b <= 'Z') {
        b += ('a' - 'A');
    }
    if (a == b) {
        return CASE_COST;
    }
    return MOVE_COST;
}

static uint32 levenshtein_distance(const char *a, uint32 aLen, uint32 aSize, const char *b, uint32 bLen)
{
    MemTempAllocator tmpAlloc;
    uint32* buffer = tmpAlloc.MallocTyped<uint32>(aSize - 1);
    uint32 maxCost = (aLen + bLen + 3) * MOVE_COST / 6;

    if (a == b)
        return 0;

    // Trim away common affixes.
    while (aLen && bLen && a[0] == b[0]) {
        a++; aLen--;
        b++; bLen--;
    }
    while (aLen && bLen && a[aLen-1] == b[bLen-1]) {
        aLen--;
        bLen--;
    }
    if (aLen == 0 || bLen == 0)
        return (aLen + bLen) * MOVE_COST;
    //if (bLen > (aSize - 1))
    //    return maxCost + 1;

    // Prefer shorter buffer
    //if (bLen < aLen) {
    //    const char *t = a; a = b; b = t;
    //    uint32 t_size = aLen; aLen = bLen; bLen = t_size;
    //}

    // quick fail when a match is impossible.
    //if ((bLen - aLen) * MOVE_COST > maxCost)
    //    return maxCost + 1;

    uint32 tmp = MOVE_COST;
    for (uint32 i = 0; i < aLen; i++) {
        buffer[i] = tmp;
        tmp += MOVE_COST;
    }

    uint32 result = 0;
    for (uint32 bIdx = 0; bIdx < bLen; bIdx++) {
        char code = b[bIdx];
        uint32 distance = result = bIdx * MOVE_COST;
        uint32 minimum = UINT32_MAX;
        for (uint32 index = 0; index < aLen; index++) {
            uint32 substitute = distance + substitution_cost(code, a[index]);
            distance = buffer[index];

            uint32 insert_delete = Min(result, distance) + MOVE_COST;
            result = Min(insert_delete, substitute);

            buffer[index] = result;
            if (result < minimum)
                minimum = result;
        }
        if (minimum > maxCost) {
            // Everything in this row is too big, so bail early.
            return maxCost + 1;
        }
    }

    uint32 minLen = Min(aLen, bLen);
    for (uint32 i = 0; i < minLen; i++) {
        if (result == 0)
            break;
        if (a[i] == b[i])
            result--;
    }

    return result;
}

static constexpr uint32 kFileDialogMaxRecents = 5;

struct GuiMessageBox
{
    char msg[4096];
    GuiMessageBoxButtons buttons;
    GuiMessageBoxFlags flags;
    void* callbackUser;
    GuiMessageBoxCallback callback;
};

struct GuiStatusBar
{
    String<1024> text;
    Color color;
    float showTime;
    AtomicLock lock;
};

struct GuiFileDialog
{
    Path path;
    GuiFileDialogFlags flags;
    Path cwd;
    const char* name;
    int selected;
    void* callbackUser;
    GuiFileDialogCallback callback;
    uint32 logicalDrivesBitMask;
    int selectedRecent;
};

struct GuiFileDialogHistory
{
    Path recents[kFileDialogMaxRecents];
    Path lastCwd;
    uint32 numRecents;
    uint32 recentStartIdx;
};

struct GuiContext
{
    GuiStatusBar statusBar;
    GuiMessageBox messageBox;
    GuiFileDialog fileDialog;
    GuiFileDialogHistory fileDialogHistory;
    bool showMessageBox;
    bool showFileDialog;
};

static GuiContext gGui;

static const char* kLogicalDrives[] = {
    "A:", "B:", "C:", "D:", "E:", "F:", "G:", "H:", "I:", 
    "J:", "K:", "L:", "M:", "N:", "O:", "P:", "Q:", "R:",
    "S:", "T:", "U:", "V:", "W:", "X:", "Y:", "Z:"
};

static void AddRecentPathToFileDialog(const Path& path)
{
    GuiFileDialogHistory& history = gGui.fileDialogHistory;

    for (uint32 i = history.recentStartIdx; i < history.numRecents; i++) {
        uint32 nextIdx = (i + 1) % history.numRecents;
        if (history.recents[i].IsEqualNoCase(path.CStr())) {
            history.recents[nextIdx] = path;
            history.recentStartIdx = (history.recentStartIdx + 1) % kFileDialogMaxRecents;
            return;
        }
    }


    uint32 lastIdx = (history.recentStartIdx + history.numRecents) % kFileDialogMaxRecents;
    history.recents[lastIdx] = path;
    uint32 numRecents = Min(history.numRecents + 1, kFileDialogMaxRecents);
    if (numRecents == history.numRecents)
        history.recentStartIdx = (history.recentStartIdx + 1) % kFileDialogMaxRecents;
    else
        history.numRecents = numRecents;
}

static void ShowMessageBox()
{
    const GuiMessageBox& box = gGui.messageBox;

    auto CloseMe = [box](GuiMessageBoxButtons button) {
        ImGui::CloseCurrentPopup();
        gGui.showMessageBox = false;
        if (box.callback) 
            box.callback(button, box.callbackUser);
    };

    //ImGui::setnextwindow
    if (ImGui::BeginPopupModal(CONFIG_APP_NAME, nullptr, ImGuiWindowFlags_AlwaysAutoResize|ImGuiWindowFlags_NoDocking|ImGuiWindowFlags_NoScrollbar)) {
        if ((box.flags & GuiMessageBoxFlags::InfoIcon) == GuiMessageBoxFlags::InfoIcon ||
             (box.flags & GuiMessageBoxFlags::WarningIcon) == GuiMessageBoxFlags::WarningIcon ||
             (box.flags & GuiMessageBoxFlags::ErrorIcon) == GuiMessageBoxFlags::ErrorIcon) 
        {
            float scale = 2.0f;
            float iconSize = scale * ImGui::GetFontSize();
            ImGui::BeginChild("MessageIcon", ImVec2(iconSize + 5, iconSize + 5), false, ImGuiWindowFlags_NoBackground);
            ImGui::SetWindowFontScale(1.5f);

            ImVec4 col;
            const char* icon = "";
            if ((GuiMessageBoxFlags::InfoIcon & box.flags) == GuiMessageBoxFlags::InfoIcon) { 
                col = ImVec4(0, 0.6f, 1.0f, 1.0f); 
                icon = ICON_FA_INFO;
            }
            else if ((GuiMessageBoxFlags::WarningIcon & box.flags) == GuiMessageBoxFlags::WarningIcon) { 
                col = ImVec4(0.9f, 1.0f, 0, 1.0f); 
                icon = ICON_FA_EXCLAMATION;
            }
            else if ((GuiMessageBoxFlags::ErrorIcon & box.flags) == GuiMessageBoxFlags::ErrorIcon) {
                col = ImVec4(1.0f, 0.1f, 0, 1.0f); 
                icon = ICON_FA_EXCLAMATION_TRIANGLE;
            }
            else {
                ASSERT_MSG(0, "Unreachable code");
            }

            ImGui::Dummy(ImVec2(2.5f, 10.0f));
            ImGui::Dummy(ImVec2(2.5f, 10.0f));
            ImGui::SameLine();
            ImGui::TextColored(col, icon);
            ImGui::EndChild();
            ImGui::SameLine();
        }

        uint32 len = strLen(box.msg);
        float width = 0;
        float height = 0;
        if (len >= 256) {
            width = 1024;
            height = 200;
        }
        else if (len >= 64) {
            width = 700;
            height = 150;
        }
        else {
            width = 500;
            height = 100;
        }
        ImGui::BeginChild("MessageText", ImVec2(width, height), true);
        ImGui::PushFont((box.flags & GuiMessageBoxFlags::SmallFont) == GuiMessageBoxFlags::SmallFont ?
                        imguiGetFonts().uiFont : imguiGetFonts().uiLargeFont);
        ImGui::TextWrapped(box.msg);
        ImGui::PopFont();
        ImGui::EndChild();

        if ((box.buttons & GuiMessageBoxButtons::Ok) == GuiMessageBoxButtons::Ok) {
            if (ImGui::Button("OK", ImVec2(120, 0)))
                CloseMe(GuiMessageBoxButtons::Ok);

            ImGui::SetItemDefaultFocus();
            ImGui::SameLine();
        }

        if ((box.buttons & GuiMessageBoxButtons::Cancel) == GuiMessageBoxButtons::Cancel) {
            if (ImGui::Button("Cancel", ImVec2(120, 0)))
                CloseMe(GuiMessageBoxButtons::Cancel);
            ImGui::SameLine();
        }

        if ((box.buttons & GuiMessageBoxButtons::Yes) == GuiMessageBoxButtons::Yes) {
            if (ImGui::Button("Yes", ImVec2(120, 0)))
                CloseMe(GuiMessageBoxButtons::Yes);
            ImGui::SameLine();
        }

        if ((box.buttons & GuiMessageBoxButtons::No) == GuiMessageBoxButtons::No) {
            if (ImGui::Button("No", ImVec2(120, 0)))
                CloseMe(GuiMessageBoxButtons::No);
            ImGui::SameLine();
        }

        ImGui::SameLine(ImGui::GetCursorPos().x + ImGui::GetContentRegionAvail().x - ImGui::GetFontSize() - ImGui::GetStyle().WindowPadding.x);

        if (ImGui::Button(ICON_FA_FILE_TEXT_O)) {
            ImGui::SetClipboardText(box.msg);
        }

        ImGui::EndPopup();
    }

    ImGui::OpenPopup(CONFIG_APP_NAME);
}

static void ShowFileDialog()
{
    GuiFileDialog& dlg = gGui.fileDialog;

    auto CloseMe = [&dlg](bool ok) {
        ImGui::CloseCurrentPopup();
        gGui.showFileDialog = false;

        if (ok) {
            dlg.path = dlg.cwd;
            gGui.fileDialogHistory.lastCwd = dlg.cwd;
            AddRecentPathToFileDialog(dlg.cwd);

            if (dlg.callback) 
                dlg.callback(dlg.path.CStr(), dlg.callbackUser);
        }
    };

    ImGui::SetNextWindowSizeConstraints(ImVec2(320, 200), ImVec2(2024, 1024));
    ImGui::SetNextWindowSize(ImVec2(830, 500), ImGuiCond_FirstUseEver);
    if (ImGui::BeginPopupModal(dlg.name, nullptr, ImGuiWindowFlags_NoDocking|ImGuiWindowFlags_NoScrollbar)) {
        // Show cwd
        ImGui::TextColored(ImVec4(0.5, 0.5, 0.5, 1.0), "Path: ");
        ImGui::SameLine();
        {
            char cwdPath[kMaxPath];
            strCopy(cwdPath, sizeof(cwdPath), dlg.cwd.CStr());
            if (ImGui::InputText("##Path", cwdPath, sizeof(cwdPath), ImGuiInputTextFlags_EnterReturnsTrue)) {
                PathInfo info = pathStat(cwdPath);
                if (info.type == PathType::Directory)
                    dlg.cwd = Path(cwdPath).GetAbsolute();
                else if (info.type == PathType::File)
                    dlg.cwd = Path(cwdPath).GetAbsolute().GetDirectory();
            }
        }
        ImGui::Separator();
        
        static_assert(CountOf(kLogicalDrives) <= 32);
        for (uint32 i = 0; i < CountOf(kLogicalDrives); i++) {
            if ((dlg.logicalDrivesBitMask >> i) & 0x1) {
                // ICON_FA_DATABASE
                if (ImGui::Button(kLogicalDrives[i])) {
                    dlg.cwd = kLogicalDrives[i];
                    dlg.cwd.Append("\\");
                }
                ImGui::SameLine();
            }
        }
        ImGui::NewLine();
        ImGui::BeginChild("Browse", ImVec2(0, -40), true, ImGuiWindowFlags_AlwaysAutoResize);

        #if 0
        {
            static char search[32];
            static const char* items[] = {
                "one",
                "two",
                "three",
                "Four",
                "five"                   
            };
            if (ImGui::InputText("Search", search, sizeof(search), ImGuiInputTextFlags_CharsNoBlank)) {
                MemTempAllocator tmpAlloc;
                Array<Pair<uint32, uint32>> dists(&tmpAlloc);
                for (uint32 i = 0; i < CountOf(items); i++) {
                    uint32 dist = levenshtein_distance(search, strLen(search), sizeof(search), items[i], strLen(items[i]));
                    dists.Push(Pair<uint32, uint32>(dist, i));
                }
                BlitSort<Pair<uint32, uint32>>(dists.Ptr(), dists.Count(), [](const Pair<uint32, uint32>& a, const Pair<uint32, uint32>& b)->int { return int(a.first) - int(b.first); });
                logDebug("Matching: ");
                for (uint32 i = 0; i < dists.Count(); i++) {
                    logDebug("\t%s (%u)", items[dists[i].second], dists[i].first);
                }
            }
        }
        #endif

        dirent** entries;
        int numEntries = scandir(dlg.cwd.CStr(), &entries, [](const dirent* d)->int { return d->d_type == DT_DIR; }, alphasort);
        if (numEntries != -1) {
            if (ImGui::IsWindowFocused() && ImGui::IsKeyPressed(ImGuiKey_Backspace)) {
                dlg.cwd = Path::Join(dlg.cwd, "..");
                dlg.cwd.ConvertToAbsolute();
                dlg.selected = 0;
            }

            for (int i = 0; i < numEntries; i++) {
                if (strIsEqual(entries[i]->d_name, "."))
                    continue;
                
                if (ImGui::Selectable(entries[i]->d_name, dlg.selected == i, ImGuiSelectableFlags_AllowDoubleClick)) {
                    dlg.selected = 0;

                    dlg.cwd = Path::Join(dlg.cwd, Path(entries[i]->d_name));
                    dlg.cwd.ConvertToAbsolute();                    
                    break;
                }
            }

            free(entries);
        }

        ImGui::EndChild();

        if (ImGui::Button("Ok", ImVec2(100, 0)))
            CloseMe(true);
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(100, 0)))
            CloseMe(false);

        GuiFileDialogHistory& history = gGui.fileDialogHistory;
        if (history.numRecents) {
            ImGui::SameLine();
            MemTempAllocator tmpAlloc;
            const char** items = tmpAlloc.MallocZeroTyped<const char*>(history.numRecents);
            for (uint32 i = 0; i < history.numRecents; i++)
                items[i] = history.recents[i].CStr();
                if (ImGui::Combo("Recents", &dlg.selectedRecent, items, int(history.numRecents))) {
                    if (history.recents[dlg.selectedRecent].IsDir())
                        dlg.cwd = history.recents[dlg.selectedRecent];
                }
        }
        

        ImGui::EndPopup();
    }

    ImGui::OpenPopup(dlg.name);    
}

void guiMessageBox(GuiMessageBoxButtons buttons, GuiMessageBoxFlags flags, GuiMessageBoxCallback callback, void* callbackUser, const char* fmt, ...)
{
    ASSERT(uint32(buttons) != 0);

    if (gGui.showMessageBox)
        return;

    GuiMessageBox& box = gGui.messageBox;

    va_list args;
    va_start(args, fmt);
    strPrintFmtArgs(box.msg, sizeof(box.msg), fmt, args);
    va_end(args);

    box.buttons = buttons;
    box.flags = flags;
    box.callback = callback;
    box.callbackUser = callbackUser;

    gGui.showMessageBox = true;
}

void guiUpdate()
{
    if (gGui.showMessageBox)
        ShowMessageBox();
    if (gGui.showFileDialog)
        ShowFileDialog();

    // Status text at the bottom
    {
        GuiStatusBar& status = gGui.statusBar;

        ImGuiStyle& style = ImGui::GetStyle();
        ImGui::PushFont(imguiGetFonts().uiLargeFont);
        const ImVec2 displaySize = ImGui::GetIO().DisplaySize;
        const float lineSize = ImGui::GetFrameHeightWithSpacing();

        AtomicLockScope lock(status.lock);
        ImDrawList* fgDrawList = ImGui::GetForegroundDrawList();
        float y = displaySize.y - lineSize;
        status.showTime += 1.0f / ImGui::GetIO().Framerate;
        float alpha = mathLinearStep(status.showTime, 0, 5.0f);
        alpha = 1.0f - mathGain(alpha, 0.05f);
        status.color.a = uint8(alpha * 255.0f);

        ImGuiViewport* viewport = ImGui::GetWindowViewport();

        fgDrawList->AddText(ImVec2(viewport->Pos.x + style.WindowPadding.x, viewport->Pos.y + y), status.color.n, status.text.CStr());
        ImGui::PopFont();
    }

}

void guiStatus(LogLevel level, const char* fmt, ...)
{
    GuiStatusBar& status = gGui.statusBar;

    AtomicLockScope lock(status.lock);

    va_list args;
    va_start(args, fmt);
    strPrintFmtArgs(status.text.Ptr(), sizeof(status.text), fmt, args);
    va_end(args);

    switch (level) {
    case LogLevel::Info:	status.color = kColorWhite; break;
    case LogLevel::Debug:	status.color = Color(0, 200, 200); break;
    case LogLevel::Verbose:	status.color = Color(128, 128, 128); break;
    case LogLevel::Warning:	status.color = kColorYellow; break;
    case LogLevel::Error:	status.color = kColorRed; break;
    default:			    status.color = kColorWhite; break;
    }

    status.showTime = 0;
}

void guiFileDialog(const char* name, const char* cwd, GuiFileDialogFlags flags, GuiFileDialogCallback callback, void* callbackUser)
{
    ASSERT_MSG((flags & GuiFileDialogFlags::BrowseDirectories) == GuiFileDialogFlags::BrowseDirectories, "");
    GuiFileDialog& dlg = gGui.fileDialog;

    if (cwd == nullptr || cwd[0] == 0 || !pathIsDir(cwd)) {
        if (!gGui.fileDialogHistory.lastCwd.IsEmpty() && gGui.fileDialogHistory.lastCwd.IsDir()) 
            cwd = gGui.fileDialogHistory.lastCwd.CStr();
        else
            cwd = ".";
    }

    dlg.name = name;
    dlg.flags = flags;
    dlg.cwd = Path(cwd).GetAbsolute();
    dlg.path = dlg.cwd;
    dlg.callback = callback;
    dlg.callbackUser = callbackUser;
    
    #if PLATFORM_WINDOWS
        dlg.logicalDrivesBitMask = GetLogicalDrives();
    #endif
    
    gGui.showFileDialog = true;
    gGui.fileDialogHistory.lastCwd = dlg.cwd;
}

void _private::guiLog(const LogEntry& entry, void*)
{
    guiStatus(entry.type, entry.text);
}
