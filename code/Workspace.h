#pragma once

#include "Core/System.h"

#include "Common.h"

struct WksWorkspace;
struct NodeGraph;

enum class WksFileType
{
    None = 0,
    Graph,
    Node
};

struct WksFileInfo
{
    const char* name;
    WksFileType type;
};

struct NO_VTABLE WksEvents
{
    virtual bool OnCreateGraph(WksWorkspace* wks, WksFileHandle fileHandle) = 0;
    virtual bool OnOpenGraph(WksWorkspace* wks, WksFileHandle fileHandle) = 0;
};

API WksWorkspace* wksCreate(const char* rootDir, WksEvents* events, Allocator* alloc);
API void wksDestroy(WksWorkspace* wks);

API WksFolderHandle wksGetRootFolder(WksWorkspace* wks);
API Pair<uint32, const WksFolderHandle*> wksGetFoldersUnderFolder(WksWorkspace* wks, WksFolderHandle folderHandle);
API Pair<uint32, const WksFileHandle*> wksGetFilesUnderFolder(WksWorkspace* wks, WksFolderHandle folderHandle);

API const char* wksGetFolderName(WksWorkspace* wks, WksFolderHandle folderHandle);
API WksFileInfo wksGetFileInfo(WksWorkspace* wks, WksFileHandle fileHandle);
API WksFolderHandle wksGetParentFolder(WksWorkspace* wks, WksFileHandle fileHandle);
API Path wksGetFullFilePath(WksWorkspace* wks, WksFileHandle fileHandle);
API Path wksGetWorkspaceFilePath(WksWorkspace* wks, WksFileHandle fileHandle);
API Path wksGetFullFolderPath(WksWorkspace* wks, WksFolderHandle folderHandle);
API bool wksIsFileValid(WksWorkspace* wks, WksFileHandle fileHandle);
API bool wksRenameFile(WksWorkspace* wks, WksFileHandle fileHandle, const char* newName);
API bool wksCreateGraph(WksWorkspace* wks, WksFolderHandle folderHandle, const char* name);
API WksFileHandle wksFindFile(WksWorkspace* wks, const char* path);

API const char* wksGetGraphExt();
API const char* wksGetNodeExt();

API void wksOpenGraph(WksWorkspace* wks, WksFileHandle fileHandle);
API WksFileHandle wksAddFileEntry(WksWorkspace* wks, WksFileType type, WksFolderHandle parentHandle, const char* filename);


