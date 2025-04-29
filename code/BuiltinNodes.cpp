#include "BuiltinNodes.h"

#include "External/sjson/sjson.h"

#if PLATFORM_WINDOWS
#include "External/dirent/dirent.h"
#else
#include <dirent.h>
#endif

#include "Core/Log.h"
#include "Core/System.h"
#include "Core/Settings.h"

#include "ImGui/ImGuiAll.h"
#include "GuiUtil.h"
#include "TaskMan.h"
#include "Main.h"
#include "GuiTextView.h"
#include "Workspace.h"

void RegisterBuiltinNodes()
{
    Node_DebugMessage::Register();
    Node_UpperCase::Register();
    Node_LowerCase::Register();
    Node_CreateProcess::Register();
    Node_JoinString::Register();
    Node_JoinStringArray::Register();
    Node_SplitString::Register();
    Node_SplitPath::Register();
    Node_IsFile::Register();
    Node_IsDir::Register();
    Node_CompareString::Register();
    Node_StringConstant::Register();
    Node_IntConstant::Register();
    Node_BoolIf::Register();
    Node_BoolNegate::Register();
    Node_Selector::Register();
    Node_MathCounter::Register();
    Node_Constants::Register();
    Node_EmbedGraph::Register();
    Node_FormatString::Register();
    Node_GraphOutput::Register();
    Node_GraphMetaData::Register();
    Node_ListDir::Register();
    Node_TranslateString::Register();
    Node_SetEnvVar::Register();
    Node_GetEnvVar::Register();
    Node_GetSettingsVar::Register();
    
    #if PLATFORM_WINDOWS
    Node_ShellExecute::Register();
    #endif
}

static bool ParseFormatText(Blob* bufferOut, const char* text, NodeGraph* graph, const Array<PinHandle>& pins, 
                            char* errorStr, uint32 errorStrSize,
                            const char* prependStr = nullptr)
{
    auto FindVar = [graph, pins](const char* name)->const char* {
        for (uint32 i = 0; i < pins.Count(); i++) {
            PinHandle pinHandle = pins[i];
            Pin& pin = ngGetPinData(graph, pinHandle);
            const char* pinName = pin.dynName ? GetString(pin.dynName) : pin.desc.name;
            if (strIsEqualNoCase(name, pinName))
                return pin.ready ? pin.data.str : nullptr;
        }

        return nullptr;
    };

    auto FindNextCloseBracket = [](const char* str)->const char* {
        int bracketDepth = 0;
        while (*str != 0) {
            if (*str == '}') {
                if (bracketDepth == 0) 
                    return str;
                else 
                    bracketDepth--;
            }
            else if (*str == '{') {
                bracketDepth++;
            }
            str++;
        }
        return nullptr;
    };


    Blob& blob = *bufferOut;
    const char* str = text;
    const char* c = str;
    const char* cropStart = c;
    char varName[64];
    size_t dummySize;

    if (prependStr) 
        blob.Write(prependStr, strLen(prependStr));

    // Preprocess pass #1: Include or get rid of ?{} sections (optional)
    while (*c != 0) {
        if (*c == '?' && *(c + 1) && *(c + 1) == '{') {
            const char* closeBracket = FindNextCloseBracket(c + 2);
            if (!closeBracket || closeBracket == (c + 2)) {
                strPrintFmt(errorStr, errorStrSize, "Parsing command failed at: %s", c);
                return false;
            }

            const char* colon = strFindChar(c + 2, ':');
            if (colon == nullptr || colon > closeBracket) {
                strPrintFmt(errorStr, errorStrSize, "Parsing command failed at: %s", c);
                return false;
            }

            strCopyCount(varName, sizeof(varName), c + 2, PtrToInt<uint32>((void*)(colon - c - 2)));
            if (c > cropStart)
                blob.Write(cropStart, PtrToInt<uint32>((void*)(c - cropStart)));

            const char* var = FindVar(varName);
            if (var != nullptr && var[0] && !strIsEqual(var, "0")) {
                if (closeBracket > colon + 1)
                    blob.Write(colon + 1, PtrToInt<uint32>((void*)(closeBracket - colon - 1)));
            }

            c = closeBracket;
            cropStart = c + 1;
        }
        c++;
    }
    if (c > cropStart)
        blob.Write(cropStart, strLen(cropStart));
    blob.Write<char>('\0');
    blob.Detach((void**)const_cast<char**>(&c), &dummySize);
    cropStart = c;

    // Preprocess pass #2: Replace variables 
    while (*c != 0) {
        if (*c == '$' && *(c + 1) && *(c + 1) == '{') {
            const char* closeBracket = FindNextCloseBracket(c + 2);
            if (!closeBracket || closeBracket == (c + 2)) {
                strPrintFmt(errorStr, errorStrSize, "Parsing command failed at: %s", c);
                return false;
            }

            if (c > cropStart)
                blob.Write(cropStart, PtrToInt<uint32>((void*)(c - cropStart)));
            
            strCopyCount(varName, sizeof(varName), c + 2, PtrToInt<uint32>((void*)(closeBracket - c - 2)));
            const char* var = FindVar(varName);
            if (!var) {
                strPrintFmt(errorStr, errorStrSize, "Parsing command failed. Variable not found or invalid: %s", varName);
                return false;
            }
            blob.Write(var, strLen(var));

            c = closeBracket;
            cropStart = c + 1;
        }

        c++;
    }
    if (c > cropStart)
        blob.Write(cropStart, strLen(cropStart));
    blob.Write<char>('\0');

    return true;
}

//----------------------------------------------------------------------------------------------------------------------
// Node_DebugMessage
bool Node_DebugMessage::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Pin& textPin = ngGetPinData(graph, inPins[0]);
    ASSERT(textPin.ready);
    logInfo(textPin.data.str);
    return true;
}

void Node_DebugMessage::Register()
{
    static Node_DebugMessage self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
// Node_UpperCase
bool Node_UpperCase::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Pin& textPin = ngGetPinData(graph, inPins[0]);
    Pin& outputPin = ngGetPinData(graph, outPins[0]);
    
    ASSERT(textPin.ready);
    strToUpper(textPin.data.str, uint32(textPin.data.size) + 1, textPin.data.str);
    outputPin.data.SetString(textPin.data.str, uint32(textPin.data.size));

    outputPin.ready = true;

    return true;
}

void Node_UpperCase::Register()
{
    static Node_UpperCase self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
// Node_LowerCase
bool Node_LowerCase::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Pin& textPin = ngGetPinData(graph, inPins[0]);
    Pin& outputPin = ngGetPinData(graph, outPins[0]);
    
    ASSERT(textPin.ready);
    strToLower(textPin.data.str, uint32(textPin.data.size) + 1, textPin.data.str);
    outputPin.data.SetString(textPin.data.str, uint32(textPin.data.size));

    outputPin.ready = true;

    return true;
}

void Node_LowerCase::Register()
{
    static Node_LowerCase self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
// Node_RunCommand
bool Node_CreateProcess::Initialize(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Node_CreateProcess::Data>();
    node.data = data;

    strCopy(data->title, sizeof(data->title), node.desc.name);
    strCopy(data->executeCmd, sizeof(data->executeCmd), "${Command} ${Arg1}");
    data->checkRetCode = true;
    data->fatalErrorOnFail = true;
    data->cmdTextInputWidth = 550;
    data->runInCmd = false;
    return true;
}

bool Node_CreateProcess::InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Node_CreateProcess::Data>();
    node.data = data;

    Data* copyData = (Data*)srcData;
    strCopy(data->title, sizeof(data->title), copyData->title);
    strCopy(data->executeCmd, sizeof(data->executeCmd), copyData->executeCmd);
    data->fatalErrorOnFail = copyData->fatalErrorOnFail;
    data->checkRetCode = copyData->checkRetCode;
    data->successRetCode = copyData->successRetCode;
    data->cmdTextInputWidth = copyData->cmdTextInputWidth;
    data->runInCmd = copyData->runInCmd;
    
    return true;
}

void Node_CreateProcess::Release(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    memFree(node.data);
}

bool Node_CreateProcess::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    // Parse and generate the final command string
    MemTempAllocator tmpAlloc;
    Blob blob(&tmpAlloc);
    blob.SetGrowPolicy(Blob::GrowPolicy::Linear);

    const char* prependCmd = nullptr;
    #if PLATFORM_WINDOWS
    if (data->runInCmd)
        prependCmd = "cmd /c ";
    #endif

    if (!ParseFormatText(&blob, data->executeCmd, graph, inPins, data->errorStr, sizeof(data->errorStr), prependCmd))
        return false;

    TskEventScope event(graph, GetTitleUI(graph, nodeHandle));

    const char* cmd = (const char*)blob.Data();
    Pin& cwdPin = ngGetPinData(graph, inPins[2]);
    const char* cwd = cwdPin.ready ? cwdPin.data.str : nullptr;

    size_t startOffset;
    TextContent* output = node.outputText;
    if (node.IsFirstTimeRun())
        output->Reset();
    else if (output->mBlob.Size())
        output->mBlob.SetSize(output->mBlob.Size() - 1);    // Remove the last null-terminator
    startOffset = output->mBlob.Size();
    
    SysProcess proc;
    event.Info(cmd);
    if (proc.Run(cmd, SysProcessFlags::CaptureOutput|SysProcessFlags::InheritHandles|SysProcessFlags::DontCreateConsole, cwd)) {
        data->runningProc = &proc;
        char buffer[4096];
        uint32 bytesRead;

        while (proc.IsRunning()) {
            bytesRead = proc.ReadStdOut(buffer, sizeof(buffer));
            if (bytesRead == 0)
                break;

            output->WriteData(buffer, bytesRead);
            output->ParseLines();
        }

        // Read remaining pipe data if the process is exited
        while ((bytesRead = proc.ReadStdOut(buffer, sizeof(buffer))) > 0)
            output->WriteData(buffer, bytesRead);

        output->WriteData<char>('\0');
        output->ParseLines();
        data->runningProc = nullptr;

        Pin& execPin = ngGetPinData(graph, outPins[0]);
        Pin& outPin = ngGetPinData(graph, outPins[1]);
        Pin& retCodePin = ngGetPinData(graph, outPins[2]);

        if (data->checkRetCode) {
            if (data->successRetCode == proc.GetExitCode()) {
                execPin.ready = true;

                // Output Text
                outPin.data.SetString((const char*)output->mBlob.Data() + startOffset);
                outPin.ready = true;
                event.Success();
            }
            else {
                execPin.ready = false;
                outPin.ready = false;

                if (data->fatalErrorOnFail) {
                    char errorData[2048];
                    uint32 bytesRead = proc.ReadStdErr(errorData, sizeof(errorData)-1);
                    errorData[bytesRead] = 0;

                    strPrintFmt(data->errorStr, sizeof(data->errorStr), "Command failed with error code '%d': %s\n%s", proc.GetExitCode(), cmd, errorData);
                    event.ErrorFmt("Process failed with return code: %d", proc.GetExitCode());

                    return false;
                }
            }
        }
        else {
            execPin.ready = true;

            // Output Text
            outPin.data.SetString((const char*)output->mBlob.Data() + startOffset);
            outPin.ready = true;
            event.Success();
        }

        retCodePin.data.n = proc.GetExitCode();
        retCodePin.ready = true;
    }
    else {
        strPrintFmt(data->errorStr, sizeof(data->errorStr), "Running command failed: %s", cmd);
        event.Error("Command failed");
        return false;
    }
    return true;
}

