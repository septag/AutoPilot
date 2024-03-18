#pragma once

#include "Core/Blobs.h"
#include "NodeGraph.h"

struct ImGuiInputTextCallbackData;

API void RegisterBuiltinNodes();

struct Node_DebugMessage final : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "Text",
            .data = { .type = PinDataType::String }
        },
    };

    inline static const NodeDesc Desc = {
        .name = "DebugMessage",
        .description = "Output debug message",
        .category = "Debug",
        .numInPins = CountOf(InPins),
        .numOutPins = 0
    };

    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    static void Register();

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override { return true; }
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override {}
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override { return nullptr; }
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override { return nullptr; }
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return kEmptyPin; }
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override {}
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override { return true; }
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}
};

struct Node_UpperCase final : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "Text",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "Output",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "Uppercase",
        .description = "Turns input string into upper case",
        .category = "String",
        .numInPins = CountOf(InPins),
        .numOutPins = CountOf(OutPins),
    };

    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    static void Register();

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override { return true; }
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override {}
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override { return nullptr; }
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override { return nullptr; }
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override {}
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override { return true; }
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}
};

struct Node_LowerCase : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "Text",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "Output",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "Lowercase",
        .description = "Turns input string into lower case",
        .category = "String",
        .numInPins = CountOf(InPins),
        .numOutPins = CountOf(OutPins),
    };

    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    static void Register();

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override { return true; }
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override {}
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override { return nullptr; }
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override { return nullptr; }
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override {}
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override { return true; }
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}
};


struct Node_CreateProcess final : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "Execute",
            .data = { .type = PinDataType::Void }
        },
        {
            .name = "Command",
            .data = { .type = PinDataType::String },
            .optional = true
        },
        {
            .name = "CWD", 
            .data = { .type = PinDataType::String },
            .optional= true
        },
        {
            .name = "Arg",
            .data = { .type = PinDataType::String },
            .optional = true
        }
    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "Execute",
            .data = { .type = PinDataType::Void }
        },
        {
            .name = "Output",
            .data = { .type = PinDataType::String }
        },
        {
            .name = "ReturnCode",
            .data = { .type = PinDataType::Integer }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "CreateProcess",
        .description = "",
        .category = "System",
        .numInPins = CountOf(InPins),
        .numOutPins = CountOf(OutPins),
        .captureOutput = true,
        .dynamicInPins = true,
        .editable = true
    };

    struct Data
    {
        // props
        char executeCmd[2048];
        char title[64];
        int  successRetCode;
        bool checkRetCode;
        bool fatalErrorOnFail;
        bool runInCmd;

        // runtime
        int  cmdTextInputWidth;
        char errorStr[1024];
        SysProcess* runningProc;
        int textSelectionStart;
        int textSelectionEnd;
        int textCursor;
        bool refocus;
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override;
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override;
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override;
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override;
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}

    static int CmdEditCallback(ImGuiInputTextCallbackData* data);
    static void Register();
};

#if PLATFORM_WINDOWS
struct Node_ShellExecute final : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "Execute",
            .data = { .type = PinDataType::Void }
        },
        {
            .name = "Command",
            .data = { .type = PinDataType::String }
        },
        {
            .name = "CWD", 
            .data = { .type = PinDataType::String },
            .optional= true
        },
        {
            .name = "Arg",
            .data = { .type = PinDataType::String },
            .optional = true
        }
    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "Execute",
            .data = { .type = PinDataType::Void }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "ShellExecute",
        .description = "",
        .category = "System",
        .numInPins = CountOf(InPins),
        .numOutPins = CountOf(OutPins),
        .dynamicInPins = true,
        .editable = true
    };

    struct Data
    {
        // props
        char executeArgs[2048];
        char title[64];
        char operation[32];
        bool fatalErrorOnFail;
        bool runAsAdmin;

        // runtime
        char errorStr[1024];
        SysProcess* runningProc;
        int selectedOp;
        int textSelectionStart;
        int textSelectionEnd;
        int textCursor;
        bool refocus;
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override;
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override;
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override;
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}

    static int CmdEditCallback(ImGuiInputTextCallbackData* data);
    static void Register();
};
#endif // PLATFORM_WINDOWS

