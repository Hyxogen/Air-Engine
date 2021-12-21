#pragma once

#ifdef AIR_PLATFORM_WINDOWS
#include <Windows.h>

#define ASSERT(x) if (x) { } else { DebugBreak(); }

#elif AIR_PLATFORM_LINUX
#include <signal.h>
#define ASSERT(x) if (x) { } else { raise(SIGTRAP); }
#else
#define ASSERT(x) x
#endif