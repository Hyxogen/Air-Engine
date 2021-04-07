#pragma once

#ifdef ASSERTIONS_ENABLED
#ifdef AIR_PLATFORM_WINDOWS
#define ASSERT(expr) \
	if (expr) {} \
	else {\
		DebugBreak();\
	}
#else
#define ASSERT(expr)
#endif
template<class T1, class T2> struct Can_copy {
	static void Constraints(T1 a, T2 b) {
		b = a;
	}

	Can_copy() {
		void(*p)(T1, T2) = Constraints;
	}
};
#endif