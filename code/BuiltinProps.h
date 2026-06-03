#pragma once

API void RegisterBuiltinProps();

struct PropertyImpl;
namespace _private 
{
    PropertyImpl* GetVoidPropImpl();
}