struct Node_JoinString final : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "JoinA",
            .data = { .type = PinDataType::String }
        },
        {
            .name = "JoinB",
            .data = { .type = PinDataType::String },
            .optional = true
        }
    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "Output",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "JoinString",
        .description = "",
        .category = "String",
        .numInPins = CountOf(InPins),
        .numOutPins = CountOf(OutPins),
        .dynamicInPins = true,
        .editable = true
    };

    struct Data
    {
        // runtime
        Blob str;
        char errDesc[64];

        // props
        char joinStr[16];
        bool isDirectory;
        bool isUnixPath;
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override;
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override;
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override { return nullptr; }
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}
    static void Register();
};

struct Node_JoinStringArray final : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "Join",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "Output",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "JoinStringArray",
        .description = "",
        .category = "String",
        .numInPins = CountOf(InPins),
        .numOutPins = CountOf(OutPins),
        .absorbsLoop = true,
        .editable = true
    };

    struct Data
    {
        // runtime
        Blob str;
        
        // props
        char joinStr[16];
        bool isDirectory;
        bool isUnixPath;
        bool prepend;
        bool append;
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override;
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override { return nullptr; }
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override;
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override { return nullptr; }
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}
    static void Register();
};


struct Node_SplitString final : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "Value",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "Output",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "SplitString",
        .description = "",
        .category = "String",
        .numInPins = CountOf(InPins),
        .numOutPins = CountOf(OutPins),
        .loop = true,
        .editable = true
    };

    struct Data
    {
        uint32 strOffset;
        const char* errorStr;
        char splitChar;
        int ignoreFirstElems;   // TODO
        int ignoreLastElems;    // TODO
        int maxElems;           // TODO
        bool splitNewLines;
        bool ignoreWhitespace;
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override;
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override;
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override { return nullptr; }
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}

    static void Register();
};

struct Node_SplitPath final : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "Path",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "Directory",
            .data = { .type = PinDataType::String }
        },
        {
            .name = "FilenameExt",
            .data = { .type = PinDataType::String }
        },
        {
            .name = "Filename",
            .data = { .type = PinDataType::String }
        },
        {
            .name = "FileExtension",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "SplitPath",
        .description = "",
        .category = "String",
        .numInPins = CountOf(InPins),
        .numOutPins = CountOf(OutPins)
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override { return true; }
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override {}
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override { return nullptr; }
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override { return nullptr; }
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override {}
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override { return true; }
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}

    static void Register(); 
};

struct Node_IsFile final : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "FilePath",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "Yes",
            .data = { .type = PinDataType::Void }
        },
        {
            .name = "No",
            .data = { .type = PinDataType::Void }
        },
        {
            .name = "FilePath",
            .data = { .type = PinDataType::String }
        },
        {
            .name = "FileSize",
            .data = { .type = PinDataType::Integer }
        },
        {
            .name = "LastModifiedDate",
            .data = { .type = PinDataType::Integer }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "IsFile",
        .description = "Checks if the file exists and valid. Also gets basic file information",
        .category = "FileSystem",
        .numInPins = CountOf(InPins),
        .numOutPins = CountOf(OutPins)
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override { return true; }
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override {}
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override { return nullptr; }
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override { return nullptr; }
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override {}
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override { return true; }
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}
    static void Register(); 
};

struct Node_IsDir : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "DirPath",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "Yes",
            .data = { .type = PinDataType::Void }
        },
        {
            .name = "No",
            .data = { .type = PinDataType::Void }
        },
        {
            .name = "DirPath",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "IsDir",
        .description = "Checks if the directory exists and valid",
        .category = "FileSystem",
        .numInPins = CountOf(InPins),
        .numOutPins = CountOf(OutPins)
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override { return true; }
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override {}
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override { return nullptr; }
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override { return nullptr; }
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override {}
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override { return true; }
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}
    static void Register(); 
};

struct Node_BoolIf final : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "Value",
            .data = { .type = PinDataType::Boolean }
        },
        {
            .name = "Execute",
            .data = { .type = PinDataType::Void },
            .optional = true
        }

    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "Yes",
            .data = { .type = PinDataType::Boolean }
        },
        {
            .name = "No",
            .data = { .type = PinDataType::Boolean }
        }
    };
   
    inline static const NodeDesc Desc = {
        .name = "IsBooleanTrue",
        .description = "Simply checks if the input boolean value is true and branch it",
        .category = "Common",
        .numInPins = CountOf(InPins),
        .numOutPins = CountOf(OutPins)
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override { return true; }
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override {}
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override { return nullptr; }
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override { return nullptr; }
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override {}
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override { return true; }
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}
    static void Register(); 
};

