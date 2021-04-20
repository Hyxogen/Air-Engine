#pragma once

#ifdef AIR_ASSERTIONS_ENABLED
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
	//If an error during compilation triggers here, it means that you've supplied a type somewhere that is not supported
	static void Constraints(T1 a, T2 b) {
		T2 c = a;
		b = a;
	}

	Can_copy() {
		void(*p)(T1, T2) = Constraints;
	}
};
#else
#define ASSERT(expr) expr
#endif