#pragma once

#ifdef AIR_PLATFORM_WINDOWS
#include <Windows.h>

#define ASSERT(x) if (!x) { } else { DebugBreak(); }

#else
#define ASSERT(x) x
#endif