#include "Main.h"

#include "Core/Base.h"
#include "Core/Allocators.h"
#include "Core/System.h"
#include "Core/Jobs.h"
#include "Core/Log.h"
#include "Core/Settings.h"
#include "Core/Atomic.h"
#include "Core/IniParser.h"

#include "GuiTextView.h"
#include "GuiNodeGraph.h"
#include "GuiUtil.h"
#include "GuiWorkspace.h"
#include "GuiTasksView.h"
#include "ImGui/ImGuiAll.h"

#define STRPOOL_U64 StringId
#define STRPOOL_MALLOC(ctx, size) memAlloc(size, (Allocator*)ctx)
#define STRPOOL_FREE(ctx, ptr) memFree(ptr, (Allocator*)ctx)
#define STRPOOL_ASSERT(expr, message) ASSERT_MSG(expr, message)
#define STRPOOL_STRNICMP(s1, s2, len) (strIsEqualNoCaseCount(s1, s2, (uint32)len) ? 0 : 1)
#define STRPOOL_IMPLEMENTATION
#include "strpool.h"

#define SJSON_IMPLEMENT
#define sjson_malloc(user, size) memAlloc(size, (Allocator*)user)
#define sjson_free(user, ptr) memFree(ptr, (Allocator*)user)
#define sjson_realloc(user, ptr, size) memRealloc(ptr, size, (Allocator*)user)
#define sjson_assert(e) ASSERT(e)
#define sjson_out_of_memory() MEMORY_FAIL()
#define sjson_snprintf strPrintFmt
#include "External/sjson/sjson.h"

#include "Core/External/minicoro/minicoro.h"

struct MainSettingsCallbacks : SettingsCustomCallbacks
{
    inline static const char* kCats[] = {
        "Build",
        "Tools",
        "Layout"
    };

    enum Category 
    {
        Build = 0,
        Tool,
        Layout,
        Count
    };

    uint32 GetCategoryCount() const override;
    const char* GetCategory(uint32 id) const override;
    bool ParseSetting(uint32 categoryId, const char* key, const char* value) override;
    void SaveCategory(uint32 categoryId, Array<SettingsKeyValue>& items) override;
};

enum class SessionState : int
{
    Stopped = 0,
    Running,
    Paused
};

enum class SessionCommand : int
{
    None = 0,
    Run,
    Stop,
    Continue
};

struct RunSession
{
    Thread thread;
    GuiNodeGraph* uiGraph;
    SessionState state;
    SessionCommand cmd;
    Mutex mtx;
    Signal signal;
    bool debugMode;
    bool ret;

    bool IsRunning() { return thread.IsRunning(); }
};

struct GraphWindow
{
    GuiNodeGraph* uiGraph;
    WksFileHandle fileHandle;
    RunSession* session;
};

struct GraphEvents : GuiNodeGraphEvents
{
    void OnSaveNode(GuiNodeGraph* graph, NodeHandle nodeHandle) override;
};

struct WorkspaceEvents final : WksEvents
{
    bool OnCreateGraph(WksWorkspace* wks, WksFileHandle fileHandle) override;
    bool OnOpenGraph(WksWorkspace* wks, WksFileHandle fileHandle) override;
};

struct ShortcutItem
{
    char name[16];
    ImGuiKey keys[2];
    int modKeys;    // modifier keys, ImGuiKey combination
    ShortcutCallback callback;
    void* user;
};

struct MainContext
{
    Settings settings;
    MainSettingsCallbacks settingsCallbacks;
    strpool_t strPool;
    AtomicLock strPoolLock;
    bool strPoolInit;
    bool showDemo;

    Array<GraphWindow> graphs;
    Array<ShortcutItem> shortcuts;
    GuiWorkspace workspace;
    uint32 focusedGraphIndex = INVALID_INDEX;
    GraphEvents graphEvents;
    WorkspaceEvents workspaceEvents;
    FocusedWindow focused;
    GuiTaskView taskViewer;
    IniContext workspaceSettings;
};

static MainContext gMain;

static_assert(uint32(MainSettingsCallbacks::Category::Count) == CountOf(MainSettingsCallbacks::kCats));

static void SaveGraph(GuiNodeGraph* uiGraph);

static void LoadOrCreateWorkspaceSettings()
{
    ASSERT(gMain.workspace.mWks);
    
    Path workspaceSettingsPath = wksGetFullFolderPath(gMain.workspace.mWks, wksGetRootFolder(gMain.workspace.mWks));
    workspaceSettingsPath = Path::Join(workspaceSettingsPath, "settings.ini");
    if (!workspaceSettingsPath.IsFile()) {
        gMain.workspaceSettings = iniCreateContext();
        iniSave(gMain.workspaceSettings, workspaceSettingsPath.CStr());
    }
    else {
        gMain.workspaceSettings = iniLoad(workspaceSettingsPath.CStr());
        if (!gMain.workspaceSettings.IsValid()) {
            logError("Loading workspace settings failed: %s", workspaceSettingsPath.CStr());
        }
    }
}

