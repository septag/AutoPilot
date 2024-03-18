#include "BuiltinProps.h"

#include "External/sjson/sjson.h"
#include "Core/Blobs.h"

#include "Main.h"
#include "NodeGraph.h"
#include "ImGui/ImGuiAll.h"

static inline const char* GetPropName(const Property& prop)
{
    const char* name = GetString(prop.pinName);
    if (name[0] == 0)
        name = prop.desc.name;
    return name;
}

struct NodeGraphVoidProp final : PropertyImpl
{
    void ShowUI(NodeGraph* graph, PropertyHandle propHandle, float) override 
    {
        ImGui::TextUnformatted("Execute");
    }

    bool Initialize(NodeGraph* graph, PropertyHandle) override {  return true; };
    void Release(NodeGraph* graph, PropertyHandle) override {}
    bool ShowCreateUI(NodeGraph* graph, PropertyHandle propHandle, PinData& initialDataInOut) override { return true; }
    void InitializeDataFromPin(NodeGraph* graph, PropertyHandle propHandle) override {}
    void SaveDataToJson(NodeGraph* graph, PropertyHandle propHandle, sjson_context* jctx, sjson_node* jparent) override {}
    bool LoadDataFromJson(NodeGraph* graph, PropertyHandle propHandle, sjson_context* jctx, sjson_node* jparent) override { return true; }
    void CopyInternalData(NodeGraph* graph, PropertyHandle propHandle, const void* srcData) override {}
};

struct NodeGraphBooleanProp final : PropertyImpl
{
    void ShowUI(NodeGraph* graph, PropertyHandle propHandle, float) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        Pin& pin = ngGetPinData(graph, prop.pin);
        ImGui::Checkbox(GetPropName(prop), &pin.data.b);
    }

    bool ShowCreateUI(NodeGraph* graph, PropertyHandle propHandle, PinData& initialDataInOut) override
    {
        ImGui::Checkbox("Default", &initialDataInOut.b);
        return true;
    }

    bool Initialize(NodeGraph* graph, PropertyHandle) override {  return true; }
    void Release(NodeGraph* graph, PropertyHandle) override {}
    void InitializeDataFromPin(NodeGraph* graph, PropertyHandle propHandle) override {}
    void SaveDataToJson(NodeGraph* graph, PropertyHandle propHandle, sjson_context* jctx, sjson_node* jparent) override {}
    bool LoadDataFromJson(NodeGraph* graph, PropertyHandle propHandle, sjson_context* jctx, sjson_node* jparent) override { return true; }
    void CopyInternalData(NodeGraph* graph, PropertyHandle propHandle, const void* data) override {}
};

struct NodeGraphIntProp final : PropertyImpl
{
    void ShowUI(NodeGraph* graph, PropertyHandle propHandle, float) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        Pin& pin = ngGetPinData(graph, prop.pin);
        ImGui::InputInt(GetPropName(prop), &pin.data.n);
    }

    bool ShowCreateUI(NodeGraph* graph, PropertyHandle propHandle, PinData& initialDataInOut) override
    {
        ImGui::InputInt("Default", &initialDataInOut.n);
        return true;
    }

    void InitializeDataFromPin(NodeGraph* graph, PropertyHandle propHandle) override {}
    bool Initialize(NodeGraph* graph, PropertyHandle) override   {  return true; };
    void Release(NodeGraph* graph, PropertyHandle) override       {}
    void SaveDataToJson(NodeGraph* graph, PropertyHandle propHandle, sjson_context* jctx, sjson_node* jparent) override {}
    bool LoadDataFromJson(NodeGraph* graph, PropertyHandle propHandle, sjson_context* jctx, sjson_node* jparent) override { return true; }
    void CopyInternalData(NodeGraph* graph, PropertyHandle propHandle, const void* data) override {}
};

struct NodeGraphStringProp final : PropertyImpl
{
    struct Data
    {
        char strEdit[1024];
        char str[1024];
    };