void Node_CreateProcess::Abort(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    if (data->runningProc) 
        data->runningProc->Abort();
}

const char* Node_CreateProcess::GetLastError(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    return data->errorStr;
}

bool Node_CreateProcess::ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    
    ImGui::InputText("Title", data->title, sizeof(data->title), ImGuiInputTextFlags_CharsNoBlank);
    ImGui::Checkbox("RunInCmd", &data->runInCmd);
    ImGui::Checkbox("CheckReturnCode", &data->checkRetCode);
    if (data->checkRetCode) {
        ImGui::Checkbox("FatalErrorOnFail", &data->fatalErrorOnFail);
        ImGui::InputInt("Success code", &data->successRetCode);
    }
    ImGui::Separator();
    ImGui::TextUnformatted("CommandLine:");

    uint32 count = 0;
    bool refocus = false;
    for (uint32 i = 0; i < node.inPins.Count(); i++) {
        PinHandle pinHandle = node.inPins[i];
        Pin& pin = ngGetPinData(graph, pinHandle);

        if (pin.data.type != PinDataType::Void) {
            const char* pinName = (node.desc.dynamicInPins && i >= node.dynamicInPinIndex) ? GetString(pin.dynName) : pin.desc.name;
            if (ImGui::Button(pinName)) {
                char tmp[sizeof(data->executeCmd)];
                char pasteText[32];
                strPrintFmt(pasteText, sizeof(pasteText), "${%s}", pinName);
                if (data->textSelectionStart != data->textSelectionEnd) {
                    if (data->textSelectionEnd < data->textSelectionStart)
                        Swap<int>(data->textSelectionStart, data->textSelectionEnd);
                    strCopyCount(tmp, sizeof(tmp), data->executeCmd, data->textSelectionStart);
                    strConcat(tmp, sizeof(tmp), pasteText);
                    data->textCursor = strLen(tmp);
                    strConcat(tmp, sizeof(tmp), data->executeCmd + data->textSelectionEnd);
                }
                else {
                    strCopyCount(tmp, sizeof(tmp), data->executeCmd, data->textCursor);
                    strConcat(tmp, sizeof(tmp), pasteText);
                    int textCursor = data->textCursor;
                    data->textCursor = strLen(tmp);
                    strConcat(tmp, sizeof(tmp), data->executeCmd + textCursor);
                }
                memcpy(data->executeCmd, tmp, sizeof(data->executeCmd));
                refocus = true;
            }

            if (++count % 6 != 0) 
                ImGui::SameLine();
        }
    }

    ImGui::NewLine();

    if (refocus) {
        ImGui::SetKeyboardFocusHere();
        data->refocus = true;
    }
    ImGui::InputTextMultiline("##Command", data->executeCmd, sizeof(data->executeCmd), ImVec2(float(data->cmdTextInputWidth), 50), 
                            ImGuiInputTextFlags_CallbackEdit|ImGuiInputTextFlags_CallbackResize|ImGuiInputTextFlags_CallbackAlways,
                            Node_CreateProcess::CmdEditCallback, data);
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_ARROW_CIRCLE_RIGHT)) {
        ImVec2 textSize = imguiGetFonts().uiFont->CalcTextSizeA(imguiGetFonts().uiFontSize, 2048, 0, data->executeCmd);
        data->cmdTextInputWidth = Max<int>(int(textSize.x), 550);
    }

    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_ARROW_CIRCLE_LEFT))
        data->cmdTextInputWidth = 550;

    if (data->executeCmd[0] == 0)
        return false;
    if (data->title[0] == 0)
        return false;
    return true;
}

const char* Node_CreateProcess::GetTitleUI(NodeGraph* graph, NodeHandle handle)
{
    Node& node = ngGetNodeData(graph, handle);
    Data* data = (Data*)node.data;
    return data->title;
}

void Node_CreateProcess::SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    sjson_put_string(jctx, jparent, "Title", data->title);
    sjson_put_string(jctx, jparent, "ExecuteCmd", data->executeCmd);
    sjson_put_int(jctx, jparent, "SuccessRetCode", data->successRetCode);
    sjson_put_int(jctx, jparent, "CmdTextInputWidth", data->cmdTextInputWidth);
    sjson_put_bool(jctx, jparent, "CheckRetCode", data->checkRetCode);
    sjson_put_bool(jctx, jparent, "FatalErrorOnFail", data->fatalErrorOnFail);
    sjson_put_bool(jctx, jparent, "RunInCmd", data->runInCmd);
}

bool Node_CreateProcess::LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    strCopy(data->title, sizeof(data->title), sjson_get_string(jparent, "Title", node.desc.name));
    strCopy(data->executeCmd, sizeof(data->executeCmd), sjson_get_string(jparent, "ExecuteCmd", ""));
    data->successRetCode = sjson_get_int(jparent, "SuccessRetCode", 0);
    data->cmdTextInputWidth = sjson_get_int(jparent, "CmdTextInputWidth", 550);
    data->checkRetCode = sjson_get_bool(jparent, "CheckRetCode", true);
    data->fatalErrorOnFail = sjson_get_bool(jparent, "FatalErrorOnFail", true);
    data->runInCmd = sjson_get_bool (jparent, "RunInCmd", false);

    return true;
}

int Node_CreateProcess::CmdEditCallback(ImGuiInputTextCallbackData* data)
{
    Data* myData = (Data*)data->UserData;

    if (data->Flags == ImGuiInputTextFlags_CallbackResize) {
        ASSERT_MSG(0, "Buffer resize not implemented");
    }

    if (myData->refocus) {
        data->CursorPos = myData->textCursor;
        data->SelectionStart = data->SelectionEnd = myData->textCursor;
        myData->refocus = false;
    }
    else {
        myData->textCursor = data->CursorPos;
        myData->textSelectionStart = data->SelectionStart;
        myData->textSelectionEnd = data->SelectionEnd;
    }

    return 0;
}

void Node_CreateProcess::Register()
{
    static Node_CreateProcess self;
    ngRegisterNode(Desc, &self);
}

#if PLATFORM_WINDOWS
//----------------------------------------------------------------------------------------------------------------------
// Node_ShellExecute
bool Node_ShellExecute::Initialize(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Node_ShellExecute::Data>();
    node.data = data;

    strCopy(data->title, sizeof(data->title), node.desc.name);
    data->fatalErrorOnFail = true;
    return true;
}

bool Node_ShellExecute::InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Node_ShellExecute::Data>();
    node.data = data;

    Data* copyData = (Data*)srcData;
    strCopy(data->title, sizeof(data->title), copyData->title);
    strCopy(data->executeArgs, sizeof(data->executeArgs), copyData->executeArgs);
    strCopy(data->operation, sizeof(data->operation), copyData->operation);
    data->fatalErrorOnFail = copyData->fatalErrorOnFail;
    data->runAsAdmin = copyData->runAsAdmin;
    data->selectedOp = copyData->selectedOp;
    
    return true;
}

void Node_ShellExecute::Release(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    memFree(node.data);
}

bool Node_ShellExecute::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    // Parse and generate the final command string
    MemTempAllocator tmpAlloc;
    Blob blob(&tmpAlloc);
    blob.SetGrowPolicy(Blob::GrowPolicy::Linear);

    if (!ParseFormatText(&blob, data->executeArgs, graph, inPins, data->errorStr, sizeof(data->errorStr)))
        return false;

    TskEventScope event(graph, GetTitleUI(graph, nodeHandle));

    Pin& cmdPin = ngGetPinData(graph, inPins[1]);
    const char* cmd = cmdPin.data.str;

    const char* args = (const char*)blob.Data();
    Pin& cwdPin = ngGetPinData(graph, inPins[2]);
    const char* cwd = cwdPin.ready ? cwdPin.data.str : nullptr;

    uint32 fullCmdSize = strLen(cmd) + strLen(args) + 2;
    char* fullCmd = tmpAlloc.MallocTyped<char>(fullCmdSize);
    strCopy(fullCmd, fullCmdSize, cmd);
    strConcat(fullCmd, fullCmdSize, " ");
    strConcat(fullCmd, fullCmdSize, args);
    event.Info(fullCmd);

    Pin& execPin = ngGetPinData(graph, outPins[0]);

    const char* operation = data->operation[0] ? data->operation : nullptr;
    if (data->runAsAdmin)
        operation = "runas";

    SysWin32ShellExecuteResult r = sysWin32ShellExecute(cmd, data->executeArgs[0] ? data->executeArgs : nullptr, cwd, 
                                                        SysWin32ShowWindow::Default, operation);
    if (r == SysWin32ShellExecuteResult::Ok) {
        execPin.ready = true;
    }
    else {
        if (data->fatalErrorOnFail) {
            const char* errorReason = "Unknown";
            switch (r) {
            case SysWin32ShellExecuteResult::OutOfMemory:   errorReason = "OutOfMemory"; break;
            case SysWin32ShellExecuteResult::FileNotFound:  errorReason = "FileNotFound"; break;
            case SysWin32ShellExecuteResult::PathNotFound:  errorReason = "PathNotFound";   break;
            case SysWin32ShellExecuteResult::BadFormat:     errorReason = "BadFormat";  break;
            case SysWin32ShellExecuteResult::AccessDenied:  errorReason = "AccessDenied"; break;
            case SysWin32ShellExecuteResult::NoAssociation: errorReason = "NoAssociation";  break;
            default:    break;
            }

            strPrintFmt(data->errorStr, sizeof(data->errorStr), "Command failed with error '%s': %s", errorReason, fullCmd);
            event.ErrorFmt("Command failed with error '%s'", errorReason);
            execPin.ready = false;
            return false;
        }
        else {
            execPin.ready = true;
        }
    }

    return true;
}

const char* Node_ShellExecute::GetLastError(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    return data->errorStr;
}

