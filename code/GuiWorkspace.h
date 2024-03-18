#pragma once

#include "Workspace.h"

struct GuiWorkspace
{
    WksWorkspace* mWks;
    WksFileHandle mSelectedFile;
    bool mIsFileHovered;
    WksFileHandle mHoveredFile;
    WksFolderHandle mHoveredFolder;
    WksFolderHandle mCreateFileFolder;
    bool mRenameMode;
    bool mShowEmptyAreaContext;
    char mCurFilename[64];
    void(*mShowOpenWorkspaceFn)();

    void Render();
};