    bool Initialize(NodeGraph* graph, PropertyHandle propHandle) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);

        NodeGraphStringProp::Data* data = memAllocZeroTyped<NodeGraphStringProp::Data>();
        prop.data = data;
    
        return true;
    }

    void Release(NodeGraph* graph, PropertyHandle propHandle) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);

        NodeGraphStringProp::Data* data = (NodeGraphStringProp::Data*)prop.data;
        memFree(data);
    }

    void ShowUI(NodeGraph* graph, PropertyHandle propHandle, float maxWidth) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        Pin& pin = ngGetPinData(graph, prop.pin);
        NodeGraphStringProp::Data* data = (NodeGraphStringProp::Data*)prop.data;
        ImGui::SetNextItemWidth(maxWidth);
        if (ImGui::InputText(GetPropName(prop), data->str, sizeof(data->str))) {
            strTrim(data->str, sizeof(data->str), data->str);
            pin.data.SetString(data->str);
        }
    }

    bool ShowCreateUI(NodeGraph* graph, PropertyHandle propHandle, PinData& initialDataInOut) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        NodeGraphStringProp::Data* data = (NodeGraphStringProp::Data*)prop.data;
        if (ImGui::InputText("Default", data->strEdit, sizeof(data->strEdit))) {
            strTrim(data->strEdit, sizeof(data->strEdit), data->strEdit);
            initialDataInOut.SetString(data->strEdit);
        }

        return true;
    }

    void InitializeDataFromPin(NodeGraph* graph, PropertyHandle propHandle) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        NodeGraphStringProp::Data* data = (NodeGraphStringProp::Data*)prop.data;
        Pin& pin = ngGetPinData(graph, prop.pin);
        ASSERT(pin.data.type == PinDataType::String);
        strCopy(data->str, sizeof(data->str), pin.data.str);
    }

    void SaveDataToJson(NodeGraph* graph, PropertyHandle propHandle, sjson_context* jctx, sjson_node* jparent) override {}
    bool LoadDataFromJson(NodeGraph* graph, PropertyHandle propHandle, sjson_context* jctx, sjson_node* jparent) override { return true; }
    void CopyInternalData(NodeGraph* graph, PropertyHandle propHandle, const void* data) override {}
};

struct NodeGraphEnumProp final : PropertyImpl
{
    struct EnumItem
    {
        String<64> name;
        String<kMaxPath> alias;
    };

    struct Data
    {
        Array<EnumItem> items;
        int selectedItem;
    };

