#pragma once

#ifdef AIR_PLATFORM_WINDOWS
#ifdef ASSERTIONS_ENABLED
#define ASSERT(expr) \
	if (expr) {} \
	else {\
		DebugBreak();\
	}
#else
#define ASSERT(expr)
#endif
#endif