bool Node_ShellExecute::ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    static const char* ops[] = {
        "default",
        "edit",
        "explore",
        "find", 
        "open",
        "print"
    };

    ImGui::InputText("Title", data->title, sizeof(data->title), ImGuiInputTextFlags_CharsNoBlank);
    ImGui::Checkbox("RunAsAdmin", &data->runAsAdmin);
    ImGui::Checkbox("FatalErrorOnFail", &data->fatalErrorOnFail);

    if (!data->runAsAdmin) {
        if (ImGui::Combo("Operation", &data->selectedOp, ops, CountOf(ops))) {
            if (data->selectedOp <= 0)
                data->operation[0] = 0;
            else 
                strCopy(data->operation, sizeof(data->operation), ops[data->selectedOp]);
        }
    }
    ImGui::Separator();
    ImGui::TextUnformatted("Arguments:");

    uint32 count = 0;
    bool refocus = false;
    for (uint32 i = 2; i < node.inPins.Count(); i++) {
        PinHandle pinHandle = node.inPins[i];
        Pin& pin = ngGetPinData(graph, pinHandle);

        if (pin.data.type != PinDataType::Void) {
            const char* pinName = (node.desc.dynamicInPins && i >= node.dynamicInPinIndex) ? GetString(pin.dynName) : pin.desc.name;
            if (ImGui::Button(pinName)) {
                char tmp[sizeof(data->executeArgs)];
                char pasteText[32];
                strPrintFmt(pasteText, sizeof(pasteText), "${%s}", pinName);
                if (data->textSelectionStart != data->textSelectionEnd) {
                    if (data->textSelectionEnd < data->textSelectionStart)
                        Swap<int>(data->textSelectionStart, data->textSelectionEnd);
                    strCopyCount(tmp, sizeof(tmp), data->executeArgs, data->textSelectionStart);
                    strConcat(tmp, sizeof(tmp), pasteText);
                    data->textCursor = strLen(tmp);
                    strConcat(tmp, sizeof(tmp), data->executeArgs + data->textSelectionEnd);
                }
                else {
                    strCopyCount(tmp, sizeof(tmp), data->executeArgs, data->textCursor);
                    strConcat(tmp, sizeof(tmp), pasteText);
                    int textCursor = data->textCursor;
                    data->textCursor = strLen(tmp);
                    strConcat(tmp, sizeof(tmp), data->executeArgs + textCursor);
                }
                memcpy(data->executeArgs, tmp, sizeof(data->executeArgs));
                refocus = true;
            }

            if (++count % 6 != 0) 
                ImGui::SameLine();
        }
    }

    ImGui::NewLine();

    if (refocus) {
        ImGui::SetKeyboardFocusHere();
        data->refocus = true;
    }
    ImGui::InputTextMultiline("##Args", data->executeArgs, sizeof(data->executeArgs), ImVec2(550, 50), 
                              ImGuiInputTextFlags_CallbackEdit|ImGuiInputTextFlags_CallbackResize|ImGuiInputTextFlags_CallbackAlways,
                              Node_ShellExecute::CmdEditCallback, data);
    if (data->title[0] == 0)
        return false;
    return true;
}

const char* Node_ShellExecute::GetTitleUI(NodeGraph* graph, NodeHandle handle)
{
    Node& node = ngGetNodeData(graph, handle);
    Data* data = (Data*)node.data;
    return data->title;
}

void Node_ShellExecute::SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    sjson_put_string(jctx, jparent, "Title", data->title);
    sjson_put_string(jctx, jparent, "ExecuteArgs", data->executeArgs);
    sjson_put_string(jctx, jparent, "Operation", data->operation);
    sjson_put_bool(jctx, jparent, "FatalErrorOnFail", data->fatalErrorOnFail);
    sjson_put_bool(jctx, jparent, "RunAsAdmin", data->runAsAdmin);
}

bool Node_ShellExecute::LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    strCopy(data->title, sizeof(data->title), sjson_get_string(jparent, "Title", node.desc.name));
    strCopy(data->executeArgs, sizeof(data->executeArgs), sjson_get_string(jparent, "ExecuteArgs", ""));
    strCopy(data->operation, sizeof(data->operation), sjson_get_string(jparent, "Operation", ""));
    data->fatalErrorOnFail = sjson_get_bool(jparent, "FatalErrorOnFail", true);
    data->runAsAdmin = sjson_get_bool (jparent, "RunAsAdmin", false);

    static const char* ops[] = {
        "default",
        "edit",
        "explore",
        "find", 
        "open",
        "print"
    };
    for (uint32 i = 0; i < CountOf(ops); i++) {
        if (strIsEqual(ops[i], data->operation)) {
            data->selectedOp = i;
            break;
        }
    }

    return true;
}

int Node_ShellExecute::CmdEditCallback(ImGuiInputTextCallbackData* data)
{
    Data* myData = (Data*)data->UserData;

    if (data->Flags == ImGuiInputTextFlags_CallbackResize) {
        ASSERT_MSG(0, "Buffer resize not implemented");
    }

    if (myData->refocus) {
        data->CursorPos = myData->textCursor;
        data->SelectionStart = data->SelectionEnd = myData->textCursor;
        myData->refocus = false;
    }
    else {
        myData->textCursor = data->CursorPos;
        myData->textSelectionStart = data->SelectionStart;
        myData->textSelectionEnd = data->SelectionEnd;
    }

    return 0;
}

void Node_ShellExecute::Register()
{
    static Node_ShellExecute self;
    ngRegisterNode(Desc, &self);
}
#endif // PLATFORM_WINDOWS

//----------------------------------------------------------------------------------------------------------------------
// Node_JoinStringArray
bool Node_JoinStringArray::Initialize(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Node_JoinStringArray::Data>();
    node.data = data;

    data->str.SetGrowPolicy(Blob::GrowPolicy::Linear);
    data->str.SetAllocator(memDefaultAlloc());

    strCopy(data->joinStr, sizeof(data->joinStr), "");

    if constexpr (PLATFORM_WINDOWS)
        data->isUnixPath = false;
    else
        data->isUnixPath = true;
    
    return true;
}

bool Node_JoinStringArray::InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Node_JoinStringArray::Data>();
    node.data = data;

    data->str.SetGrowPolicy(Blob::GrowPolicy::Linear);
    data->str.SetAllocator(memDefaultAlloc());

    Data* copyData = (Data*)srcData;
    strCopy(data->joinStr, sizeof(data->joinStr), copyData->joinStr);
    data->isUnixPath = copyData->isUnixPath;
    data->isDirectory = copyData->isDirectory;
    data->prepend = copyData->prepend;
    data->append = copyData->append;

    return true;
}

void Node_JoinStringArray::Release(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Node_JoinStringArray::Data* data = memAllocZeroTyped<Node_JoinStringArray::Data>();
    data->str.Free();
    memFree(node.data);
}

bool Node_JoinStringArray::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Node_JoinStringArray::Data* data = (Node_JoinStringArray::Data*)node.data;

    Pin& pinJoin = ngGetPinData(graph, inPins[0]);

    if (node.IsFirstTimeRun())
        data->str.Reset();

    if (data->prepend) {
        if (!data->isDirectory) { if (data->joinStr[0]) data->str.Write(data->joinStr, strLen(data->joinStr)); }
        else                    { data->str.Write<char>(data->isUnixPath ? '/' : '\\'); }
    }

    if (pinJoin.data.size) {
        if (data->isDirectory)
            data->str.Write(strReplaceChar(pinJoin.data.str, uint32(pinJoin.data.size)+1, data->isUnixPath ? '\\' : '/', data->isUnixPath ? '/' : '\\'), pinJoin.data.size);
        else 
            data->str.Write(pinJoin.data.str, pinJoin.data.size);
    }


    if (pinJoin.loop || data->append) {
        if (!data->isDirectory) { if (data->joinStr[0]) data->str.Write(data->joinStr, strLen(data->joinStr)); }
        else                    { data->str.Write<char>(data->isUnixPath ? '/' : '\\'); }
    }

    if (!pinJoin.loop) {
        data->str.Write<char>(0);

        Pin& outPin = ngGetPinData(graph, outPins[0]);
        outPin.data.SetString((const char*)data->str.Data(), (uint32)data->str.Size() - 1);
        outPin.ready = true;
    }

    return true;
}

bool Node_JoinStringArray::ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Node_JoinStringArray::Data* data = (Node_JoinStringArray::Data*)node.data;

    ImGui::Checkbox("Directory Join", &data->isDirectory);
    if (!data->isDirectory) {
        ImGui::InputText("Join String", data->joinStr, sizeof(data->joinStr));
    }
    else {
        ImGui::Checkbox("Unix Path", &data->isUnixPath);
    }

    ImGui::Checkbox("Prepend", &data->prepend);
    ImGui::Checkbox("Append", &data->append);

    return true;
}

void Node_JoinStringArray::SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Node_JoinStringArray::Data* data = (Node_JoinStringArray::Data*)node.data;
    sjson_put_bool(jctx, jparent, "IsDirectory", data->isDirectory);
    sjson_put_bool(jctx, jparent, "Prepend", data->prepend);
    sjson_put_bool(jctx, jparent, "Append", data->append);
    sjson_put_bool(jctx, jparent, "IsUnixPath", data->isUnixPath);
    sjson_put_string(jctx, jparent, "JoinStr", data->joinStr);
}

bool Node_JoinStringArray::LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Node_JoinStringArray::Data* data = (Node_JoinStringArray::Data*)node.data;

    if constexpr(PLATFORM_WINDOWS)
        data->isUnixPath = false;
    else
        data->isUnixPath = true;

    data->isDirectory = sjson_get_bool(jparent, "IsDirectory", false);
    data->isUnixPath = sjson_get_bool(jparent, "IsUnixPath", data->isUnixPath);
    data->prepend = sjson_get_bool(jparent, "Prepend", false);
    data->append = sjson_get_bool(jparent, "Append", false);
    strCopy(data->joinStr, sizeof(data->joinStr), sjson_get_string(jparent, "JoinStr", ""));

    return true;
}

void Node_JoinStringArray::Register()
{
    static Node_JoinStringArray self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
// Node_JoinString
bool Node_JoinString::Initialize(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Node_JoinString::Data>();
    node.data = data;

    data->str.SetGrowPolicy(Blob::GrowPolicy::Linear);
    data->str.SetAllocator(memDefaultAlloc());

    if constexpr(PLATFORM_WINDOWS)
        data->isUnixPath = false;
    else
        data->isUnixPath = true;
    
    return true;
}

bool Node_JoinString::InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Node_JoinString::Data>();
    node.data = data;

    data->str.SetGrowPolicy(Blob::GrowPolicy::Linear);
    data->str.SetAllocator(memDefaultAlloc());

    Data* copyData = (Data*)srcData;
    strCopy(data->joinStr, sizeof(data->joinStr), copyData->joinStr);
    data->isUnixPath = copyData->isUnixPath;
    data->isDirectory = copyData->isDirectory;

    return true;
}

void Node_JoinString::Release(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Node_JoinString::Data>();
    data->str.Free();
    memFree(node.data);
}

bool Node_JoinString::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Node_JoinString::Data*)node.data;
    data->str.Reset();

    if (inPins.Count() < 2) {
        strCopy(data->errDesc, sizeof(data->errDesc), "Must have at least have two inputs");
        return false;
    }

    uint32 joinStrLen = strLen(data->joinStr);

    auto AppendJoinStr = [data, joinStrLen]() {
        if (!data->isDirectory) {
            if (joinStrLen)
                data->str.Write(data->joinStr, joinStrLen);
        }
        else {
            data->str.Write<char>(data->isUnixPath ? '/' : '\\');
        }
    };

    auto AppendPinStr = [data](Pin& pin) {
        if (pin.data.size) {
            if (data->isDirectory)
                data->str.Write(strReplaceChar(pin.data.str, uint32(pin.data.size)+1, 
                                               data->isUnixPath ? '\\' : '/', data->isUnixPath ? '/' : '\\'), pin.data.size);
            else 
                data->str.Write(pin.data.str, pin.data.size);
        }
    };
    
    Pin& pinStr1 = ngGetPinData(graph, inPins[0]);
    AppendPinStr(pinStr1);
    AppendJoinStr();

    Pin& pinStr2 = ngGetPinData(graph, inPins[1]);
    AppendPinStr(pinStr2);
    if (inPins.Count() > 2)
        AppendJoinStr();

    for (uint32 i = 2; i < inPins.Count(); i++) {
        Pin& pinStr = ngGetPinData(graph, inPins[i]);
        AppendPinStr(pinStr);
        if (i < inPins.Count() - 1)
            AppendJoinStr();
    }
   
    data->str.Write<char>(0);

    Pin& outPin = ngGetPinData(graph, outPins[0]);
    outPin.data.SetString((const char*)data->str.Data(), (uint32)data->str.Size() - 1);
    outPin.ready = true;

    return true;
}

