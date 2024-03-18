#include "Workspace.h"

#include "Core/Log.h"

#if PLATFORM_WINDOWS
    #include "External/dirent/dirent.h"
#else
    #include <dirent.h>
#endif

#include "NodeGraph.h"
#include "GuiNodeGraph.h"

static const char kWksGraphExt[] = ".graph";
static const char kWksGraphLayoutExt[] = ".layout";
static const char kWksGraphUserLayoutExt[] = ".user_layout";
static const char kWksNodeExt[] = ".node";

struct WksFile
{
    WksFileType type;
    String<64> name;
    WksFolderHandle parentHandle;
};

struct WksFolder
{
    String<64> name;
    Array<WksFileHandle> files;
    Array<WksFolderHandle> folders;
    WksFolderHandle parentHandle;
};

struct WksWorkspace
{
    Path rootDir;
    WksFolderHandle rootHandle;
    HandlePool<WksFileHandle, WksFile> filePool;
    HandlePool<WksFolderHandle, WksFolder> folderPool;
    WksEvents* events;
};

static void wksGather(WksWorkspace* wks, const char* dirname, WksFolderHandle curHandle, bool recurse)
{
    auto SortFunc = [](const struct dirent **a, const struct dirent **b)->int {
        char extA[32];
        char extB[32];
        pathFileExtension((*a)->d_name, extA, sizeof(extA));
        pathFileExtension((*b)->d_name, extB, sizeof(extB));
        return strcmp(extA + 1, extB + 1);
    };

    dirent** entries;
    int numEntries = scandir(dirname, &entries, [](const dirent* d)->int { 
        if (d->d_type == DT_DIR && d->d_name[0] != '.')
            return 1;
        if (strEndsWith(d->d_name, kWksGraphExt) || strEndsWith(d->d_name, kWksNodeExt))
            return 1;
        return 0;
    }, SortFunc);

    if (numEntries != -1) {
        for (int i = 0; i < numEntries; i++) {
            dirent* d = entries[i];
            if (d->d_type == DT_DIR) {
                WksFolderHandle folderHandle = wks->folderPool.Add({});
                WksFolder& folder = wks->folderPool.Data(folderHandle);
                folder.name = d->d_name;
                folder.parentHandle = curHandle;

                if (recurse) {
                    Path dirPath = Path::Join(dirname, d->d_name);
                    wksGather(wks, dirPath.CStr(), folderHandle, recurse);
                }

                wks->folderPool.Data(curHandle).folders.Push(folderHandle);
            }
            else {
                WksFileType fileType = WksFileType::None;
                if (strEndsWith(d->d_name, kWksGraphExt))
                    fileType = WksFileType::Graph;
                else if (strEndsWith(d->d_name, kWksNodeExt))
                    fileType = WksFileType::Node;
                WksFileHandle fileHandle = wks->filePool.Add(WksFile { 
                    .type = fileType,
                    .name = d->d_name,
                    .parentHandle = curHandle
                });

                wks->folderPool.Data(curHandle).files.Push(fileHandle);
            }
        }
        free(entries);
    }   
}

WksFileHandle wksFindFile(WksWorkspace* wks, const char* path)
{
    ASSERT(path);

    if (*path == '/')
        ++path;
    Path unixPath(path);
    unixPath.ConvertToUnix();

    uint32 startIndex = 0;
    uint32 slashIndex = unixPath.FindChar('/');
    WksFolderHandle folderHandle = wks->rootHandle;
    while (slashIndex != INVALID_INDEX) {
        if (slashIndex != startIndex) {
            Path folderName = unixPath.SubStr(startIndex, slashIndex);
            WksFolder& folder = wks->folderPool.Data(folderHandle);
            bool found = false;
            for (WksFolderHandle childHandle : folder.folders) {
                if (wks->folderPool.Data(childHandle).name.IsEqualNoCase(folderName.CStr())) {
                    folderHandle = childHandle;
                    found = true;
                    break;
                }
            }

            if (!found)
                return WksFileHandle();
        }

        startIndex = slashIndex + 1;
        slashIndex = unixPath.FindChar('/', startIndex);
    }

    // last slash. find the file in directory
    ASSERT(folderHandle.IsValid());
    WksFolder& folder = wks->folderPool.Data(folderHandle);
    Path filename = unixPath.SubStr(startIndex);
    for (WksFileHandle fileHandle : folder.files) {
        if (filename.IsEqualNoCase(wks->filePool.Data(fileHandle).name.CStr()))
            return fileHandle;
    }
    
    return WksFileHandle();
}