static int RunGraphThread(void* userData)
{
    RunSession* session = (RunSession*)userData;
    ASSERT(session->uiGraph);

    bool r;
    if (session->debugMode) {
        mco_desc desc = mco_desc_init([](mco_coro* coro) { 
            RunSession* session = (RunSession*)mco_get_user_data(coro);
            session->ret = ngExecute(session->uiGraph->mGraph, true, coro);
        }, kMB);

        desc.malloc_cb = [](size_t size, void* allocData)->void* { return memAlloc(size, (Allocator*)allocData); };
        desc.free_cb = [](void* ptr, void* allocData) { memFree(ptr, (Allocator*)allocData); };
        desc.allocator_data = memDefaultAlloc();
        desc.user_data = session;

        mco_coro* coro;
        if (mco_create(&coro, &desc) != MCO_SUCCESS)  {
            logError("Creating coroutines failed");
            return -1;
        }

        bool firstTime = true;
        while (1) {
            
            if (!firstTime)
                session->signal.Wait();            
            firstTime = false;

            {
                MutexScope mtx(session->mtx);
                session->state = SessionState::Running;
            }

            mco_resume(coro);

            if (mco_status(coro) == MCO_DEAD) {
                mco_destroy(coro);

                MutexScope mtx(session->mtx);
                session->state = SessionState::Stopped;
                break;
            }
            else {
                MutexScope mtx(session->mtx);
                session->state = SessionState::Paused;
            }
        }

        r = session->ret;
    }
    else {
        session->state = SessionState::Running;
        r = ngExecute(session->uiGraph->mGraph);
        session->state = SessionState::Stopped;
    }
       
    logDebug("Execute finished");
    return r ? 0 : -1;
}

static RunSession* CreateRunSession(bool debugMode, GuiNodeGraph* guiGraph)
{
    RunSession* session = memAllocZeroTyped<RunSession>();
    session->uiGraph = guiGraph;
    session->debugMode = debugMode;
    session->cmd = SessionCommand::Run;
    guiGraph->mDebugMode = debugMode;
    guiGraph->mEditParams = false;
    guiGraph->mDisableEdit = true;
    session->mtx.Initialize();
    session->signal.Initialize();

    session->thread.Start(ThreadDesc {
        .entryFn = RunGraphThread,
        .userData = session,
        .name = "RunGraph"    // TODO: set the name of the graph
    });

    return session;
}

static void SendSessionCommand(RunSession* session, SessionCommand cmd)
{
    MutexScope mtx(session->mtx);
    switch (cmd) {
    case SessionCommand::Stop:
        if (session->state == SessionState::Stopped)
            return;
        break;

    case SessionCommand::Run:
        if (session->state == SessionState::Running || session->state == SessionState::Paused)
            return;
        break;

    case SessionCommand::Continue:
        if (session->state != SessionState::Paused)
            return;
        break;
    default:
        break;
    }
    session->cmd = cmd;

    if (cmd == SessionCommand::Stop)
        ngStop(session->uiGraph->mGraph);

    if (session->debugMode) {
        
        if (cmd == SessionCommand::Continue || cmd == SessionCommand::Stop) {
            session->signal.Set(1);
            session->signal.Raise();
        }            
    }
}

static int DestroyRunRussion(RunSession* session)
{
    SendSessionCommand(session, SessionCommand::Stop);

    int r = session->thread.Stop();
    session->mtx.Release();
    session->signal.Release();
    session->uiGraph->mDebugMode = false;
    session->uiGraph->mDisableEdit = false;
    memFree(session);

    return r;
}

static void ProcessShortcuts()
{
    for (const ShortcutItem& item : gMain.shortcuts) {
        int modKeys = 0;
        if (ImGui::IsKeyDown(ImGuiKey_ModAlt))
            modKeys |= ImGuiKey_ModAlt;
        if (ImGui::IsKeyDown(ImGuiKey_ModCtrl))
            modKeys |= ImGuiKey_ModCtrl;
        if (ImGui::IsKeyDown(ImGuiKey_ModShift))
            modKeys |= ImGuiKey_ModShift;

        if ((item.keys[0] && ImGui::IsKeyPressed(item.keys[0])) && 
            (item.keys[1] == 0 || (item.keys[1] && ImGui::IsKeyPressed(item.keys[1]))) &&
            (item.modKeys == 0 || item.modKeys == modKeys))
        {
            item.callback(item.user);
        }
    }
}

void SetFocusedGraph(GuiNodeGraph* uiGraph)
{
    uint32 index = gMain.graphs.FindIf([uiGraph](const GraphWindow& w) { return uiGraph == w.uiGraph; });
    if (index != INVALID_INDEX)
        gMain.focusedGraphIndex = index;
}

void DestroyNodeGraphUI(GuiNodeGraph* uiGraph)
{
    if (uiGraph) {
        uint32 index = gMain.graphs.FindIf([uiGraph](const GraphWindow& w) { return w.uiGraph == uiGraph; });
        if (index != INVALID_INDEX)  {
            if (gMain.graphs[index].session)
                DestroyRunRussion(gMain.graphs[index].session);
            gMain.graphs.Pop(index);
        }

        if (uiGraph->mGraph)
            ngDestroy(uiGraph->mGraph);

        uiGraph->Release();
        memFree(uiGraph);
    }
}