    bool Initialize(NodeGraph* graph, PropertyHandle propHandle) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        Data* data = memAllocZeroTyped<Data>();
        data->items.SetAllocator(memDefaultAlloc());
        prop.data = data;
        return true;
    }

    void Release(NodeGraph* graph, PropertyHandle propHandle) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        Data* data = memAllocZeroTyped<Data>();
        data->items.Free();
        memFree(prop.data);
    }

    void ShowUI(NodeGraph* graph, PropertyHandle propHandle, float maxWidth) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        Pin& pin = ngGetPinData(graph, prop.pin);
        Data* data = (Data*)prop.data;

        if (data->items.Count()) {
            MemTempAllocator tmpAlloc;
            char** itemsStr = tmpAlloc.MallocZeroTyped<char*>();
            for (uint32 i = 0; i < data->items.Count(); i++)
                itemsStr[i] = const_cast<char*>(data->items[i].name.CStr());
            
            ImGui::SetNextItemWidth(maxWidth);
            if (ImGui::Combo(GetPropName(prop), &data->selectedItem, itemsStr, (int)data->items.Count())) {
                const char* value = data->items[data->selectedItem].alias.CStr();
                if (value[0] == '\0')
                    value = data->items[data->selectedItem].name.CStr();
                pin.data.SetString(value);
            }
        }
        else {
            ImGui::TextUnformatted(GetPropName(prop));
        }
    }

    bool ShowCreateUI(NodeGraph* graph, PropertyHandle propHandle, PinData& initialDataInOut) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        Data* data = (Data*)prop.data;

        if (ImGui::Button(ICON_FA_PLUS_SQUARE)) {
            data->items.Push(EnumItem{});
        }

        bool isNameEmpty = false;
        for (uint32 i = 0; i < data->items.Count(); i++) {
            EnumItem& item = data->items[i];
            char idStr[32];
            strPrintFmt(idStr, sizeof(idStr), "Name####name_%u", i);
            ImGui::InputText(idStr, item.name.Ptr(), sizeof(item.name), ImGuiInputTextFlags_CharsNoBlank);
            item.name.CalcLength();
            ImGui::SameLine();
            
            isNameEmpty |= item.name.IsEmpty();

            strPrintFmt(idStr, sizeof(idStr), "Alias###alias_%u", i);
            ImGui::InputText(idStr, item.alias.Ptr(), sizeof(item.alias), ImGuiInputTextFlags_CharsNoBlank);
            item.alias.CalcLength();

            ImGui::SameLine();
            strPrintFmt(idStr, sizeof(idStr), "btn_%u", i);
            ImGui::PushID(idStr);
            if (ImGui::Button(ICON_FA_MINUS_SQUARE)) {
                data->items.Pop(i);
                i--;
            }
            ImGui::PopID();            
        }

        if (data->items.Count()) {
            const char* value = data->items[0].alias.CStr();
            if (value[0] == '\0')
                value = data->items[0].name.CStr();
            initialDataInOut.SetString(value);
        }

        return !isNameEmpty;
    }

    void InitializeDataFromPin(NodeGraph* graph, PropertyHandle propHandle) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        Data* data = (Data*)prop.data;
        Pin& pin = ngGetPinData(graph, prop.pin);
        ASSERT(pin.data.type == PinDataType::String);

        const char* value = pin.data.str;
        for (uint32 i = 0; i < data->items.Count(); i++) {
            const EnumItem& item = data->items[i];
            if ((item.alias.IsEmpty() && item.name == value) || item.alias == value) {
                data->selectedItem = int(i);
                break;
            }
        }
    }

    void SaveDataToJson(NodeGraph* graph, PropertyHandle propHandle, sjson_context* jctx, sjson_node* jparent) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        Data* data = (Data*)prop.data;

        sjson_node* jitems = sjson_put_array(jctx, jparent, "Items");
        for (uint32 i = 0; i < data->items.Count(); i++) {
            sjson_node* jitem = sjson_mkobject(jctx);
            sjson_put_string(jctx, jitem, "Name", data->items[i].name.CStr());
            if (!data->items[i].alias.IsEmpty())
                sjson_put_string(jctx, jitem, "Alias", data->items[i].alias.CStr());
            sjson_append_element(jitems, jitem);
        }
    }

    bool LoadDataFromJson(NodeGraph* graph, PropertyHandle propHandle, sjson_context* jctx, sjson_node* jparent) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        Data* data = (Data*)prop.data;
        data->items.Clear();

        sjson_node* jitems = sjson_find_member(jparent, "Items");
        if (jitems) {
            sjson_node* jitem = sjson_first_child(jitems);

            while (jitem) {
                EnumItem item;
                item.name = sjson_get_string(jitem, "Name", "");
                ASSERT_MSG(!item.name.IsEmpty(), "Something went wrong! 'Name' cannot be empty");
                item.alias = sjson_get_string(jitem, "Alias", "");

                data->items.Push(item);

                jitem = jitem->next;
            }
        }

        return true;
    }

    void CopyInternalData(NodeGraph* graph, PropertyHandle propHandle, const void* srcData) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        Data* data = (Data*)prop.data;

        Data* _srcData = (Data*)srcData;
        _srcData->items.CopyTo(&data->items);
        data->selectedItem = _srcData->selectedItem;
    }
};