struct Node_BoolNegate : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "Value",
            .data = { .type = PinDataType::Boolean }
        }
    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "NegValue",
            .data = { .type = PinDataType::Boolean }
        }
    };
   
    inline static const NodeDesc Desc = {
        .name = "NegateBoolean",
        .description = "Negates a boolean value",
        .category = "Common",
        .numInPins = CountOf(InPins),
        .numOutPins = CountOf(OutPins)
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override { return true; }
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override {}
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override { return nullptr; }
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override { return nullptr; }
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override {}
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override { return true; }
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}
    static void Register(); 
};

struct Node_MathCounter final : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "Input",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "Counter",
            .data = { .type = PinDataType::Integer }
        },
        {
            .name = "Output",
            .data = { .type = PinDataType::String }
        },
    };
   
    inline static const NodeDesc Desc = {
        .name = "MathCounter",
        .description = "Increases the counter everytime it's executed",
        .category = "Math",
        .numInPins = CountOf(InPins),
        .numOutPins = CountOf(OutPins),
        .editable = true
    };

    struct Data
    {
        int counter;
        int start;
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override;
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override { return nullptr; }
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override;
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override { return nullptr; }
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}
    static void Register(); 
};


struct Node_CompareString final : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "ValueA",
            .data = { .type = PinDataType::String }
        },
        {
            .name = "ValueB",
            .data = { .type = PinDataType::String }
        }

    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "Yes",
            .data = { .type = PinDataType::Void }
        },
        {
            .name = "No",
            .data = { .type = PinDataType::Void }
        },
        {
            .name = "ValueA",
            .data = { .type = PinDataType::String }
        },
        {
            .name = "ValueB",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "CompareString",
        .description = "Compares two strings",
        .category = "String",
        .numInPins = CountOf(InPins),
        .numOutPins = CountOf(OutPins),
        .editable = true
    };

    enum class Mode : int
    {
        Normal = 0,
        BeginsWith,
        EndsWith,
        _Count 
    };

    struct Data
    {
        Mode mode;
        bool ignoreCase;
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override;
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override;
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override { return nullptr; }
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override { return nullptr; }
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}
    static void Register(); 
};