bool Node_JoinString::ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    ImGui::Checkbox("Directory Join", &data->isDirectory);
    if (!data->isDirectory)
        ImGui::InputText("Join String", data->joinStr, sizeof(data->joinStr));
    else 
        ImGui::Checkbox("Unix Path", &data->isUnixPath);
    return true;
}

const char* Node_JoinString::GetLastError(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    return data->errDesc;    
}

void Node_JoinString::SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Node_JoinString::Data*)node.data;
    sjson_put_bool(jctx, jparent, "IsDirectory", data->isDirectory);
    sjson_put_bool(jctx, jparent, "IsUnixPath", data->isUnixPath);
    sjson_put_string(jctx, jparent, "JoinStr", data->joinStr);
}

bool Node_JoinString::LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Node_JoinString::Data*)node.data;

    if constexpr(PLATFORM_WINDOWS)
        data->isUnixPath = false;
    else
        data->isUnixPath = true;

    data->isDirectory = sjson_get_bool(jparent, "IsDirectory", false);
    data->isUnixPath = sjson_get_bool(jparent, "IsUnixPath", data->isUnixPath);
    strCopy(data->joinStr, sizeof(data->joinStr), sjson_get_string(jparent, "JoinStr", ""));

    return true;
}

void Node_JoinString::Register()
{
    static Node_JoinString self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
// Node_SplitString

bool Node_SplitString::Initialize(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Node_SplitString::Data>();
    node.data = data;

    data->splitNewLines = true;

    return true;
}

bool Node_SplitString::InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Node_SplitString::Data>();
    node.data = data;

    Data* copyData = (Data*)srcData;
    data->splitChar = copyData->splitChar;
    data->ignoreFirstElems = copyData->ignoreFirstElems;
    data->ignoreLastElems = copyData->ignoreLastElems;
    data->maxElems = copyData->maxElems;
    data->splitNewLines = copyData->splitNewLines;
    data->ignoreWhitespace = copyData->ignoreWhitespace;

    return true;
}

void Node_SplitString::Release(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Node_SplitString::Data* data = (Node_SplitString::Data*)node.data;

    memFree(data);
}

bool Node_SplitString::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Node_SplitString::Data* data = (Node_SplitString::Data*)node.data;

    char splitChars[32];
    splitChars[0] = data->splitChar;
    splitChars[1] = 0;
    if (data->splitNewLines) 
        strConcat(splitChars, sizeof(splitChars), "\r\n");
    uint32 splitCharsLen = strLen(splitChars);

    auto IsSplitChar = [splitChars, splitCharsLen](char ch) { 
        for (uint32 i = 0; i < splitCharsLen; i++) {
            if (splitChars[i] == ch)
                return true;
        }
        return false;
    };
        
    Pin& inPin = ngGetPinData(graph, inPins[0]);
    if (inPin.loop) {
        data->errorStr = "Cannot feed arrays into SplitString";
        return false;
    }

    if (node.IsFirstTimeRun())
        data->strOffset = 0;

    char* inStr = inPin.data.str;
    char* startStr = inStr + data->strOffset;
    char* str = startStr;
    while (*str) {
        if (IsSplitChar(*str)) {
            MemTempAllocator tmpAlloc;
            uint32 len = uint32(str - startStr);
            if (len) {
                char* split = tmpAlloc.MallocTyped<char>(len + 1);
                strCopyCount(split, len+1, startStr, len);

                data->strOffset = uint32(str + 1 - inStr);

                Pin& outPin = ngGetPinData(graph, outPins[0]);
                outPin.data.SetString(split, len);
                outPin.ready = true;

                if (*(str + 1))
                    outPin.loop = true;

                return true;
            }
            else {
                data->strOffset = uint32(str + 1 - inStr);
            }
        }
        str++;
    }

    Pin& outPin = ngGetPinData(graph, outPins[0]);
    if (str != startStr) {
        MemTempAllocator tmpAlloc;

        uint32 len = uint32(str - startStr);
        if (len) {
            char* split = tmpAlloc.MallocTyped<char>(len + 1);
            strCopy(split, len+1, startStr);

            outPin.data.SetString(split, len);
            outPin.ready = true;
            outPin.loop = false;
        }
    }
    else {
        outPin.ready = false;
        outPin.loop = false;
    }

    return true;
}

const char* Node_SplitString::GetLastError(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Node_SplitString::Data* data = (Node_SplitString::Data*)node.data;
    return data->errorStr;
}

bool Node_SplitString::ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Node_SplitString::Data* data = (Node_SplitString::Data*)node.data;
    
    char text[2] = {data->splitChar};
    if (ImGui::InputText("SplitChar", text, sizeof(text), ImGuiInputTextFlags_CharsNoBlank))
        data->splitChar = text[0];
    ImGui::Checkbox("SplitNewlines", &data->splitNewLines);
    ImGui::Checkbox("IgnoreWhitespace", &data->ignoreWhitespace);

    if (data->splitChar == 0 && !data->splitNewLines)
        return false;
    return true;
}

void Node_SplitString::SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Node_SplitString::Data* data = (Node_SplitString::Data*)node.data;
    char text[2] = {data->splitChar};
    sjson_put_string(jctx, jparent, "SplitChar", text);
    sjson_put_bool(jctx, jparent, "SplitNewLines", data->splitNewLines);
    sjson_put_bool(jctx, jparent, "IgnoreWhitespace", data->ignoreWhitespace);
}

bool Node_SplitString::LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Node_SplitString::Data* data = (Node_SplitString::Data*)node.data;

    const char* text = sjson_get_string(jparent, "SplitChar", "");
    data->splitChar = text[0];

    data->splitNewLines = sjson_get_bool(jparent, "SplitNewLines", true);
    data->ignoreWhitespace = sjson_get_bool(jparent, "IgnoreWhitespace", false);

    return true;
}

void Node_SplitString::Register()
{
    static Node_SplitString self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
// Node_SplitPath
bool Node_SplitPath::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Pin& path = ngGetPinData(graph, node.inPins[0]);
    Pin& dir = ngGetPinData(graph, node.outPins[0]);
    Pin& filenameExt = ngGetPinData(graph, node.outPins[1]);
    Pin& filename = ngGetPinData(graph, node.outPins[2]);
    Pin& fileext = ngGetPinData(graph, node.outPins[3]);

    char directoryStr[kMaxPath];
    char filenameStr[kMaxPath];
    char fileextStr[kMaxPath];
    char filenameExtStr[kMaxPath];

    pathDirectory(path.data.str, directoryStr, sizeof(directoryStr));
    pathFileNameAndExt(path.data.str, filenameExtStr, sizeof(filenameExtStr));
    pathFileName(path.data.str, filenameStr, sizeof(filenameStr));
    pathFileExtension(path.data.str, fileextStr, sizeof(fileextStr));

    dir.data.SetString(directoryStr);           dir.ready = true;
    filenameExt.data.SetString(filenameExtStr); filenameExt.ready = true;
    filename.data.SetString(filenameStr);       filename.ready = true;
    fileext.data.SetString(fileextStr);         fileext.ready = true;

    return true;
}

void Node_SplitPath::Register()
{
    static Node_SplitPath self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
// Node_IsFile
bool Node_IsFile::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Pin& path = ngGetPinData(graph, node.inPins[0]);
    Pin& yesPin = ngGetPinData(graph, node.outPins[0]);
    Pin& noPin = ngGetPinData(graph, node.outPins[1]);
    Pin& outPath = ngGetPinData(graph, node.outPins[2]);
    Pin& outSize = ngGetPinData(graph, node.outPins[3]);
    Pin& outDate = ngGetPinData(graph, node.outPins[4]);

    PathInfo info = pathStat(path.data.str);
    outPath.data.SetString(path.data.str);
    outPath.ready = true;

    if (info.type == PathType::File) {
        yesPin.ready = true;
        noPin.ready = false;
        outSize.data.n = int(info.size);    // TODO: fix truncate
        outDate.data.n = int(info.lastModified);    // TODO: fix truncate
        outSize.ready = true;
        outDate.ready = true;
    }
    else {
        yesPin.ready = false;
        noPin.ready = true;
    }

    return true;
}

void Node_IsFile::Register()
{
    static Node_IsFile self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
// Node_IsFile
bool Node_IsDir::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Pin& path = ngGetPinData(graph, node.inPins[0]);
    Pin& yesPin = ngGetPinData(graph, node.outPins[0]);
    Pin& noPin = ngGetPinData(graph, node.outPins[1]);
    Pin& outPath = ngGetPinData(graph, node.outPins[2]);

    PathInfo info = pathStat(path.data.str);
    outPath.data.SetString(path.data.str);
    outPath.ready = true;

    yesPin.ready = info.type == PathType::Directory ? true : false;
    noPin.ready = !yesPin.ready;

    return true;
}

void Node_IsDir::Register()
{
    static Node_IsDir self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
// Node_CompareString
bool Node_CompareString::Initialize(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    node.data = data;

    return true;
}

bool Node_CompareString::InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    node.data = data;

    Data* copyData = (Data*)srcData;
    copyData->mode = copyData->mode;
    copyData->ignoreCase = copyData->ignoreCase;

    return true;
}

void Node_CompareString::Release(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    memFree(node.data);
}

bool Node_CompareString::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    const char* valueA = ngGetPinData(graph, inPins[0]).data.str;
    const char* valueB = ngGetPinData(graph, inPins[1]).data.str;

    bool isEqual = false;
    switch (data->mode) {
    case Mode::Normal:  
        isEqual = data->ignoreCase ? 
            strIsEqualNoCase(valueA, valueB) : 
            strIsEqual(valueA, valueB);     
        break;
    case Mode::BeginsWith: 
        isEqual = data->ignoreCase ? 
            strIsEqualNoCaseCount(valueA, valueB, strLen(valueA)) : 
            strIsEqualCount(valueA, valueB, strLen(valueA));
        break;
    case Mode::EndsWith:  {
        uint32 lenA = strLen(valueA);
        uint32 lenB = strLen(valueB);
        if (lenA <= lenB) {
            isEqual = data->ignoreCase ? 
                strIsEqualNoCaseCount(valueA, valueB + lenB - lenA, lenA) : 
                strIsEqualCount(valueA, valueB + lenB - lenA, lenA);
        }
        break;
    }
    default: break;
    }

    Pin& yesPin = ngGetPinData(graph, outPins[0]);
    Pin& noPin = ngGetPinData(graph, outPins[1]);
    Pin& outAPin = ngGetPinData(graph, outPins[2]);
    Pin& outBPin = ngGetPinData(graph, outPins[3]);

    yesPin.ready = isEqual;
    noPin.ready = !isEqual;
    outAPin.data.SetString(valueA);
    outAPin.ready = true;
    outBPin.data.SetString(valueB);
    outBPin.ready = true;

    return true;
}