void WaitForProcessAndReadOutputText(const SysProcess& proc, Blob* outputBlob, uint32 updateIterval)
{
    char buffer[4096];
    uint32 bytesRead;

    while (proc.IsRunning()) {
        bytesRead = proc.ReadStdOut(buffer, sizeof(buffer));
        if (bytesRead == 0)
            break;

        outputBlob->Write(buffer, bytesRead);

        if (updateIterval)
            threadSleep(updateIterval);
        else
            atomicPauseCpu();            
    }

    // Read remaining pipe data if the process is exited
    while ((bytesRead = proc.ReadStdOut(buffer, sizeof(buffer))) > 0)
        outputBlob->Write(buffer, bytesRead);

    outputBlob->Write<char>('\0');
}

static Path GetSettingsFilePath()
{
    // Create cache dir if it doesn't exist
    Path cacheDir;
    pathGetCacheDir(cacheDir.Ptr(), sizeof(cacheDir), CONFIG_APP_NAME);
    if (!cacheDir.IsDir())
        pathCreateDir(cacheDir.CStr());
    return Path::Join(cacheDir, CONFIG_APP_NAME ".ini");
}

bool Initialize()
{
    settingsAddCustomCallbacks(&gMain.settingsCallbacks);
    settingsInitializeFromINI(GetSettingsFilePath().CStr());

    logSetSettings(LogLevel::Debug, false, false);
    jobsInitialize({});
    
    ngInitialize();
    tskInitialize();
    gMain.taskViewer.Initialize();

    logRegisterCallback(_private::guiLog, nullptr);

    gMain.workspace.mShowOpenWorkspaceFn = ShowOpenWorkspace;

    // TODO: debug this on mac, it fails when trying to capture the stacktrace
    // debugSetCaptureStacktraceForFiberProtector(true);

    if (!gMain.settings.layout.lastWorkspacePath.IsEmpty()) {
        gMain.workspace.mWks = wksCreate(gMain.settings.layout.lastWorkspacePath.CStr(), &gMain.workspaceEvents, memDefaultAlloc());
        if (!gMain.workspace.mWks)
            gMain.settings.layout.lastWorkspacePath = "";
        LoadOrCreateWorkspaceSettings();
    }
    else {
        // TEMP: try to open the sample workspace folder
        static const char* tryPaths[] = {
            "../../Samples",
            "../Samples",
            "Samples"
        };

        for (uint32 i = 0; i < CountOf(tryPaths); i++) {
            if (pathIsDir(tryPaths[i])) {
                gMain.workspace.mWks = wksCreate("../../Samples", &gMain.workspaceEvents, memDefaultAlloc());
                if (!gMain.workspace.mWks)
                    gMain.settings.layout.lastWorkspacePath = "";
                LoadOrCreateWorkspaceSettings();
                break;
            }
        }
    }

    RegisterShortcut("CTRL+F", [](void*) {
        switch (gMain.focused.type) {
        case FocusedWindow::Type::Workspace:
            logDebug("Workspace Search");
            break;
        case FocusedWindow::Type::Output:
            logDebug("Output Search");
            break;
        default:
            break;
        }
    }, nullptr);

    RegisterShortcut("CTRL+S", [](void*) {
        if (gMain.focusedGraphIndex != INVALID_INDEX) {
            GuiNodeGraph* uiGraph = gMain.graphs[gMain.focusedGraphIndex].uiGraph;
            SaveGraph(uiGraph);
        }
    }, nullptr);

    return true;
}

void Release()
{
    settingsSaveToINI(GetSettingsFilePath().CStr());

    for (GraphWindow& gw : gMain.graphs) {
        if (gw.uiGraph) {
            Path filepath = wksGetFullFilePath(GetWorkspace(), ngGetFileHandle(gw.uiGraph->mGraph));
            Path dir = filepath.GetDirectory();
            Path filename = filepath.GetFileName();
            ngSaveLayout(Path::Join(dir, filename).Append(".user_layout").CStr(), *gw.uiGraph, true);

            if (gw.session)
                DestroyRunRussion(gw.session);
            if (gw.uiGraph->mGraph) 
                ngDestroy(gw.uiGraph->mGraph);

            gw.uiGraph->Release();
            memFree(gw.uiGraph);
        }
    }

    gMain.graphs.Free();

    gMain.taskViewer.Release();
    ngRelease();
    tskRelease();

    jobsRelease();
    settingsRelease();

    if (gMain.strPoolInit)
        strpool_term(&gMain.strPool);
}

