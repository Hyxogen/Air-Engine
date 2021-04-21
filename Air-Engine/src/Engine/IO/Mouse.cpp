#include "Mouse.hpp"

#ifdef AIR_PLATFORM_WINDOWS

#else
#error Air Engine only supports windows at the moment
#endif

namespace engine {
	namespace io {

		Mouse::Mouse(Window* window) : m_Window(window) {}

		Mouse::Create(Window* window) {
			#ifdef AIR_PLATFORM_WINDOWS

			#endif
		}
	}
}