WksWorkspace* wksCreate(const char* rootDir, WksEvents* events, Allocator* alloc)
{
    if (!pathIsDir(rootDir)) {
        logError("RootDir for workspace is invalid: %s", rootDir);
        return nullptr;
    }

    WksWorkspace* wks = memAllocZeroTyped<WksWorkspace>(1, alloc); 
    wks->rootDir = Path(rootDir).GetAbsolute();
    wks->filePool.SetAllocator(alloc);
    wks->folderPool.SetAllocator(alloc);
    wks->events = events;
    
    // Gather all files and folders for the root directory recursively
    WksFolderHandle folderHandle = wks->folderPool.Add({});

    // Note: this function can take siginificant amount of time if directory tree is huge
    wksGather(wks, wks->rootDir.CStr(), folderHandle, true);
    wks->rootHandle = folderHandle;

    return wks;
}

void wksDestroy(WksWorkspace* wks)
{
    if (wks) {
        for (WksFolder& folder : wks->folderPool) {
            folder.files.Free();
            folder.folders.Free();
        }

        wks->filePool.Free();
        wks->folderPool.Free();
    }
}

WksFolderHandle wksGetRootFolder(WksWorkspace* wks)
{
    return wks->rootHandle;
}

Pair<uint32, const WksFolderHandle*> wksGetFoldersUnderFolder(WksWorkspace* wks, WksFolderHandle folderHandle)
{
    WksFolder& folder = wks->folderPool.Data(folderHandle);
    return Pair<uint32, const WksFolderHandle*>(folder.folders.Count(), folder.folders.Ptr());
}

Pair<uint32, const WksFileHandle*> wksGetFilesUnderFolder(WksWorkspace* wks, WksFolderHandle folderHandle)
{
    WksFolder& folder = wks->folderPool.Data(folderHandle);
    return Pair<uint32, const WksFileHandle*>(folder.files.Count(), folder.files.Ptr());
}

const char* wksGetFolderName(WksWorkspace* wks, WksFolderHandle folderHandle)
{
    WksFolder& folder = wks->folderPool.Data(folderHandle);
    return folder.name.CStr();
}

WksFileInfo wksGetFileInfo(WksWorkspace* wks, WksFileHandle fileHandle)
{
    WksFile& file = wks->filePool.Data(fileHandle);
    return WksFileInfo {
        .name = file.name.CStr(),
        .type = file.type 
    };
}

static Path wksGetFullPath(WksWorkspace* wks, WksFolderHandle parentHandle, const char* name, bool appendRootDir = true)
{
    Path fullpath(name);
    while (parentHandle.IsValid()) {
        WksFolder& parentFolder = wks->folderPool.Data(parentHandle);
        fullpath = Path::Join(Path(parentFolder.name.CStr()), fullpath);
        parentHandle = parentFolder.parentHandle;
    }

    if (appendRootDir)
        fullpath = Path::Join(wks->rootDir, fullpath);

    return fullpath;
}

Path wksGetFullFilePath(WksWorkspace* wks, WksFileHandle fileHandle)
{
    WksFile& file = wks->filePool.Data(fileHandle);
    return wksGetFullPath(wks, file.parentHandle, file.name.CStr());
}

Path wksGetWorkspaceFilePath(WksWorkspace* wks, WksFileHandle fileHandle)
{
    WksFile& file = wks->filePool.Data(fileHandle);
    return wksGetFullPath(wks, file.parentHandle, file.name.CStr(), false);
}