bool Node_CompareString::ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    const char* items[int(Mode::_Count)] = {
        "A==B",
        "BeginsWithA",
        "EndsWithA"
    };
    ImGui::Combo("Mode", (int*)&data->mode, items, int(Mode::_Count));
    ImGui::Checkbox("IgnoreCase", &data->ignoreCase);

    return true;
}

void Node_CompareString::SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    sjson_put_int(jctx, jparent, "Mode", int(data->mode));
    sjson_put_bool(jctx, jparent, "IgnoreCase", data->ignoreCase);
}

bool Node_CompareString::LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    data->mode = Mode(sjson_get_int(jparent, "Mode", 0));
    data->ignoreCase = sjson_get_bool(jparent, "IgnoreCase", false);
    return true;
}

void Node_CompareString::Register()
{
    static Node_CompareString self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
// Node_StringConstant
bool Node_StringConstant::Initialize(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    node.data = data;
    
    strCopy(data->varName, sizeof(data->varName), node.desc.name);

    return true;
}

bool Node_StringConstant::InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    node.data = data;

    Data* copyData = (Data*)srcData;
    strCopy(data->varName, sizeof(data->varName), copyData->varName);
    strCopy(data->value, sizeof(data->value), copyData->value);

    return true;
}

void Node_StringConstant::Release(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    memFree(node.data);
}

const char* Node_StringConstant::GetTitleUI(NodeGraph* graph, NodeHandle handle)
{
    Node& node = ngGetNodeData(graph, handle);
    Data* data = (Data*)node.data;
    return data->varName;
}

bool Node_StringConstant::ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    ImGui::InputText("Name", data->varName, sizeof(data->varName), ImGuiInputTextFlags_CharsNoBlank);
    ImGui::InputText("Value", data->value, sizeof(data->value));

    return true;
}

bool Node_StringConstant::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    Pin& outPin = ngGetPinData(graph, outPins[0]);
    outPin.data.SetString(data->value);
    outPin.ready = true;
    return true;
}

void Node_StringConstant::SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    sjson_put_string(jctx, jparent, "VarName", data->varName);
    sjson_put_string(jctx, jparent, "Value", data->value);
}

bool Node_StringConstant::LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    strCopy(data->varName, sizeof(data->varName), sjson_get_string(jparent, "VarName", node.desc.name));
    strCopy(data->value, sizeof(data->value), sjson_get_string(jparent, "Value", ""));

    return true;
}

void Node_StringConstant::Register()
{
    static Node_StringConstant self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
// Node_Constants
bool Node_Constants::Initialize(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    node.data = data;
    
    data->items.SetAllocator(memDefaultAlloc());
    strCopy(data->title, sizeof(data->title), node.desc.name);

    return true;
}

bool Node_Constants::InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    node.data = data;

    data->items.SetAllocator(memDefaultAlloc());

    Data* copyData = (Data*)srcData;
    strCopy(data->title, sizeof(data->title), copyData->title);
    copyData->items.CopyTo(&data->items);

    return true;
}

void Node_Constants::Release(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    data->items.Free();
    memFree(node.data);
}

const char* Node_Constants::GetTitleUI(NodeGraph* graph, NodeHandle handle)
{
    Node& node = ngGetNodeData(graph, handle);
    Data* data = (Data*)node.data;
    return data->title;
}

bool Node_Constants::ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    ImGui::InputText("title", data->title, sizeof(data->title), ImGuiInputTextFlags_CharsNoBlank);
    ImGui::Separator();

    ImGui::TextUnformatted("Value overrides. You can set a longer value to each output pin");
    if (node.outPins.Count()) {
        if (ImGui::Button(ICON_FA_PLUS_SQUARE)) {
            data->items.Push(Item{});
        }
    }
    else {
        ImGui::TextUnformatted("No output pins to map to. Please add output pins first");
    }

    MemTempAllocator tmpAlloc;
    const char** pinNames = nullptr;
    if (node.outPins.Count()) {
        pinNames = tmpAlloc.MallocTyped<const char*>(node.outPins.Count());
        for (uint32 i = 0; i < node.outPins.Count(); i++) {
            Pin& pin = ngGetPinData(graph, node.outPins[i]);
            ASSERT(pin.dynName);
            pinNames[i] = GetString(pin.dynName);
        }
    }

    bool isValueEmpty = false;
    for (uint32 i = 0; i < data->items.Count(); i++) {
        Item& item = data->items[i];
        char idStr[32];

        strPrintFmt(idStr, sizeof(idStr), "Value###value_%u", i);
        ImGui::SetNextItemWidth(400);
        ImGui::InputText(idStr, item.value, sizeof(item.value), 0);
        isValueEmpty |= item.value[0] == 0;
        ImGui::SameLine();

        ImGui::TextUnformatted(ICON_FA_ARROW_RIGHT);
        ImGui::SameLine();

        ImGui::SetNextItemWidth(150);
        strPrintFmt(idStr, sizeof(idStr), "##pin_%u", i);
        int selectedPinIndex = Min(node.outPins.Count() - 1, item.outputPinIndex);
        if (ImGui::Combo(idStr, &selectedPinIndex, pinNames, node.outPins.Count())) {
            item.outputPinIndex = selectedPinIndex;
        }

        ImGui::SameLine();
        strPrintFmt(idStr, sizeof(idStr), "btn_%u", i);
        ImGui::PushID(idStr);
        if (ImGui::Button(ICON_FA_MINUS_SQUARE)) {
            data->items.Pop(i--);
        }
        ImGui::PopID();
    }

    return !isValueEmpty;
}

bool Node_Constants::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    for (uint32 index = 0; index < outPins.Count(); index++) {
        Pin& outPin = ngGetPinData(graph, outPins[index]);

        bool hasValue = false;
        for (Item& item : data->items) {
            if (item.outputPinIndex == index) {
                outPin.data.SetString(item.value);
                hasValue = true;
                break;
            }
        }

        if (!hasValue)
            outPin.data.SetString(GetString(outPin.dynName));

        outPin.ready = true;
    }

    return true;
}

void Node_Constants::SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    sjson_put_string(jctx, jparent, "Title", data->title);

    sjson_node* jitems = sjson_put_array(jctx, jparent, "Items");
    for (const Item& item : data->items) {
        sjson_node* jitem = sjson_mkobject(jctx);
        sjson_put_string(jctx, jitem, "Value", item.value);
        sjson_put_int(jctx, jitem, "OutputPinIndex", int(item.outputPinIndex));
        sjson_append_element(jitems, jitem);
    }
}

bool Node_Constants::LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    strCopy(data->title, sizeof(data->title), sjson_get_string(jparent, "Title", node.desc.name));
    sjson_node* jitems = sjson_find_member(jparent, "Items");
    if (jitems) {
        sjson_node* jitem = sjson_first_child(jitems);
        while (jitem) {
            Item item {};
            strCopy(item.value, sizeof(item.value), sjson_get_string(jitem, "Value", ""));
            item.outputPinIndex = uint32(sjson_get_int(jitem, "OutputPinIndex", 0));
            data->items.Push(item);

            jitem = jitem->next;
        }
    }

    return true;
}

void Node_Constants::Register()
{
    static Node_Constants self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
// Node_IntConstant
bool Node_IntConstant::Initialize(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    node.data = data;

    strCopy(data->varName, sizeof(data->varName), node.desc.name);
    return true;
}

bool Node_IntConstant::InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    node.data = data;

    Data* copyData = (Data*)srcData;
    strCopy(data->varName, sizeof(data->varName), copyData->varName);
    data->value = copyData->value;

    return true;
}

void Node_IntConstant::Release(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    memFree(node.data);
}

const char* Node_IntConstant::GetTitleUI(NodeGraph* graph, NodeHandle handle)
{
    Node& node = ngGetNodeData(graph, handle);
    Data* data = (Data*)node.data;
    return data->varName;
}

bool Node_IntConstant::ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    ImGui::InputText("Name", data->varName, sizeof(data->varName), ImGuiInputTextFlags_CharsNoBlank);
    ImGui::InputInt("Value", &data->value);

    return true;
}

bool Node_IntConstant::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    Pin& outPin = ngGetPinData(graph, outPins[0]);
    outPin.data.n = data->value;
    outPin.ready = true;
    return true;
}

void Node_IntConstant::SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    sjson_put_string(jctx, jparent, "VarName", data->varName);
    sjson_put_int(jctx, jparent, "Value", data->value);
}

bool Node_IntConstant::LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    strCopy(data->varName, sizeof(data->varName), sjson_get_string(jparent, "VarName", node.desc.name));
    data->value = sjson_get_int(jparent, "Value", 0);
    return true;
}

void Node_IntConstant::Register()
{
    static Node_IntConstant self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
// Node_BoolIf
bool Node_BoolIf::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Pin& valuePin = ngGetPinData(graph, node.inPins[0]);

    Pin& yesPin = ngGetPinData(graph, node.outPins[0]);
    Pin& noPin = ngGetPinData(graph, node.outPins[1]);

    yesPin.data.b = valuePin.data.b;
    noPin.data.b = !valuePin.data.b;

    yesPin.ready = valuePin.data.b;
    noPin.ready = !valuePin.data.b;

    return true;
}

void Node_BoolIf::Register()
{
    static Node_BoolIf self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
// Node_BoolIf
bool Node_BoolNegate::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Pin& valuePin = ngGetPinData(graph, node.inPins[0]);
    Pin& outPin = ngGetPinData(graph, node.outPins[0]);

    outPin.ready = true;
    outPin.data.b = !valuePin.data.b;

    return true;
}

void Node_BoolNegate::Register()
{
    static Node_BoolNegate self;
    ngRegisterNode(Desc, &self);
}


//----------------------------------------------------------------------------------------------------------------------
// Node_StringSelect
bool Node_Selector::Initialize(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    node.data = data;

    data->items.SetAllocator(memDefaultAlloc());
    strCopy(data->title, sizeof(data->title), node.desc.name);
    
    return true;
}

bool Node_Selector::InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    node.data = data;

    data->items.SetAllocator(memDefaultAlloc());

    Data* copyData = (Data*)srcData;
    strCopy(data->title, sizeof(data->title), copyData->title);
    copyData->items.CopyTo(&data->items);
    
    return true;
}

void Node_Selector::Release(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    data->items.Free();
}

const char* Node_Selector::GetTitleUI(NodeGraph* graph, NodeHandle handle)
{
    Node& node = ngGetNodeData(graph, handle);
    Data* data = (Data*)node.data;
    return data->title;
}