struct NodeGraphMultiSelectProp final : PropertyImpl
{
    struct Item
    {
        String<64> name;
    };

    struct Data
    {
        Array<Item> items;
        Array<uint32> selectedItems;
    };

    bool Initialize(NodeGraph* graph, PropertyHandle propHandle) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        Data* data = memAllocZeroTyped<Data>();
        data->items.SetAllocator(memDefaultAlloc());
        data->selectedItems.SetAllocator(memDefaultAlloc());
        prop.data = data;
        return true;
    }

    void Release(NodeGraph* graph, PropertyHandle propHandle) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        Data* data = memAllocZeroTyped<Data>();
        data->items.Free();
        data->selectedItems.Free();
        memFree(prop.data);
    }

    void ShowUI(NodeGraph* graph, PropertyHandle propHandle, float maxWidth) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        Pin& pin = ngGetPinData(graph, prop.pin);
        Data* data = (Data*)prop.data;

        if (ImGui::BeginPopupContextItem("MultiSelectPropSelector")) {
            for (uint32 i = 0; i < data->items.Count(); i++) {
                uint32 selIndex = data->selectedItems.Find(i);
                bool selected = selIndex != INVALID_INDEX;
                if (ImGui::MenuItem(data->items[i].name.CStr(), nullptr, &selected)) {
                    if (selected) {
                        if (selIndex != INVALID_INDEX)
                            data->selectedItems[selIndex] = true;
                        else
                            data->selectedItems.Push(i);
                    }
                    else if (selIndex != INVALID_INDEX) {
                        data->selectedItems.RemoveAndSwap(selIndex);
                    }

                    // Update the property string
                    MemTempAllocator tmpAlloc;
                    Blob blob(&tmpAlloc);
                    blob.SetGrowPolicy(Blob::GrowPolicy::Linear);
                    for (uint32 k = 0; k < data->selectedItems.Count(); k++) {
                        uint32 selIndex = data->selectedItems[k];
                        blob.Write(data->items[selIndex].name.CStr(), data->items[selIndex].name.Length());
                        if (k < data->selectedItems.Count() - 1)
                            blob.Write<char>(';');
                    }
                    blob.Write<char>('\0');

                    pin.data.SetString((const char*)blob.Data());
                }
            }
            ImGui::EndPopup();
        }

        if (pin.data.str == nullptr)
            pin.data.SetString("");

        ImGui::SetNextItemWidth(maxWidth);
        ImGui::InputText(GetString(prop.pinName), pin.data.str, pin.data.size + 1, ImGuiInputTextFlags_ReadOnly);
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_DOT_CIRCLE_O)) 
            ImGui::OpenPopup("MultiSelectPropSelector");
    }

    bool ShowCreateUI(NodeGraph* graph, PropertyHandle propHandle, PinData& initialDataInOut) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        Data* data = (Data*)prop.data;

        if (ImGui::Button(ICON_FA_PLUS_SQUARE)) {
            data->items.Push(Item{});
        }

        bool isNameEmpty = false;
        for (uint32 i = 0; i < data->items.Count(); i++) {
            Item& item = data->items[i];
            char idStr[32];
            strPrintFmt(idStr, sizeof(idStr), "Name####name_%u", i);
            ImGui::InputText(idStr, item.name.Ptr(), sizeof(item.name), ImGuiInputTextFlags_CharsNoBlank);
            item.name.CalcLength();
            ImGui::SameLine();
            
            isNameEmpty |= item.name.IsEmpty();

            strPrintFmt(idStr, sizeof(idStr), "btn_%u", i);
            ImGui::PushID(idStr);
            if (ImGui::Button(ICON_FA_MINUS_SQUARE)) {
                data->items.Pop(i);
                i--;
            }
            ImGui::PopID();            
        }

        return !isNameEmpty;
    }

    void InitializeDataFromPin(NodeGraph* graph, PropertyHandle propHandle) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        Data* data = (Data*)prop.data;
        Pin& pin = ngGetPinData(graph, prop.pin);
        ASSERT(pin.data.type == PinDataType::String);
        data->selectedItems.Clear();

        auto FindInItems = [data](const char* value)->uint32 {
            for (uint32 i = 0; i < data->items.Count(); i++) {
                const Item& item = data->items[i];
                if (item.name == value) 
                    return i;
            }
            return UINT32_MAX;
        };

        // split string by ';' and look up each item 
        const char* value = pin.data.str;
        const char* split = strFindChar(value, ';');
        while (split) {
            if (value < split) {
                char name[64];
                strCopyCount(name, sizeof(name), value, (uint32)uintptr(split - value));
                uint32 index = FindInItems(name);
                if (index != INVALID_INDEX)
                    data->selectedItems.Push(index);
            }

            value = split + 1;
            split = strFindChar(split + 1, ';');
        }

        uint32 index = FindInItems(value);
        if (index != INVALID_INDEX)
            data->selectedItems.Push(index);        
    }

    void SaveDataToJson(NodeGraph* graph, PropertyHandle propHandle, sjson_context* jctx, sjson_node* jparent) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        Data* data = (Data*)prop.data;

        sjson_node* jitems = sjson_put_array(jctx, jparent, "Items");
        for (uint32 i = 0; i < data->items.Count(); i++) {
            sjson_node* jitem = sjson_mkobject(jctx);
            sjson_put_string(jctx, jitem, "Name", data->items[i].name.CStr());
            sjson_append_element(jitems, jitem);
        }
    }

    bool LoadDataFromJson(NodeGraph* graph, PropertyHandle propHandle, sjson_context* jctx, sjson_node* jparent) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        Data* data = (Data*)prop.data;
        data->items.Clear();

        sjson_node* jitems = sjson_find_member(jparent, "Items");
        if (jitems) {
            sjson_node* jitem = sjson_first_child(jitems);

            while (jitem) {
                Item item;
                item.name = sjson_get_string(jitem, "Name", "");
                ASSERT_MSG(!item.name.IsEmpty(), "Something went wrong! 'Name' cannot be empty");
                data->items.Push(item);
                jitem = jitem->next;
            }
        }

        return true;
    }

    void CopyInternalData(NodeGraph* graph, PropertyHandle propHandle, const void* srcData) override
    {
        Property& prop = ngGetPropertyData(graph, propHandle);
        Data* data = (Data*)prop.data;

        Data* _srcData = (Data*)srcData;
        _srcData->items.CopyTo(&data->items);
        _srcData->selectedItems.CopyTo(&data->selectedItems);
    }

};


PropertyImpl* _private::GetVoidPropImpl()
{
    static NodeGraphVoidProp voidProp;
    return &voidProp;
}

void RegisterBuiltinProps()
{
    static NodeGraphBooleanProp booleanProp;
    static NodeGraphIntProp intProp;
    static NodeGraphStringProp strProp;
    static NodeGraphEnumProp enumProp;
    static NodeGraphMultiSelectProp multiSelProp;

    ngRegisterProperty(PropertyDesc { 
        .name = "Boolean",
        .description = "Boolean on/off option",
        .dataType = PinDataType::Boolean
    }, &booleanProp);

    ngRegisterProperty(PropertyDesc {
        .name = "Int",
        .description = "Signed integer value",
        .dataType = PinDataType::Integer
    }, &intProp);

    ngRegisterProperty(PropertyDesc {
        .name = "String",
        .description = "String value",
        .dataType = PinDataType::String
    }, &strProp);

    ngRegisterProperty(PropertyDesc {
        .name = "Enum",
        .description = "Enum value",
        .dataType = PinDataType::String
    }, &enumProp);

    ngRegisterProperty(PropertyDesc {
        .name = "MultiSelect",
        .description = "Select multiple items",
        .dataType = PinDataType::String
    }, &multiSelProp);

}