void ShowOpenWorkspace()
{
    guiFileDialog("Open workspace", nullptr, GuiFileDialogFlags::BrowseDirectories, [](const char* path, void* userData) {
        
        if (gMain.workspace.mWks) {
            wksDestroy(gMain.workspace.mWks);
            gMain.workspace.mSelectedFile = WksFileHandle {};
        }

        gMain.workspace.mWks = wksCreate(path, &gMain.workspaceEvents, memDefaultAlloc());
        if (gMain.workspace.mWks)
            gMain.settings.layout.lastWorkspacePath = path;
    }, nullptr);
}

static void SaveGraph(GuiNodeGraph* uiGraph)
{
    WksFileHandle fileHandle = ngGetFileHandle(uiGraph->mGraph);
    Path filepath = wksGetFullFilePath(GetWorkspace(), fileHandle);
    Path dir = filepath.GetDirectory();
    Path filename = filepath.GetFileName();

    ngSave(uiGraph->mGraph);
    ngSaveLayout(Path::Join(dir, filename).Append(".layout").CStr(), *uiGraph);

    uiGraph->mUnsavedChanges = false;

    logVerbose("Saved: %s", filepath.CStr());

    // Look through all other graphs that has this dependency and reload them
    for (GraphWindow& gw : gMain.graphs) {
        ASSERT(gw.uiGraph->mGraph);
        if (ngGetFileHandle(gw.uiGraph->mGraph) != fileHandle &&
            ngHasChild(gw.uiGraph->mGraph, fileHandle)) 
        {
            ngReloadChildNodes(gw.uiGraph->mGraph, fileHandle);
        }
    }
}

void Update()
{
    ImGuiIO& io = ImGui::GetIO();

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu(CONFIG_APP_NAME)) {
            if (ImGui::MenuItem("Save")) {
                if (gMain.focusedGraphIndex != INVALID_INDEX) {
                    GuiNodeGraph* uiGraph = gMain.graphs[gMain.focusedGraphIndex].uiGraph;
                    SaveGraph(uiGraph);
                }
            }

            if (ImGui::MenuItem("Open workspace ...")) {
                ShowOpenWorkspace();
            }

            ImGui::Separator();
            ImGui::MenuItem("Show Demo", nullptr, &gMain.showDemo);
            if (ImGui::MenuItem("About")) {
                guiMessageBox(GuiMessageBoxButtons::Ok|GuiMessageBoxButtons::Cancel, GuiMessageBoxFlags::InfoIcon, nullptr, nullptr, 
                              "AutoPilot version 0.001\nBoop Bip Beep");
            }
            ImGui::Separator();
            ImGui::MenuItem("Quit");
            ImGui::EndMenu();
        }

        
        if (gMain.workspace.mWks) {
            ImGui::SameLine(0, 30);
            ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
            ImGui::Text("[%s]", wksGetFullFolderPath(gMain.workspace.mWks, wksGetRootFolder(gMain.workspace.mWks)).CStr());
            ImGui::PopStyleColor();
        }

         // Right status bar
        imguiAlignRight([io] {
            char fps[32];
            strPrintFmt(fps, sizeof(fps), "Fps: %.1f", io.Framerate);
            ImGui::TextColored(ImGui::GetStyle().Colors[ImGuiCol_TextDisabled], fps);
        });

        ImGui::EndMainMenuBar();
    }

    // Graph execution control
    if (gMain.focusedGraphIndex != INVALID_INDEX && imguiBeginMainToolbar(35)) {
        // - Only show play button for Non-running selected graphs
        // - Show stop for any running session
        {
            GraphWindow& currentWnd = gMain.graphs[gMain.focusedGraphIndex];
            const char* name = ngGetName(currentWnd.uiGraph->mGraph);
            if (currentWnd.session == nullptr && !HasRunningSessions()) {
                if (ImGui::Button(ICON_FA_PLAY, ImVec2(32, 32))) {
                    tskSetCallbacks(ngGetTaskHandle(currentWnd.uiGraph->mGraph), &gMain.taskViewer); 

                    guiStatus(LogLevel::Info, "Running nodegraph '%s' ...", name);
                    currentWnd.uiGraph->ResetTextViews();
                    currentWnd.session = CreateRunSession(false, currentWnd.uiGraph);
                }
        
                if (ImGui::Button(ICON_FA_STEP_FORWARD, ImVec2(32, 32))) {
                    tskSetCallbacks(ngGetTaskHandle(currentWnd.uiGraph->mGraph), &gMain.taskViewer); 

                    guiStatus(LogLevel::Info, "Stepping nodegraph '%s' ...", name);
                    currentWnd.uiGraph->ResetTextViews();
                    currentWnd.session = CreateRunSession(true, currentWnd.uiGraph);
                }
            }
            else if (currentWnd.session && currentWnd.session->debugMode && currentWnd.session->state == SessionState::Paused) 
            {
                if (ImGui::Button(ICON_FA_STEP_FORWARD, ImVec2(32, 32)))
                    SendSessionCommand(currentWnd.session, SessionCommand::Continue);
            }
        }

        for (GraphWindow& w : gMain.graphs) {
            if (w.session && w.session->IsRunning()) {
                if (ImGui::Button(ICON_FA_STOP, ImVec2(32, 32))) {
                    DestroyRunRussion(w.session);
                    tskSetCallbacks(ngGetTaskHandle(w.uiGraph->mGraph), nullptr);
                    w.session = nullptr;
                }
        
                break;
            }
        }


        imguiEndMainToolbar();
    }


    if (gMain.showDemo)
        ImGui::ShowDemoWindow(&gMain.showDemo);

    gMain.taskViewer.Render("Tasks");
    gMain.workspace.Render();

    if (gMain.graphs.Count()) {
        for (uint32 i = 0; i < gMain.graphs.Count(); i++) {
            GraphWindow& w = gMain.graphs[i];
            w.uiGraph->Render();

            // cleanup finished sessions
            if (w.session && !w.session->IsRunning()) {
                DestroyRunRussion(w.session);
                tskSetCallbacks(ngGetTaskHandle(w.uiGraph->mGraph), nullptr);
                w.session = nullptr;
            }
        }
    }

    guiUpdate();

    ProcessShortcuts();
}

