#pragma once

#include "Core/Base.h"

API void RegisterBuiltinProps();

struct PropertyImpl;
namespace _private 
{
    PropertyImpl* GetVoidPropImpl();
}