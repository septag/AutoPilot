#pragma once

#include "Core/Pools.h"

using StringId = uint64;

#ifndef __OBJC__
DEFINE_HANDLE(PinHandle);
DEFINE_HANDLE(NodeHandle);
DEFINE_HANDLE(LinkHandle);
DEFINE_HANDLE(PropertyHandle);

DEFINE_HANDLE(WksFolderHandle);
DEFINE_HANDLE(WksFileHandle);

DEFINE_HANDLE(TskGraphHandle);
DEFINE_HANDLE(TskEventHandle);
#endif