bool Node_Selector::ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    
    ImGui::InputText("Title", data->title, sizeof(data->title), ImGuiInputTextFlags_CharsNoBlank);
    ImGui::Separator();
    
    if (node.outPins.Count()) {
        if (ImGui::Button(ICON_FA_PLUS_SQUARE)) {
            data->items.Push(SelectorItem{});
        }
    }
    else {
        ImGui::TextUnformatted("No output pins to map to. Please add output pins first");
    }

    MemTempAllocator tmpAlloc;
    const char** pinNames = nullptr;
    if (node.outPins.Count()) {
        pinNames = tmpAlloc.MallocTyped<const char*>(node.outPins.Count());
        for (uint32 i = 0; i < node.outPins.Count(); i++) {
            Pin& pin = ngGetPinData(graph, node.outPins[i]);
            ASSERT(pin.dynName);
            pinNames[i] = GetString(pin.dynName);
        }
    }

    bool isValueEmpty = false;
    for (uint32 i = 0; i < data->items.Count(); i++) {
        SelectorItem& item = data->items[i];
        char idStr[32];

        strPrintFmt(idStr, sizeof(idStr), "##cond_%u", i);
        int selectedCond = int(item.cond);
        ImGui::SetNextItemWidth(150);
        if (ImGui::Combo(idStr, &selectedCond, ConditionStr, int(Condition::_Count))) {
            item.cond = Condition(selectedCond);
        }        
        ImGui::SameLine();

        strPrintFmt(idStr, sizeof(idStr), "Value###value_%u", i);
        ImGui::SetNextItemWidth(200);
        ImGui::InputText(idStr, item.value.Ptr(), item.value.Capacity(), ImGuiInputTextFlags_CharsNoBlank);
        item.value.CalcLength();
        isValueEmpty |= item.value.IsEmpty();
        ImGui::SameLine();

        ImGui::TextUnformatted(ICON_FA_ARROW_RIGHT);
        ImGui::SameLine();

        ImGui::SetNextItemWidth(100);
        strPrintFmt(idStr, sizeof(idStr), "##pin_%u", i);
        int selectedPinIndex = Min(node.outPins.Count() - 1, item.outputPinIndex);
        if (ImGui::Combo(idStr, &selectedPinIndex, pinNames, node.outPins.Count())) {
            item.outputPinIndex = selectedPinIndex;
        }

        ImGui::SameLine();
        strPrintFmt(idStr, sizeof(idStr), "btn_%u", i);
        ImGui::PushID(idStr);
        if (ImGui::Button(ICON_FA_MINUS_SQUARE)) {
            data->items.Pop(i--);
        }
        ImGui::PopID();
    }

    if (isValueEmpty)
        return false;

    return true;
}

bool Node_Selector::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    Pin& valuePin = ngGetPinData(graph, inPins[0]);

    if (data->items.Count() == 0) {
        strCopy(data->errorMsg, sizeof(data->errorMsg), "There are no mapping items for this selector. You should at least add one");
        return false;
    }

    for (PinHandle handle : outPins)
        ngGetPinData(graph, handle).ready = false;

    for (SelectorItem& item : data->items) {
        if (item.outputPinIndex >= outPins.Count()) {
            strPrintFmt(data->errorMsg, sizeof(data->errorMsg), "Cannot map selector item with value '%s' to pin #%u. Pin index is out of bounds, Possibly deleted", 
                        item.value.CStr(), item.outputPinIndex);
            return false;
        }
        Pin& outPin = ngGetPinData(graph, outPins[item.outputPinIndex]);

        switch (item.cond) {
        case Condition::Equal:
            if (strIsEqual(valuePin.data.str, item.value.CStr())) {
                outPin.data.SetString(GetString(outPin.dynName));;
                outPin.ready = true;
            }
            break;

        case Condition::EqualIgnoreCase:
            if (strIsEqualNoCase(valuePin.data.str, item.value.CStr())) {
                outPin.data.SetString(GetString(outPin.dynName));;
                outPin.ready = true;
            }
            break;

        case Condition::NotEqual:
            if (!strIsEqual(valuePin.data.str, item.value.CStr())) {
                outPin.data.SetString(GetString(outPin.dynName));;
                outPin.ready = true;
            }
            break;
        default: break;
        }
    }

    return true;
}

const char* Node_Selector::GetLastError(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    return data->errorMsg;
}

void Node_Selector::SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    
    sjson_put_string(jctx, jparent, "Title", data->title);
    sjson_node* jitems = sjson_put_array(jctx, jparent, "SelectorItems");
    for (const SelectorItem& item : data->items) {
        sjson_node* jitem = sjson_mkobject(jctx);
        sjson_put_string(jctx, jitem, "Value", item.value.CStr());
        sjson_put_int(jctx, jitem, "Condition", int(item.cond));
        sjson_put_int(jctx, jitem, "OutputPinIndex", int(item.outputPinIndex));
        sjson_append_element(jitems, jitem);
    }
}

bool Node_Selector::LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    strCopy(data->title, sizeof(data->title), sjson_get_string(jparent, "Title", node.desc.name));
    sjson_node* jitems = sjson_find_member(jparent, "SelectorItems");
    if (jitems) {
        sjson_node* jitem = sjson_first_child(jitems);
        while (jitem) {
            SelectorItem item {};
            item.value = sjson_get_string(jitem, "Value", "");
            item.cond = Condition(sjson_get_int(jitem, "Condition", 0));
            item.outputPinIndex = uint32(sjson_get_int(jitem, "OutputPinIndex", 0));
            data->items.Push(item);

            jitem = jitem->next;
        }
    }
    return true;
}

void Node_Selector::Register()
{
    static Node_Selector self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
bool Node_MathCounter::Initialize(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    node.data = data;

    return true;
}

bool Node_MathCounter::InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    node.data = data;
    const Data* _srcData = (const Data*)srcData;

    data->counter = _srcData->counter;
    data->start = _srcData->start;

    return Initialize(graph, nodeHandle);
}

void Node_MathCounter::Release(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    memFree(node.data);
}

bool Node_MathCounter::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Pin& inPin = ngGetPinData(graph, inPins[0]);
    Data* data = (Data*)node.data;
    ASSERT(inPin.ready);

    Pin& countPin = ngGetPinData(graph, outPins[0]);
    Pin& outPin = ngGetPinData(graph, outPins[1]);

    if (node.IsFirstTimeRun())
        data->counter = data->start;

    countPin.data.n = data->counter++;
    countPin.ready = true;

    outPin.data.SetString(inPin.data.str);
    outPin.ready = true;

    return true;
}

bool Node_MathCounter::ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    ImGui::InputInt("StartFrom", &data->start);
    return true;
}

void Node_MathCounter::SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    sjson_put_int(jctx, jparent, "StartFrom", data->start);
}

bool Node_MathCounter::LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    
    data->start = sjson_get_int(jparent, "StartFrom", 0);
    return true;
}

void Node_MathCounter::Register()
{
    static Node_MathCounter self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
// Node_EmbedGraph
bool Node_EmbedGraph::Initialize(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    data->graphMutex.Initialize();
    node.data = data;
    return true;
}

bool Node_EmbedGraph::InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData)
{
    // TODO
    return false;
}

void Node_EmbedGraph::Release(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    ngDestroy(data->graph);
    data->graphMutex.Release();
    memFree(data);
}

const char* Node_EmbedGraph::GetTitleUI(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    if (data->title[0]) 
        return data->title;
    else if (!data->fileHandle.IsValid())
        return wksGetFileInfo(GetWorkspace(), data->fileHandle).name;
    else
        return node.desc.name;
}

bool Node_EmbedGraph::ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    Path filepath = wksGetWorkspaceFilePath(GetWorkspace(), data->fileHandle);
    ImGui::InputText("Title", data->title, sizeof(data->title), ImGuiInputTextFlags_CharsNoBlank);
    ImGui::InputText("Filepath", filepath.Ptr(), filepath.Capacity(), ImGuiInputTextFlags_ReadOnly);

    return true;
}

bool Node_EmbedGraph::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    if (data->loadError || !data->graph)
        return false;

    data->graphMutex.Enter();
    
    TskEventScope taskEvent(graph, GetTitleUI(graph, nodeHandle));
    
    // Set properties in the graph
    {
        MemTempAllocator tmpAlloc;
        Array<PropertyHandle> propHandles = ngGetProperties(data->graph, &tmpAlloc);

        for (uint32 i = node.dynamicInPinIndex; i < inPins.Count(); i++) {
            Pin& inPin = ngGetPinData(graph, inPins[i]);
            uint32 propIndex = propHandles.FindIf([inPin, data](const PropertyHandle& handle)->bool { return ngGetPropertyData(data->graph, handle).pinName == inPin.dynName; });
            if (propIndex == INVALID_INDEX) {
                logWarning("Property '%s' not found in graph '%s'", GetString(inPin.dynName), wksGetWorkspaceFilePath(GetWorkspace(), ngGetFileHandle(data->graph)).CStr());
            }
            else {
                Property& prop = ngGetPropertyData(data->graph, propHandles[propIndex]);
                Pin& propPin = ngGetPinData(data->graph, prop.pin);
                propPin.data.CopyFrom(inPin.data);
            }
        }
    }

    TextContent* output = node.outputText;
    if (node.IsFirstTimeRun())
        output->Reset();
    else if (output->mBlob.Size())
        output->mBlob.SetSize(output->mBlob.Size() - 1);    // Remove the last null-terminator

    bool r = ngExecute(data->graph, false, nullptr, output, taskEvent.mHandle);

    if (r) {
        Pin& execPin = ngGetPinData(graph, outPins[0]);
        execPin.ready = true;
        taskEvent.Success();

        Pin& outPin = ngGetPinData(graph, outPins[1]);
        outPin.ready = true;
        outPin.data.CopyFrom(ngGetOutputResult(data->graph));
    }
    else {
        strCopy(data->errorMsg, sizeof(data->errorMsg), ngGetLastError(data->graph));
        taskEvent.Error(data->errorMsg);
    }
    
    data->graphMutex.Exit();
    return r;
}

const char* Node_EmbedGraph::GetLastError(NodeGraph* graph, NodeHandle nodeHandle) 
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    return data->errorMsg;
}

void Node_EmbedGraph::SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    sjson_put_string(jctx, jparent, "Title", data->title);
    sjson_put_string(jctx, jparent, "Filepath", wksGetWorkspaceFilePath(GetWorkspace(), data->fileHandle).CStr());
}

bool Node_EmbedGraph::LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    char errMsg[512];

    strCopy(data->title, sizeof(data->title), sjson_get_string(jparent, "Title", node.desc.name));
    Path filepath = sjson_get_string(jparent, "Filepath", "");
    if (filepath.IsEmpty()) {
        SetLoadError(graph, nodeHandle, WksFileHandle(), "No file to load");
        return false;
    }

    WksFileHandle fileHandle = wksFindFile(GetWorkspace(), filepath.CStr());
    if (!fileHandle.IsValid()) {
        strPrintFmt(errMsg, sizeof(errMsg), "File does not exist in workspace anymore: %s", filepath.CStr());
        SetLoadError(graph, nodeHandle, WksFileHandle(), errMsg);
        return false;
    }

    NodeGraph* newGraph = ngLoadChild(graph, fileHandle, errMsg, sizeof(errMsg));
    if (newGraph) {
        Set(graph, nodeHandle, newGraph, fileHandle);
        return true;
    }
    else  {
        SetLoadError(graph, nodeHandle, fileHandle, errMsg);
        return false;
    }
}

void Node_EmbedGraph::Set(NodeGraph* graph, NodeHandle nodeHandle, NodeGraph* embedGraph, WksFileHandle fileHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    data->graph = embedGraph;
    data->fileHandle = fileHandle;
    data->loadError = false;

    if (data->title[0] == 0)
        strCopy(data->title, sizeof(data->title), wksGetFileInfo(GetWorkspace(), fileHandle).name);
}