uint32 MainSettingsCallbacks::GetCategoryCount() const
{
    return uint32(MainSettingsCallbacks::Category::Count);
}

const char* MainSettingsCallbacks::GetCategory(uint32 id) const
{
    ASSERT(id < uint32(MainSettingsCallbacks::Category::Count));
    return MainSettingsCallbacks::kCats[id];
}

bool MainSettingsCallbacks::ParseSetting(uint32 categoryId, const char* key, const char* value)
{
    ASSERT(categoryId < uint32(MainSettingsCallbacks::Category::Count));
    switch (MainSettingsCallbacks::Category(categoryId)) {
    case MainSettingsCallbacks::Category::Tool:
        if (strIsEqualNoCase(key, "AdbPath")) {
            gMain.settings.tools.adbPath = value;
            return true;
        }
        break;
    case MainSettingsCallbacks::Category::Build:
        if (strIsEqualNoCase(key, "VisualStudioPath")) {
            gMain.settings.build.visualStudioPath = value;
            return true;
        }
        else if (strIsEqualNoCase(key, "VcVarsCmdPath")) {
            gMain.settings.build.vcVarsCmdPath = value;
            return true;
        }
        break;
    case MainSettingsCallbacks::Category::Layout:
        if (strIsEqualNoCase(key, "WindowWidth")) {
            gMain.settings.layout.windowWidth = uint16(strToInt(value));
            return true;
        }
        else if (strIsEqualNoCase(key, "WindowHeight")) {
            gMain.settings.layout.windowHeight = uint16(strToInt(value));
            return true;
        }
        else if (strIsEqualNoCase(key, "WindowX")) {
            gMain.settings.layout.windowX = uint16(strToInt(value));
            return true;
        }
        else if (strIsEqualNoCase(key, "WindowY")) {
            gMain.settings.layout.windowY = uint16(strToInt(value));
            return true;
        }
        else if (strIsEqualNoCase(key, "LastWorkspacePath")) {
            gMain.settings.layout.lastWorkspacePath = value;
        }
    default:
        break;
    }

    return false;
}

void MainSettingsCallbacks::SaveCategory(uint32 categoryId, Array<SettingsKeyValue>& items)
{
    char num[32];
    auto ToStr = [&num](int n)->const char* { strPrintFmt(num, sizeof(num), "%d", n); return num; };

    ASSERT(categoryId < uint32(MainSettingsCallbacks::Category::Count));
    switch (MainSettingsCallbacks::Category(categoryId)) {
    case MainSettingsCallbacks::Category::Tool:
        items.Push(SettingsKeyValue { "AdbPath", gMain.settings.tools.adbPath });
        break;
    case MainSettingsCallbacks::Category::Build:
        items.Push(SettingsKeyValue { "VisualStudioPath", gMain.settings.build.visualStudioPath });
        items.Push(SettingsKeyValue { "VcVarsCmdPath", gMain.settings.build.vcVarsCmdPath });
        break;
    case MainSettingsCallbacks::Category::Layout:
        items.Push(SettingsKeyValue { "WindowWidth", ToStr(gMain.settings.layout.windowWidth) });
        items.Push(SettingsKeyValue { "WindowHeight", ToStr(gMain.settings.layout.windowHeight) });
        items.Push(SettingsKeyValue { "WindowX", ToStr(gMain.settings.layout.windowX) });
        items.Push(SettingsKeyValue { "WindowY", ToStr(gMain.settings.layout.windowY) });
        items.Push(SettingsKeyValue { "LastWorkspacePath", gMain.settings.layout.lastWorkspacePath.CStr() });
        break;
    default:
        break;
    }
}

Settings& GetSettings()
{
    return gMain.settings;
}

StringId CreateString(const char* str)
{
    ASSERT(str);

    AtomicLockScope lock(gMain.strPoolLock);
    if (!gMain.strPoolInit) {
        strpool_config_t conf = strpool_default_config;
        conf.memctx = memDefaultAlloc();
        strpool_init(&gMain.strPool, &conf);
        gMain.strPoolInit = true;
    }

    StringId handle = strpool_inject(&gMain.strPool, str, strLen(str));
    strpool_incref(&gMain.strPool, handle);
    return handle;
}

