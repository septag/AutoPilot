#include "GuiWorkspace.h"

#include "Core/Log.h"

#include "ImGui/ImGuiAll.h"

#include "Main.h"

bool guiShowFolderItem(GuiWorkspace& uiWks, WksFolderHandle curHandle, bool indent)
{
    if (indent)
        ImGui::Indent();
    Pair<uint32, const WksFileHandle*> files = wksGetFilesUnderFolder(uiWks.mWks, curHandle);
    Pair<uint32, const WksFolderHandle*> folders = wksGetFoldersUnderFolder(uiWks.mWks, curHandle);

    if (uiWks.mCreateFileFolder == curHandle) {
        ImGui::SetKeyboardFocusHere();
        if (ImGui::InputText("##Create", uiWks.mCurFilename, sizeof(uiWks.mCurFilename), ImGuiInputTextFlags_CharsNoBlank|ImGuiInputTextFlags_EnterReturnsTrue)) {
            if (uiWks.mCurFilename[0] != 0 && wksCreateGraph(uiWks.mWks, uiWks.mCreateFileFolder, uiWks.mCurFilename)) {
                uiWks.mCreateFileFolder = WksFolderHandle();
            }
            else {
                logError("Cannot create file '%s'. Invalid name or File already exists", uiWks.mCurFilename);
            }
        }
        if (ImGui::IsKeyPressed(ImGuiKey_Escape)) 
            uiWks.mCreateFileFolder = WksFolderHandle();
    }

    bool isAnyHovered = false;
    for (uint32 i = 0; i < folders.first; i++) {
        WksFolderHandle folderHandle = folders.second[i];
        const char* folderName = wksGetFolderName(uiWks.mWks, folderHandle);

        ImGuiTreeNodeFlags treeNodeFlags = folderHandle == uiWks.mCreateFileFolder ? ImGuiTreeNodeFlags_DefaultOpen : 0;
        bool folderOpened = ImGui::CollapsingHeader(folderName, nullptr, treeNodeFlags);
        if (ImGui::IsItemHovered())  {
            uiWks.mHoveredFolder = folderHandle;
            isAnyHovered = true;
        }
        if (!uiWks.mIsFileHovered)
            ImGui::OpenPopupOnItemClick("WksFolderContextMenu", ImGuiPopupFlags_MouseButtonRight);
        if (folderOpened)
            isAnyHovered |= guiShowFolderItem(uiWks, folderHandle, true);
    }

    for (uint32 i = 0; i < files.first; i++) {
        WksFileHandle fileHandle = files.second[i];
        WksFileInfo fileInfo = wksGetFileInfo(uiWks.mWks, fileHandle);

        if (uiWks.mRenameMode && uiWks.mHoveredFile == fileHandle) {
            ImGui::SetKeyboardFocusHere();
            if (ImGui::InputText("##Rename", uiWks.mCurFilename, sizeof(uiWks.mCurFilename), ImGuiInputTextFlags_CharsNoBlank|ImGuiInputTextFlags_EnterReturnsTrue)) {
                if (uiWks.mCurFilename[0] != 0 && wksRenameFile(uiWks.mWks, fileHandle, uiWks.mCurFilename)) {
                    uiWks.mRenameMode = false;
                }
                else {
                    logError("Cannot rename to '%s'. Invalid name or File already exists", uiWks.mCurFilename);
                }
            }
            if (ImGui::IsKeyPressed(ImGuiKey_Escape)) 
                uiWks.mRenameMode = false;
        }
        else {
            char label[255];
            const char* icon = "";
            if (fileInfo.type == WksFileType::Graph)
                icon = ICON_FA_CUBES;
            else if (fileInfo.type == WksFileType::Node)
                icon = ICON_FA_CUBE;
            strPrintFmt(label, sizeof(label), "%s %s", icon, fileInfo.name);
            if (ImGui::Selectable(label, uiWks.mSelectedFile == fileHandle, ImGuiSelectableFlags_AllowDoubleClick)) {
                uiWks.mSelectedFile = fileHandle;
                if (fileInfo.type == WksFileType::Graph)
                    wksOpenGraph(uiWks.mWks, fileHandle);
            }
        }

        if (fileInfo.type == WksFileType::Node || fileInfo.type == WksFileType::Graph) {
            if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                const char* ddName = fileInfo.type == WksFileType::Node ? "NodeFileDD" : "GraphFileDD";
                const char* ddIcon = fileInfo.type == WksFileType::Node ? ICON_FA_CUBE : ICON_FA_CUBES;
                ImGui::SetDragDropPayload(ddName, &fileHandle, sizeof(fileHandle));
                ImGui::Text("%s %s", ddIcon, fileInfo.name);
                ImGui::EndDragDropSource();
            }
        }
        if (!uiWks.mRenameMode) {
            uiWks.mIsFileHovered = ImGui::IsItemHovered();        
            if (uiWks.mIsFileHovered) {
                isAnyHovered = true;
                uiWks.mHoveredFile = fileHandle;
            }
        }
        ImGui::OpenPopupOnItemClick("WksFileContextMenu", ImGuiPopupFlags_MouseButtonRight);      
    }

    if (indent)
        ImGui::Unindent();

    return isAnyHovered;
}

void GuiWorkspace::Render()
{
    if (imguiGetDocking().left) {
        ImGui::SetNextWindowDockID(imguiGetDocking().left);
        imguiGetDocking().left = 0;
    }

    if (ImGui::Begin("Workspace")) {
        if (mWks && ImGui::BeginChild("Browser")) {
            // Context menu items
            {
                ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0, 0, 0, 1.0f));
                if (ImGui::BeginPopupContextItem("WksFolderContextMenu"))
                {
                    // ImGui::Text("Folder: %s", wksGetFolderName(wks, hoveredFolder));
                    if (ImGui::MenuItem("Add Graph")) {
                        mCurFilename[0] = '\0';
                        mCreateFileFolder = mHoveredFolder;
                    }
                    ImGui::EndPopup();
                }
        
                if (ImGui::BeginPopupContextItem("WksFileContextMenu"))
                {
                    WksFileInfo info = wksGetFileInfo(mWks, mHoveredFile);
                    if (ImGui::MenuItem("Rename")) {
                        strCopy(mCurFilename, sizeof(mCurFilename), info.name);
                        pathFileName(mCurFilename, mCurFilename, sizeof(mCurFilename));
                        mRenameMode = true;
                    }
        
                    ImGui::EndPopup();
                }
                ImGui::PopStyleColor();
            }

            WksFolderHandle rootHandle = wksGetRootFolder(mWks);
            bool isAnyItemHovered = guiShowFolderItem(*this, rootHandle, false);

            if (mShowEmptyAreaContext) {
                mHoveredFolder = wksGetRootFolder(mWks);
                ImGui::OpenPopup("WksFolderContextMenu");
                mShowEmptyAreaContext = false;
            }

            ImGui::EndChild();

            if (ImGui::IsItemHovered() && !isAnyItemHovered && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
                mShowEmptyAreaContext = true;
            }
        }
        else {
            if (ImGui::Button("Open workspace", ImVec2(-1, 0))) {
                if (mShowOpenWorkspaceFn)
                    mShowOpenWorkspaceFn();
            }
        }
    }

    if (ImGui::IsWindowFocused())
        SetFocusedWindow(FocusedWindow { .type = FocusedWindow::Type::Workspace, .obj = this });

    ImGui::End();
}