void Node_EmbedGraph::SetLoadError(NodeGraph* graph, NodeHandle nodeHandle, WksFileHandle fileHandle, const char* errMsg)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    ASSERT(!data->graph);
    data->loadError = true;
    data->fileHandle = fileHandle;
    strCopy(data->errorMsg, sizeof(data->errorMsg), errMsg);

    if (data->title[0] == 0)
        strCopy(data->title, sizeof(data->title), wksGetFileInfo(GetWorkspace(), fileHandle).name);
}

WksFileHandle Node_EmbedGraph::GetGraphFileHandle(NodeGraph* graph, NodeHandle nodeHandle) const
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    return data->fileHandle;
}

bool Node_EmbedGraph::ReloadGraph(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    MutexScope mtx(data->graphMutex);
    if (!data->loadError && data->graph) {
        ngUnloadChild(graph, data->fileHandle);
        ngDestroy(data->graph);
        char errMsg[512];
        data->graph = ngLoadChild(graph, data->fileHandle, errMsg, sizeof(errMsg), true);
        if (!data->graph) {
            SetLoadError(graph, nodeHandle, data->fileHandle, errMsg);
            return false;
        }
    }

    return true;
}

void Node_EmbedGraph::Abort(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    if (data->graph)
        ngStop(data->graph);
}

void Node_EmbedGraph::Register()
{
    static Node_EmbedGraph self;
    ngRegisterNode(Desc, &self);
}

//------------------------------------------------------------------------
bool Node_FormatString::Initialize(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    node.data = data;
    return true;
}

bool Node_FormatString::InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    node.data = data;
    Data* _srcData = (Data*)srcData;

    memcpy(data->text, _srcData->text, sizeof(data->text));
    return true;
}

void Node_FormatString::Release(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    memFree(data);
}

bool Node_FormatString::ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    ImGui::TextUnformatted("Formatted Text:");

    uint32 count = 0;
    bool refocus = false;
    for (uint32 i = 0; i < node.inPins.Count(); i++) {
        PinHandle pinHandle = node.inPins[i];
        Pin& pin = ngGetPinData(graph, pinHandle);

        if (pin.data.type != PinDataType::Void) {
            const char* pinName = (node.desc.dynamicInPins && i >= node.dynamicInPinIndex) ? GetString(pin.dynName) : pin.desc.name;
            if (ImGui::Button(pinName)) {
                char tmp[sizeof(data->text)];
                char pasteText[32];
                strPrintFmt(pasteText, sizeof(pasteText), "${%s}", pinName);
                if (data->textSelectionStart != data->textSelectionEnd) {
                    if (data->textSelectionEnd < data->textSelectionStart)
                        Swap<int>(data->textSelectionStart, data->textSelectionEnd);
                    strCopyCount(tmp, sizeof(tmp), data->text, data->textSelectionStart);
                    strConcat(tmp, sizeof(tmp), pasteText);
                    data->textCursor = strLen(tmp);
                    strConcat(tmp, sizeof(tmp), data->text + data->textSelectionEnd);
                }
                else {
                    strCopyCount(tmp, sizeof(tmp), data->text, data->textCursor);
                    strConcat(tmp, sizeof(tmp), pasteText);
                    int textCursor = data->textCursor;
                    data->textCursor = strLen(tmp);
                    strConcat(tmp, sizeof(tmp), data->text + textCursor);
                }
                memcpy(data->text, tmp, sizeof(data->text));
                refocus = true;
            }

            if (++count % 6 != 0) 
                ImGui::SameLine();
        }
    }

    ImGui::NewLine();

    if (refocus) {
        ImGui::SetKeyboardFocusHere();
        data->refocus = true;
    }
    ImGui::InputTextMultiline("##FormattedText", data->text, sizeof(data->text), ImVec2(300, 50), 
                              ImGuiInputTextFlags_CallbackEdit|ImGuiInputTextFlags_CallbackResize|ImGuiInputTextFlags_CallbackAlways,
                              CmdEditCallback, data);

    if (data->text[0] == 0)
        return false;
    return true;
}

bool Node_FormatString::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    MemTempAllocator tmpAlloc;
    Blob blob(&tmpAlloc);
    blob.SetGrowPolicy(Blob::GrowPolicy::Linear);

    if (!ParseFormatText(&blob, data->text, graph, inPins, data->errorStr, sizeof(data->errorStr)))
        return false;

    Pin& outPin = ngGetPinData(graph, outPins[0]);
    outPin.data.SetString((const char*)blob.Data());
    outPin.ready = true;

    return true;
}

void Node_FormatString::SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    sjson_put_string(jctx, jparent, "Text", data->text);
}

bool Node_FormatString::LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    strCopy(data->text, sizeof(data->text), sjson_get_string(jparent, "Text", ""));
    return true;
}

const char* Node_FormatString::GetLastError(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    return data->errorStr;
}

int Node_FormatString::CmdEditCallback(ImGuiInputTextCallbackData* data)
{
    Data* myData = (Data*)data->UserData;

    if (data->Flags == ImGuiInputTextFlags_CallbackResize) {
        ASSERT_MSG(0, "Buffer resize not implemented");
    }

    if (myData->refocus) {
        data->CursorPos = myData->textCursor;
        data->SelectionStart = data->SelectionEnd = myData->textCursor;
        myData->refocus = false;
    }
    else {
        myData->textCursor = data->CursorPos;
        myData->textSelectionStart = data->SelectionStart;
        myData->textSelectionEnd = data->SelectionEnd;
    }

    return 0;
}

void Node_FormatString::Register()
{
    static Node_FormatString self;
    ngRegisterNode(Desc, &self);
}

//------------------------------------------------------------------------
bool Node_GraphOutput::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Pin& inPin = ngGetPinData(graph, inPins[0]);
    ngSetOutputResult(graph, inPin.data);
    return true;
}

void Node_GraphOutput::Register()
{
    static Node_GraphOutput self;
    ngRegisterNode(Desc, &self);
}

//------------------------------------------------------------------------
bool Node_GraphMetaData::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Pin& inPin = ngGetPinData(graph, inPins[0]);
    ngSetMetaData(graph, inPin.data);
    return true;
}

void Node_GraphMetaData::Register()
{
    static Node_GraphMetaData self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
bool Node_ListDir::Initialize(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    node.data = data;
    return true;
}

bool Node_ListDir::InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* _srcData)
{
    if (!Initialize(graph, nodeHandle))
        return false;

    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    Data* srcData = (Data*)_srcData;

    strCopy(data->extensions, sizeof(data->extensions), srcData->extensions);
    strCopy(data->excludeExtensions, sizeof(data->excludeExtensions), srcData->excludeExtensions);
    data->recursive = srcData->recursive;
    data->ignoreDirectories = srcData->ignoreDirectories;
    data->onlyDirectories = srcData->onlyDirectories;

    return true;
}

void Node_ListDir::Release(NodeGraph* graph, NodeHandle nodeHandle)
{
}

bool Node_ListDir::ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    ImGui::Checkbox("Recursive", &data->recursive);
    
    if (ImGui::Checkbox("Ignore directories", &data->ignoreDirectories)) {
        data->onlyDirectories = !data->ignoreDirectories;
    }
    
    if (ImGui::Checkbox("Only include directories", &data->onlyDirectories)) {
        data->ignoreDirectories = !data->onlyDirectories;
    }

    if (!data->onlyDirectories) {
        ImGui::Separator();
        ImGui::TextUnformatted("Extensions are separated by space. Example: \".txt .cpp .h\"");
        if (ImGui::InputText("Extensions", data->extensions, sizeof(data->extensions))) {
            strTrim(data->extensions, sizeof(data->extensions), data->extensions);
        }

        if (ImGui::InputText("Exclude Extensions", data->excludeExtensions, sizeof(data->excludeExtensions))) {
            strTrim(data->excludeExtensions, sizeof(data->excludeExtensions), data->excludeExtensions);
        }
    }

    if (data->ignoreDirectories && data->onlyDirectories)
        return false;

    return true;
}

static void ListDir_GetListing(const Path& dirPath, Node_ListDir::Data* data, TextContent* output, 
                               Span<char*> extensions, Span<char*> excludeExtensions, 
                               DIR* d)
{
    auto IsAcceptableFileName = [&extensions, &excludeExtensions](const char* name)->bool 
    {
        if (extensions.Count()) {
            for (const char* ext : extensions) {
                if (strEndsWith(name, ext))
                    return true;
            }
            return false;
        }

        for (const char* ext : excludeExtensions) {
            if (strEndsWith(name, ext))
                return false;
        }

        return true;
    };
    
    auto WriteEntry = [output](const Path& path)
    {
        output->WriteData(path.CStr(), path.Length());
        output->WriteData<char>('\n');
        output->ParseLines();
    };

    dirent* ent;
    while ((ent = readdir(d)) != nullptr) {
        if (ent->d_type == DT_DIR) {
            if (strIsEqual(ent->d_name, ".") || strIsEqual(ent->d_name, ".."))
                continue;

            Path subdirPath = Path::Join(dirPath, ent->d_name);

            if (!data->ignoreDirectories)
                WriteEntry(subdirPath);

            if (data->recursive) {
                DIR* subdir = opendir(subdirPath.CStr());
                if (subdir) {
                    ListDir_GetListing(subdirPath, data, output, extensions, excludeExtensions, subdir);
                    closedir(subdir);
                }
            }
        }
        else {
            if (!data->onlyDirectories && IsAcceptableFileName(ent->d_name))
                WriteEntry(Path::Join(dirPath, ent->d_name));
        }
    }
}

bool Node_ListDir::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    
    MemTempAllocator tmpAlloc;
    char extensionsStr[sizeof(data->extensions)];
    char excludeExtensionsStr[sizeof(data->excludeExtensions)];
    strCopy(extensionsStr, sizeof(extensionsStr), data->extensions);
    strCopy(excludeExtensionsStr, sizeof(excludeExtensionsStr), data->excludeExtensions);
    strReplaceChar(extensionsStr, sizeof(extensionsStr), '*', ' ');
    strReplaceChar(excludeExtensionsStr, sizeof(excludeExtensionsStr), '*', ' ');

    Span<char*> extensions = strSplit(extensionsStr, ' ', &tmpAlloc);
    Span<char*> excludeExtensions = strSplit(excludeExtensionsStr, ' ', &tmpAlloc);

    Pin& dirPin = ngGetPinData(graph, inPins[0]);

    if (dirPin.data.str[0] == 0 || !pathIsDir(dirPin.data.str)) {
        strPrintFmt(data->errorMsg, sizeof(data->errorMsg), "Invalid directory: %s", dirPin.data.str);
        return false;
    }

    DIR* d = opendir(dirPin.data.str);
    if (!d) {
        strPrintFmt(data->errorMsg, sizeof(data->errorMsg), "Cannot open directory: %s", dirPin.data.str);
        return false;
    }

    size_t startOffset;
    TextContent* output = node.outputText;
    if (node.IsFirstTimeRun())
        output->Reset();
    else if (output->mBlob.Size())
        output->mBlob.SetSize(output->mBlob.Size() - 1);    // Remove the last null-terminator
    startOffset = output->mBlob.Size();

    ListDir_GetListing(Path(dirPin.data.str), data, output, extensions, excludeExtensions, d);
    closedir(d);

    output->WriteData<char>('\0');
    output->ParseLines();

    Pin& outListingPin = ngGetPinData(graph, outPins[0]);
    Pin& outDirPin = ngGetPinData(graph, outPins[1]);

    outListingPin.data.SetString((const char*)output->mBlob.Data() + startOffset);
    outListingPin.ready = true;

    outDirPin.data.CopyFrom(dirPin.data);
    outDirPin.ready = true;

    return true;
}