void DestroyString(StringId handle)
{
    ASSERT(gMain.strPoolInit);

    if (handle) {
        AtomicLockScope lock(gMain.strPoolLock);
        int refCount = strpool_getref(&gMain.strPool, handle);
        if (refCount == 0)
            strpool_discard(&gMain.strPool, handle);
    }
}

StringId DuplicateString(StringId handle)
{
    if (handle == 0)
        return 0;
    ASSERT(gMain.strPoolInit);

    AtomicLockScope lock(gMain.strPoolLock);
    strpool_incref(&gMain.strPool, handle);
    return handle;
}

const char* GetString(StringId handle)
{
    AtomicLockScope lock(gMain.strPoolLock);
    return handle ? strpool_cstr(&gMain.strPool, handle) : "";
}

bool HasUnsavedChanges()
{
    for (GraphWindow& w : gMain.graphs) {
        if (w.uiGraph->mUnsavedChanges)
            return true;
    }
    return false;
}

bool HasRunningSessions()
{
    for (GraphWindow& w : gMain.graphs) {
        if (w.session)
            return true;
    }
    return false;
}

void QuitRequested(void(*closeCallback)())
{
    auto quitFn = [](GuiMessageBoxButtons result, void* userData) {
        if (result == GuiMessageBoxButtons::Yes) {
            for (GraphWindow& w : gMain.graphs) {
                if (w.uiGraph->mUnsavedChanges)
                    SaveGraph(w.uiGraph);
            }
        }

        if (result == GuiMessageBoxButtons::Cancel)
            return;
        else {
            using CallbackType = void(*)();
            ((CallbackType)userData)();
        }
    };

    if (HasRunningSessions()) {
        guiMessageBox(GuiMessageBoxButtons::Ok, GuiMessageBoxFlags::WarningIcon, nullptr, nullptr,
                      "Cannot close, you still have running sessions. Stop those first.");
        return;
    }

    guiMessageBox(GuiMessageBoxButtons::Yes | GuiMessageBoxButtons::No | GuiMessageBoxButtons::Cancel,
                  GuiMessageBoxFlags::WarningIcon,
                  quitFn, (void*)closeCallback,
                  "You have unsaved changes. Do you want to save all opened graphs?");

}

void GraphEvents::OnSaveNode(GuiNodeGraph* uiGraph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(uiGraph->mGraph, nodeHandle);
    const char* name = node.impl->GetTitleUI(uiGraph->mGraph, nodeHandle);
    if (!name)
        name = node.desc.name;

    WksFileHandle fileHandle = ngGetFileHandle(uiGraph->mGraph);
    Path dir = wksGetFullFilePath(GetWorkspace(), fileHandle).GetDirectory();
    ASSERT(dir.IsDir());

    Path name_(name);
    {
        strReplaceChar(name_.Ptr(), sizeof(name_), ' ', '_');
        strReplaceChar(name_.Ptr(), sizeof(name_), ':', '_');
        strReplaceChar(name_.Ptr(), sizeof(name_), ';', '_');
        strReplaceChar(name_.Ptr(), sizeof(name_), '\'', '_');
        strReplaceChar(name_.Ptr(), sizeof(name_), '\"', '_');
        strReplaceChar(name_.Ptr(), sizeof(name_), '`', '_');
        strReplaceChar(name_.Ptr(), sizeof(name_), '?', '_');
        strReplaceChar(name_.Ptr(), sizeof(name_), '/', '_');
        strReplaceChar(name_.Ptr(), sizeof(name_), ',', '_');
    }

    name_.Append(wksGetNodeExt());
    Path filepath = Path::Join(dir, name_);

    if (ngSaveNode(filepath.CStr(), uiGraph->mGraph, nodeHandle)) {
        uint32 index = gMain.graphs.FindIf([uiGraph](const GraphWindow& w) { return uiGraph == w.uiGraph; });
        if (index != INVALID_INDEX) {
            WksFolderHandle folderHandle = wksGetParentFolder(gMain.workspace.mWks, gMain.graphs[index].fileHandle);
            wksAddFileEntry(gMain.workspace.mWks, WksFileType::Node, folderHandle, name_.CStr());
        }
    }   
}

bool WorkspaceEvents::OnCreateGraph(WksWorkspace* wks, WksFileHandle fileHandle)
{
    GuiNodeGraph* uiGraph = NEW(memDefaultAlloc(), GuiNodeGraph);
    uiGraph->Initialize();
    uiGraph->mEvents = &gMain.graphEvents;

    NodeGraph* graph = ngCreate(memDefaultAlloc(), uiGraph);
    if (!ngSave(graph, fileHandle)) {
        DestroyNodeGraphUI(uiGraph);
        return false;
    }

    return true;
}