struct Node_StringConstant final : NodeImpl
{
    inline static const PinDesc OutPins[] = {
        {
            .name = "Value",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "StringConstant",
        .description = "",
        .category = "Constant",
        .numInPins = 0,
        .numOutPins = CountOf(OutPins),
        .editable = true,
        .constant = true
    };

    struct Data
    {
        char varName[64];
        char value[kMaxPath];
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override;
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override;
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override;
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override;

    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    const PinDesc& GetInputPin(uint32 index) override { return kEmptyPin; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override { return nullptr; }
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}
    static void Register(); 
};

struct Node_Constants final : NodeImpl
{
    inline static const PinDesc OutPins[] = {
        {
            .name = "Value",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "Constants",
        .description = "",
        .category = "Constant",
        .numInPins = 0,
        .numOutPins = CountOf(OutPins),
        .dynamicOutPins = true,
        .editable = true,
        .constant = true
    };

    struct Item
    {
        char value[256];
        uint32 outputPinIndex;
    };

    struct Data
    {
        char title[64];
        Array<Item> items;
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override;
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override;
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override;
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override;

    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    const PinDesc& GetInputPin(uint32 index) override { return kEmptyPin; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override { return nullptr; }
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}
    static void Register(); 
};


struct Node_IntConstant final : NodeImpl
{
    inline static const PinDesc OutPins[] = {
        {
            .name = "Value",
            .data = { .type = PinDataType::Integer }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "IntConstant",
        .description = "",
        .category = "Constant",
        .numInPins = 0,
        .numOutPins = CountOf(OutPins),
        .editable = true,
        .constant = true
    };

    struct Data
    {
        char varName[64];
        int value;
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override;
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override;
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override;
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override;

    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    const PinDesc& GetInputPin(uint32 index) override { return kEmptyPin; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override { return nullptr; }
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}
    static void Register(); 
};

struct Node_Selector final : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "Value",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "Execute",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "Selector",
        .description = "Matches the input string to s",
        .category = "Common",
        .numInPins = 1,
        .numOutPins = 1,
        .dynamicOutPins = true,
        .editable = true
    };

    // Note: Don't change the ordering here, it will break the data
    enum class Condition : int
    {
        Equal = 0,
        EqualIgnoreCase,
        NotEqual,
        _Count
    };

    inline static const char* ConditionStr[int(Condition::_Count)] = {
        "IsEqual",
        "IsEqualIgnoreCase",
        "IsNotEqual"
    };

    struct SelectorItem
    {
        Condition cond;
        String<64> value;
        uint32 outputPinIndex;
    };

    struct Data
    {
        char title[64];
        Array<SelectorItem> items;
        char errorMsg[512];
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override;
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override;
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override;
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override;
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}
    static void Register(); 
};

struct Node_EmbedGraph final : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "Execute",
            .data = { .type = PinDataType::Void }
        },
        {
            .name = "Input",
            .data = { .type = PinDataType::String },
            .optional = true
        }
    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "Execute",
            .data = { .type = PinDataType::Void }
        },
        {
            .name = "Output",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "EmbedGraph",
        .description = "Runs another graph",
        .category = "Common",
        .numInPins = CountOf(InPins),
        .numOutPins = CountOf(OutPins),
        .captureOutput = true,
        .dynamicInPins = true,
        .editable = true
    };

    struct Data
    {
        Mutex graphMutex;   // TODO: We are currently using this to lock Reload while node is executing. Gotta do a better job
        NodeGraph* graph;
        WksFileHandle fileHandle;
        char title[64];
        char errorMsg[512];
        bool loadError;
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override;
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override;
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override;
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override;
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override;
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}

    void Set(NodeGraph* graph, NodeHandle nodeHandle, NodeGraph* embedGraph, WksFileHandle fileHandle);
    void SetLoadError(NodeGraph* graph, NodeHandle nodeHandle, WksFileHandle fileHandle, const char* errMsg);
    WksFileHandle GetGraphFileHandle(NodeGraph* graph, NodeHandle nodeHandle) const;
    bool ReloadGraph(NodeGraph* graph, NodeHandle handle);

    static void Register();
};

struct Node_FormatString : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "Input",
            .data = { .type = PinDataType::String },
            .optional = true
        }
    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "Output",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "FormatString",
        .description = "",
        .category = "String",
        .numInPins = CountOf(InPins),
        .numOutPins = CountOf(OutPins),
        .captureOutput = true,
        .dynamicInPins = true,
        .editable = true
    };

    struct Data
    {
        // props
        char text[2048];

        // runtime
        char errorStr[1024];
        int textSelectionStart;
        int textSelectionEnd;
        int textCursor;
        bool refocus;
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override;
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override;
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override { return nullptr; }
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override;
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}

    static int CmdEditCallback(ImGuiInputTextCallbackData* data);
    static void Register();
};

struct Node_GraphOutput : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "Result",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "GraphOutput",
        .description = "",
        .category = "Common",
        .numInPins = CountOf(InPins),
        .numOutPins = 0,
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override { return true; }
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override { return nullptr;  }
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override { }
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override { return true; } 
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return kEmptyPin; }
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override { return nullptr; }
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}

    static void Register();
};

struct Node_GraphMetaData : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "Value",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "MetaData",
        .description = "",
        .category = "Common",
        .numInPins = CountOf(InPins),
        .numOutPins = 0
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override { return true; }
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override { return nullptr;  }
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override { }
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override { return true; } 
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return kEmptyPin; }
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override { return nullptr; }
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}

    static void Register();
};

struct Node_ListDir final : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "Directory",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "Listing",
            .data = { .type = PinDataType::String }
        },
        {
            .name = "Directory",
            .data = { . type = PinDataType::String }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "ListDirectory",
        .description = "",
        .category = "FileSystem",
        .numInPins = CountOf(InPins),
        .numOutPins = CountOf(OutPins),
        .captureOutput = true,
        .editable = true
    };

    struct Data
    {
        char errorMsg[256];

        char extensions[256];
        char excludeExtensions[256];
        bool recursive;
        bool ignoreDirectories;
        bool onlyDirectories;
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override;
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override;
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override { return nullptr;  }
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override;
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}

    static void Register();
};