void Node_ListDir::SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    sjson_put_string(jctx, jparent, "Extensions", data->extensions);
    sjson_put_string(jctx, jparent, "ExcludeExtensions", data->excludeExtensions);
    sjson_put_bool(jctx, jparent, "Recursive", data->recursive);
    sjson_put_bool(jctx, jparent, "IgnoreDirectories", data->ignoreDirectories);
    sjson_put_bool(jctx, jparent, "OnlyDirectories", data->onlyDirectories);
}

bool Node_ListDir::LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    strCopy(data->extensions, sizeof(data->extensions), sjson_get_string(jparent, "Extensions", ""));
    strCopy(data->excludeExtensions, sizeof(data->excludeExtensions), sjson_get_string(jparent, "ExcludeExtensions", ""));
    data->recursive = sjson_get_bool(jparent, "Recursive", false);
    data->ignoreDirectories = sjson_get_bool(jparent, "IgnoreDirectories", false);
    data->onlyDirectories = sjson_get_bool(jparent, "OnlyDirectories", false);

    return true;
}

const char* Node_ListDir::GetLastError(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    return data->errorMsg;
}

void Node_ListDir::Register()
{
    static Node_ListDir self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
// Node_TranslateString
bool Node_TranslateString::Initialize(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    node.data = data;

    data->items.SetAllocator(memDefaultAlloc());
    strCopy(data->title, sizeof(data->title), node.desc.name);
    
    return true;
}

bool Node_TranslateString::InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    node.data = data;

    data->items.SetAllocator(memDefaultAlloc());

    Data* copyData = (Data*)srcData;
    strCopy(data->title, sizeof(data->title), copyData->title);
    copyData->items.CopyTo(&data->items);
    
    return true;
}

void Node_TranslateString::Release(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    data->items.Free();
}

const char* Node_TranslateString::GetTitleUI(NodeGraph* graph, NodeHandle handle)
{
    Node& node = ngGetNodeData(graph, handle);
    Data* data = (Data*)node.data;
    return data->title;
}

bool Node_TranslateString::ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    
    ImGui::InputText("Title", data->title, sizeof(data->title), ImGuiInputTextFlags_CharsNoBlank);
    ImGui::Separator();
    
    if (ImGui::Button(ICON_FA_PLUS_SQUARE)) {
        data->items.Push(Item{});
    }

    MemTempAllocator tmpAlloc;
    bool isValueEmpty = false;
    for (uint32 i = 0; i < data->items.Count(); i++) {
        Item& item = data->items[i];
        char idStr[32];

        strPrintFmt(idStr, sizeof(idStr), "##cond_%u", i);
        int selectedCond = int(item.cond);
        ImGui::SetNextItemWidth(150);
        if (ImGui::Combo(idStr, &selectedCond, ConditionStr, int(Condition::_Count))) {
            item.cond = Condition(selectedCond);
        }        
        ImGui::SameLine();

        strPrintFmt(idStr, sizeof(idStr), "Value###value_%u", i);
        ImGui::SetNextItemWidth(200);
        if (ImGui::InputText(idStr, item.value.Ptr(), sizeof(item.value))) 
            item.value.Trim();
        
        item.value.CalcLength();
        isValueEmpty |= item.value.IsEmpty();
        ImGui::SameLine();

        ImGui::TextUnformatted(ICON_FA_ARROW_RIGHT);
        ImGui::SameLine();

        ImGui::SetNextItemWidth(200);
        strPrintFmt(idStr, sizeof(idStr), "##output_%u", i);
        if (ImGui::InputText(idStr, item.output.Ptr(), item.output.Capacity())) 
            item.output.Trim();

        ImGui::SameLine();
        strPrintFmt(idStr, sizeof(idStr), "btn_%u", i);
        ImGui::PushID(idStr);
        if (ImGui::Button(ICON_FA_MINUS_SQUARE)) {
            data->items.Pop(i--);
        }
        ImGui::PopID();
    }

    if (isValueEmpty)
        return false;

    return true;
}

bool Node_TranslateString::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    Pin& valuePin = ngGetPinData(graph, inPins[0]);
    Pin& outPin = ngGetPinData(graph, outPins[0]);

    if (data->items.Count() == 0) {
        strCopy(data->errorMsg, sizeof(data->errorMsg), "There are no mapping items for this node. You should at least add one");
        return false;
    }

    for (Item& item : data->items) {
        switch (item.cond) {
        case Condition::Equal:
            if (strIsEqual(valuePin.data.str, item.value.CStr())) {
                outPin.data.SetString(item.output.CStr());;
                outPin.ready = true;
            }
            break;

        case Condition::EqualIgnoreCase:
            if (strIsEqualNoCase(valuePin.data.str, item.value.CStr())) {
                outPin.data.SetString(item.output.CStr());;
                outPin.ready = true;
            }
            break;

        case Condition::NotEqual:
            if (!strIsEqual(valuePin.data.str, item.value.CStr())) {
                outPin.data.SetString(item.output.CStr());;
                outPin.ready = true;
            }
            break;
        default:
            ASSERT(0);
            break;
        }
    }

    // If input text doesn't meet any condition, just pass it through
    if (!outPin.ready) {
        outPin.data.SetString(valuePin.data.str);
        outPin.ready = true;
    }

    return true;
}

const char* Node_TranslateString::GetLastError(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    return data->errorMsg;
}

void Node_TranslateString::SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    
    sjson_put_string(jctx, jparent, "Title", data->title);
    sjson_node* jitems = sjson_put_array(jctx, jparent, "Items");
    for (const Item& item : data->items) {
        sjson_node* jitem = sjson_mkobject(jctx);
        sjson_put_string(jctx, jitem, "Value", item.value.CStr());
        sjson_put_int(jctx, jitem, "Condition", int(item.cond));
        sjson_put_string(jctx, jitem, "Output", item.output.CStr());
        sjson_append_element(jitems, jitem);
    }
}

bool Node_TranslateString::LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;

    strCopy(data->title, sizeof(data->title), sjson_get_string(jparent, "Title", node.desc.name));
    sjson_node* jitems = sjson_find_member(jparent, "Items");
    if (jitems) {
        sjson_node* jitem = sjson_first_child(jitems);
        while (jitem) {
            Item item {};
            item.value = sjson_get_string(jitem, "Value", "");
            item.cond = Condition(sjson_get_int(jitem, "Condition", 0));
            item.output = sjson_get_string(jitem, "Output", "");
            data->items.Push(item);

            jitem = jitem->next;
        }
    }
    return true;
}

void Node_TranslateString::Register()
{
    static Node_TranslateString self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
// Node_SetEnvVar
bool Node_SetEnvVar::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    // Node& node = ngGetNodeData(graph, nodeHandle);
    Pin& namePin = ngGetPinData(graph, inPins[0]);
    Pin& valuePin = ngGetPinData(graph, inPins[1]);

    bool r = sysSetEnvVar(namePin.data.str, valuePin.data.str);
    if (r)
        ngGetPinData(graph, outPins[0]).ready = true;

    return r;
}

void Node_SetEnvVar::Register()
{
    static Node_SetEnvVar self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------\
// Node_GetEnvVar
bool Node_GetEnvVar::Initialize(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    node.data = data;
    return true;
}

bool Node_GetEnvVar::InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    memcpy(data, srcData, sizeof(Data));
    node.data = data;
    return true;
}

void Node_GetEnvVar::Release(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    memFree(node.data);
}

const char* Node_GetEnvVar::GetTitleUI(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    
    strPrintFmt(data->title, sizeof(data->title), "EnvVar: %s", data->name[0] ? data->name : "[None]");
    return data->title;
}

bool Node_GetEnvVar::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Pin& valuePin = ngGetPinData(graph, outPins[0]);
    Data* data = (Data*)node.data;
    
    MemTempAllocator tmpAlloc;
    char* value = tmpAlloc.MallocTyped<char>(32*kKB);
    if (sysGetEnvVar(data->name, value, 32*kKB)) {
        valuePin.data.SetString(value);
        valuePin.ready = true;

        return true;
    }
    else {
        return false;
    }
}

bool Node_GetEnvVar::ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) 
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    ImGui::InputText("Name", data->name, sizeof(data->name), ImGuiInputTextFlags_CharsNoBlank);
    return true;
}

void Node_GetEnvVar::SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    sjson_put_string(jctx, jparent, "VarName", data->name);
}

bool Node_GetEnvVar::LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    strCopy(data->name, sizeof(data->name), sjson_get_string(jparent, "VarName", ""));
    return true;
}

const char* Node_GetEnvVar::GetLastError(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    static char errorMsg[128];
    strPrintFmt(errorMsg, sizeof(errorMsg), "EnvironmentVariable '%s' not found", data->name);
    return errorMsg;
}

void Node_GetEnvVar::Register()
{
    static Node_GetEnvVar self;
    ngRegisterNode(Desc, &self);
}

//----------------------------------------------------------------------------------------------------------------------
// Node_GetSettingsVar
bool Node_GetSettingsVar::Initialize(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    node.data = data;
    return true;
}

bool Node_GetSettingsVar::InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = memAllocZeroTyped<Data>();
    memcpy(data, srcData, sizeof(Data));
    node.data = data;
    return true;
}

void Node_GetSettingsVar::Release(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    memFree(node.data);
}

const char* Node_GetSettingsVar::GetTitleUI(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    
    strPrintFmt(data->title, sizeof(data->title), "SettingsVar: %s", data->name[0] ? data->name : "[None]");
    return data->title;
}

bool Node_GetSettingsVar::Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Pin& valuePin = ngGetPinData(graph, outPins[0]);
    Data* data = (Data*)node.data;
    
    MemTempAllocator tmpAlloc;
    Span<char*> path = strSplit(data->name, '/', &tmpAlloc);
    if (path.Count() > 1) {
        const char* category = path[0];
        const char* name = path[1];
        const char* value = GetWorkspaceSettingByCategoryName(category, name);
        if (!value)
            return false;
        
        valuePin.data.SetString(value);
        valuePin.ready = true;
        return true;
    }
    else {
        return false;
    }
}

bool Node_GetSettingsVar::ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    ImGui::InputText("Name", data->name, sizeof(data->name), ImGuiInputTextFlags_CharsNoBlank);
    return true;
}

void Node_GetSettingsVar::SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    sjson_put_string(jctx, jparent, "SettingName", data->name);
}

bool Node_GetSettingsVar::LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    strCopy(data->name, sizeof(data->name), sjson_get_string(jparent, "SettingName", ""));
    return true;
}

const char* Node_GetSettingsVar::GetLastError(NodeGraph* graph, NodeHandle nodeHandle)
{
    Node& node = ngGetNodeData(graph, nodeHandle);
    Data* data = (Data*)node.data;
    static char errorMsg[128];
    strPrintFmt(errorMsg, sizeof(errorMsg), "SettingsVariable '%s' not found", data->name);
    return errorMsg;
}

void Node_GetSettingsVar::Register()
{
    static Node_GetSettingsVar self;
    ngRegisterNode(Desc, &self);
}
