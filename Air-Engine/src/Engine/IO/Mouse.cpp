#include "Mouse.hpp"

#ifdef AIR_PLATFORM_WINDOWS
#include "../../Platform/Windows/WindowsWindow.hpp"
#include "../../Platform/Windows/WindowsKeyboard.hpp"
#else
#error Air Engine only supports windows at the moment
#endif

namespace engine {
	namespace io {

		Mouse::Mouse(Window* window) : m_Window(window) {}

		Mouse* Mouse::Create(Window* window) {
			#ifdef AIR_PLATFORM_WINDOWS
			return nullptr;
			#endif
		}
	}
}