struct Node_TranslateString final : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "Text",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "Output",
            .data= { .type = PinDataType::String }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "TranslateString",
        .description = "",
        .category = "String",
        .numInPins = CountOf(InPins),
        .numOutPins = CountOf(OutPins),
        .editable = true
    };

    // Note: Don't change the ordering here, it will break the data
    enum class Condition : int
    {
        Equal = 0,
        EqualIgnoreCase,
        NotEqual,
        _Count
    };

    inline static const char* ConditionStr[int(Condition::_Count)] = {
        "IsEqual",
        "IsEqualIgnoreCase",
        "IsNotEqual"
    };

    struct Item
    {
        Condition cond;
        String<64> value;
        String<256> output;
    };

    struct Data
    {
        char title[64];
        Array<Item> items;
        char errorMsg[512];
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override;
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override;
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override;
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override;
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}
    static void Register(); 
};

struct Node_SetEnvVar final : NodeImpl
{
    inline static const PinDesc InPins[] = {
        {
            .name = "Name",
            .data = { .type = PinDataType::String }
        },
        {
            .name = "Value",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const PinDesc OutPins[] = {
        {
            .name = "Execute",
            .data = { .type = PinDataType::Void }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "SetEnvironmentVariable",
        .description = "",
        .category = "System",
        .numInPins = CountOf(InPins),
        .numOutPins = CountOf(OutPins)
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override {  return true; }
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override { return nullptr; }
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override { return true; }
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override {}
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override { return true; }
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const PinDesc& GetInputPin(uint32 index) override { return InPins[index]; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override { return nullptr; }
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}
    static void Register(); 
};

struct Node_GetEnvVar final : NodeImpl
{
    inline static const PinDesc OutPins[] = {
        {
            .name = "Value",
            .data = { .type = PinDataType::String }
        }
    }; 

    inline static const NodeDesc Desc = {
        .name = "EnvironmentVariable",
        .description = "",
        .category = "Constant",
        .numInPins = 0,
        .numOutPins = CountOf(OutPins),
        .editable = true,
        .constant = true
    };

    struct Data
    {
        char name[64];
        char title[128];
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override;
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override;
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override;
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const PinDesc& GetInputPin(uint32 index) override { return kEmptyPin; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override;
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}
    static void Register(); 
};

struct Node_GetSettingsVar final : NodeImpl
{
    inline static const PinDesc OutPins[] = {
        {
            .name = "Value",
            .data = { .type = PinDataType::String }
        }
    };

    inline static const NodeDesc Desc = {
        .name = "SettingsVariable",
        .description = "",
        .category = "Constant",
        .numInPins = 0,
        .numOutPins = CountOf(OutPins),
        .editable = true,
        .constant = true
    };

    struct Data
    {
        char name[128];
        char title[128];
    };

    bool Initialize(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool InitializeDuplicate(NodeGraph* graph, NodeHandle nodeHandle, const void* srcData) override;
    void Release(NodeGraph* graph, NodeHandle nodeHandle) override;
    const char* GetTitleUI(NodeGraph* graph, NodeHandle handle) override;
    bool ShowEditUI(NodeGraph* graph, NodeHandle nodeHandle) override;
    bool Execute(NodeGraph* graph, NodeHandle nodeHandle, const Array<PinHandle>& inPins, const Array<PinHandle>& outPins) override;
    void SaveDataToJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    bool LoadDataFromJson(NodeGraph* graph, NodeHandle nodeHandle, sjson_context* jctx, sjson_node* jparent) override;
    void Abort(NodeGraph* graph, NodeHandle nodeHandle) override {}
    const PinDesc& GetInputPin(uint32 index) override { return kEmptyPin; }
    const PinDesc& GetOutputPin(uint32 index) override { return OutPins[index]; }
    const char* GetLastError(NodeGraph* graph, NodeHandle nodeHandle) override;
    void DrawData(NodeGraph* graph, NodeHandle nodeHandle, bool isDebugMode) override {}
    static void Register();

};