bool WorkspaceEvents::OnOpenGraph(WksWorkspace* wks, WksFileHandle fileHandle)
{
    // Prevent duplicates
    uint32 index = gMain.graphs.FindIf([fileHandle](const GraphWindow& w) { return w.fileHandle == fileHandle; });
    if (index != INVALID_INDEX) {
        gMain.graphs[index].uiGraph->mRefocus = true;
        return true;
    }

    GuiNodeGraph* uiGraph = NEW(memDefaultAlloc(), GuiNodeGraph);
    uiGraph->Initialize();
    uiGraph->mEvents = &gMain.graphEvents;

    uiGraph->mGraph = ngCreate(memDefaultAlloc(), uiGraph);
    char errorMsg[512];
    if (!ngLoad(uiGraph->mGraph, fileHandle, errorMsg, sizeof(errorMsg))) {
        logError(errorMsg);
        DestroyNodeGraphUI(uiGraph);
        return false;
    }

    Path filepath = wksGetFullFilePath(wks, fileHandle);
       
    Path dir = filepath.GetDirectory();
    Path filename = filepath.GetFileName();

    ngLoadLayout(Path::Join(dir, filename).Append(".layout").CStr(), *uiGraph);
    ngLoadLayout(Path::Join(dir, filename).Append(".user_layout").CStr(), *uiGraph);

    gMain.graphs.Push(GraphWindow { 
        .uiGraph = uiGraph, 
        .fileHandle = fileHandle 
    });

    return true;
}

WksWorkspace* GetWorkspace()
{
    return gMain.workspace.mWks;
}

// shortcut string example:
// "mod1+mod2+key1+key2+key3"
// "SHIFT+CTRL+K"
static ShortcutItem ParseShortcutKeys(const char* shortcut)
{
    shortcut = strSkipWhitespace(shortcut);

    ShortcutItem item {};
    uint32 numKeys = 0;
    const char* plus;
    char keystr[32];

    auto ParseSingleKey = [&item, &numKeys](const char* keystr) {
        uint32 len = strLen(keystr);

        bool isFn = 
            (len == 2 || len == 3) && 
            strToUpper(keystr[0]) == 'F' && 
            ((len == 2 && strIsNumber(keystr[1])) || (len == 3 && strIsNumber(keystr[1]) && strIsNumber(keystr[2])));
        if (isFn && numKeys < 2) {
            char numstr[3] = {keystr[1], keystr[2], 0};
            int fnum = strToInt(numstr) - 1;
            if (fnum >= 0 && fnum < 12)
                item.keys[numKeys++] = ImGuiKey(ImGuiKey_F1 + fnum);
        }
        else if (len > 1) {
            char modstr[32];
            strToUpper(modstr, sizeof(modstr), keystr);
            if (strIsEqual(modstr, "ALT"))
                item.modKeys |= ImGuiKey_ModAlt;
            else if (strIsEqual(modstr, "CTRL"))
                item.modKeys |= ImGuiKey_ModCtrl;
            else if (strIsEqual(modstr, "SHIFT"))
                item.modKeys |= ImGuiKey_ModShift;
        } 
        else if (len == 1 && numKeys < 2) {
            if (keystr[0] > 32) {
                switch (strToUpper(keystr[0])) {
                case '0': item.keys[numKeys++] = ImGuiKey_0; break;
                case '1': item.keys[numKeys++] = ImGuiKey_1; break;
                case '2': item.keys[numKeys++] = ImGuiKey_2; break;
                case '3': item.keys[numKeys++] = ImGuiKey_3; break;
                case '4': item.keys[numKeys++] = ImGuiKey_4; break;
                case '5': item.keys[numKeys++] = ImGuiKey_5; break;
                case '6': item.keys[numKeys++] = ImGuiKey_6; break;
                case '7': item.keys[numKeys++] = ImGuiKey_7; break;
                case '8': item.keys[numKeys++] = ImGuiKey_8; break;
                case '9': item.keys[numKeys++] = ImGuiKey_9; break;
                case 'A': item.keys[numKeys++] = ImGuiKey_A; break;
                case 'B': item.keys[numKeys++] = ImGuiKey_B; break;
                case 'C': item.keys[numKeys++] = ImGuiKey_C; break;
                case 'D': item.keys[numKeys++] = ImGuiKey_D; break;
                case 'E': item.keys[numKeys++] = ImGuiKey_E; break;
                case 'F': item.keys[numKeys++] = ImGuiKey_F; break;
                case 'G': item.keys[numKeys++] = ImGuiKey_G; break;
                case 'H': item.keys[numKeys++] = ImGuiKey_H; break;
                case 'I': item.keys[numKeys++] = ImGuiKey_I; break;
                case 'J': item.keys[numKeys++] = ImGuiKey_J; break;
                case 'K': item.keys[numKeys++] = ImGuiKey_K; break;
                case 'L': item.keys[numKeys++] = ImGuiKey_L; break;
                case 'M': item.keys[numKeys++] = ImGuiKey_M; break;
                case 'N': item.keys[numKeys++] = ImGuiKey_N; break;
                case 'O': item.keys[numKeys++] = ImGuiKey_O; break;
                case 'P': item.keys[numKeys++] = ImGuiKey_P; break;
                case 'Q': item.keys[numKeys++] = ImGuiKey_Q; break;
                case 'R': item.keys[numKeys++] = ImGuiKey_R; break;
                case 'S': item.keys[numKeys++] = ImGuiKey_S; break;
                case 'T': item.keys[numKeys++] = ImGuiKey_T; break;
                case 'U': item.keys[numKeys++] = ImGuiKey_U; break;
                case 'V': item.keys[numKeys++] = ImGuiKey_V; break;
                case 'W': item.keys[numKeys++] = ImGuiKey_W; break;
                case 'X': item.keys[numKeys++] = ImGuiKey_X; break;
                case 'Y': item.keys[numKeys++] = ImGuiKey_Y; break;
                case 'Z': item.keys[numKeys++] = ImGuiKey_Z; break;
                case '-': item.keys[numKeys++] = ImGuiKey_Minus; break;
                case '=': item.keys[numKeys++] = ImGuiKey_Equal; break;
                case '[': item.keys[numKeys++] = ImGuiKey_LeftBracket; break;
                case ']': item.keys[numKeys++] = ImGuiKey_RightBracket; break;
                case ';': item.keys[numKeys++] = ImGuiKey_Semicolon; break;
                case '\'': item.keys[numKeys++] = ImGuiKey_Apostrophe; break;
                case '`': item.keys[numKeys++] = ImGuiKey_GraveAccent; break;
                case ',': item.keys[numKeys++] = ImGuiKey_Comma; break;
                case '.': item.keys[numKeys++] = ImGuiKey_Period; break;
                case '/': item.keys[numKeys++] = ImGuiKey_Slash; break;
                case '\\': item.keys[numKeys++] = ImGuiKey_Backslash; break;
                default: break;
                }
            }
        }
    };


    while (shortcut[0]) {
        plus = strFindChar(shortcut, '+');
        if (!plus)
            break;

        strCopyCount(keystr, sizeof(keystr), shortcut, PtrToInt<uint32>((void*)(plus - shortcut)));
        ParseSingleKey(keystr);
        shortcut = strSkipWhitespace(plus + 1);
    }

    // read the last one
    if (shortcut[0]) {
        strCopy(keystr, sizeof(keystr), shortcut);
        ParseSingleKey(keystr);
    }

    return item;
}