Path wksGetFullFolderPath(WksWorkspace* wks, WksFolderHandle folderHandle)
{
    WksFolder& folder = wks->folderPool.Data(folderHandle);
    return wksGetFullPath(wks, folder.parentHandle, folder.name.CStr());
}

WksFolderHandle wksGetParentFolder(WksWorkspace* wks, WksFileHandle fileHandle)
{
    WksFile& file = wks->filePool.Data(fileHandle);
    return file.parentHandle;
}

bool wksRenameFile(WksWorkspace* wks, WksFileHandle fileHandle, const char* newName)
{
    WksFile& file = wks->filePool.Data(fileHandle);
    
    Path curFilepath = wksGetFullFilePath(wks, fileHandle);

    // 
    Path newFilename(newName);
    switch (file.type) {
    case WksFileType::Graph:    if (!strEndsWith(newName, kWksGraphExt)) newFilename.Append(kWksGraphExt);   break;
    case WksFileType::Node:     if (!strEndsWith(newName, kWksNodeExt)) newFilename.Append(kWksNodeExt); break;
    default:    break;
    }
    Path newFilepath = wksGetFullPath(wks, file.parentHandle, newFilename.CStr());

    bool r = pathMove(curFilepath.CStr(), newFilepath.CStr());
    if (r) {
        file.name = newFilename.CStr();

        // Rename related files too
        Path dir = newFilepath.GetDirectory();
        Path filename = newFilepath.GetFileName();
        Path newFilepathNoExt = Path::Join(dir, filename);

        dir = curFilepath.GetDirectory();
        filename = curFilepath.GetFileName();
        Path curFilepathNoExt = Path::Join(dir, filename);

        pathMove(Path(curFilepathNoExt).Append(kWksGraphLayoutExt).CStr(), Path(newFilepathNoExt).Append(kWksGraphLayoutExt).CStr());
        pathMove(Path(curFilepathNoExt).Append(kWksGraphUserLayoutExt).CStr(), Path(newFilepathNoExt).Append(kWksGraphUserLayoutExt).CStr());
    }
    return r;
}

bool wksCreateGraph(WksWorkspace* wks, WksFolderHandle folderHandle, const char* name)
{
    Path folderPath = wksGetFullFolderPath(wks, folderHandle);
    Path namePath = Path(name);
    namePath.Append(kWksGraphExt);
    Path graphPath = Path::Join(folderPath, namePath);
    if (graphPath.Exists())
        return false;

    WksFolder& folder = wks->folderPool.Data(folderHandle);
    WksFileHandle fileHandle = wks->filePool.Add(WksFile {
        .type = WksFileType::Graph,
        .name = namePath.CStr(),
        .parentHandle = folderHandle
    });

    if (wks->events) {
        if (!wks->events->OnCreateGraph(wks, fileHandle)) {
            wks->filePool.Remove(fileHandle);
            logError("Creating graph failed: %s", graphPath.CStr());
            return false;
        }
    }

    folder.files.Push(fileHandle);
    return true;
}

void wksOpenGraph(WksWorkspace* wks, WksFileHandle fileHandle)
{
    if (wks->events) {
        if (!wks->events->OnOpenGraph(wks, fileHandle)) {
            logError("Opening graph failed: %s", wksGetFullFilePath(wks, fileHandle).CStr());
        }
    }
}

const char* wksGetGraphExt()
{
    return kWksGraphExt;
}

const char* wksGetNodeExt()
{
    return kWksNodeExt;
}

WksFileHandle wksAddFileEntry(WksWorkspace* wks, WksFileType type, WksFolderHandle parentHandle, const char* filename)
{
    WksFolder& folder = wks->folderPool.Data(parentHandle);
    WksFileHandle fileHandle = wks->filePool.Add(WksFile {
        .type = type,
        .name = filename,
        .parentHandle = parentHandle
    });
    folder.files.Push(fileHandle);
    return fileHandle;
}

bool wksIsFileValid(WksWorkspace* wks, WksFileHandle fileHandle)
{
    return wks->filePool.IsValid(fileHandle);
}