bool RegisterShortcut(const char* shortcut, ShortcutCallback shortcutFn, void* userData)
{
    ASSERT(shortcut);
    ASSERT(shortcutFn);

    // strip whitespace and search for duplicates
    char name[32];
    if (strLen(shortcut) >= sizeof(name)) {
        ASSERT(0);
        return false;
    }

    strRemoveWhitespace(name, sizeof(name), shortcut);
    strToUpper(name, sizeof(name), name);
    for (const ShortcutItem& item : gMain.shortcuts) {
        if (strIsEqual(name, item.name)) {
            ASSERT_MSG(0, "Shortcut already registered '%s'", shortcut);
            return false;
        }
    }

    ShortcutItem item = ParseShortcutKeys(name);
    if (item.keys[0]) {
        strCopy(item.name, sizeof(item.name), name);
        item.callback = shortcutFn;
        item.user = userData;
        gMain.shortcuts.Push(item);
        return true;
    }
    else {
        return false;
    }
}

void UnregisterShortcut(const char* shortcut)
{
    char name[32];
    strRemoveWhitespace(name, sizeof(name), shortcut);
    strToUpper(name, sizeof(name), name);
    for (uint32 i = 0; i < gMain.shortcuts.Count(); i++) {
        const ShortcutItem& item = gMain.shortcuts[i];
        if (strIsEqual(name, item.name)) {
            gMain.shortcuts.RemoveAndSwap(i);
            return;
        }
    }
}

void SetFocusedWindow(const FocusedWindow& focused)
{
    gMain.focused = focused;
}

void MakeTimeFormat(float tmSecs, char* outText, uint32 textSize)
{
    if (tmSecs < 1.0f) {
        strPrintFmt(outText, textSize, "%d ms", int(tmSecs*1000.0f));
        return;
    }

    if (tmSecs < 60.0f) {
        strPrintFmt(outText, textSize, "%.1f secs", tmSecs);
        return;
    }

    if (tmSecs < 3600.0f) {
        int secs = int(tmSecs);
        strPrintFmt(outText, textSize, "%d min %d secs", secs/60, secs%60);
        return;
    }
    
    int secs = int(tmSecs);
    strPrintFmt(outText, textSize, "%d hr %d min", secs/3600, (secs%3600)/60);
}

const char* GetWorkspaceSettingByCategoryName(const char* category, const char* name)
{
    if (!gMain.workspaceSettings.IsValid())
        return nullptr;
    
    IniSection section = gMain.workspaceSettings.FindSection(category);
    if (section.IsValid()) {
        IniProperty prop = section.FindProperty(name);
        if (prop.IsValid())
            return prop.GetValue();
    }
    
    return nullptr;
}
