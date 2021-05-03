#include "airpch.h"
#include "Keyboard.hpp"

#ifdef AIR_PLATFORM_WINDOWS
#include "../../Platform/Windows/WindowsKeyboard.hpp"
#else
#error Air Engine only supports windows at the moment
#endif

namespace engine {
	namespace io {

		Keyboard::Keyboard(Window* window) : m_Window(window) {}

		Keyboard* Keyboard::Create(Window* window) {
			#ifdef AIR_PLATFORM_WINDOWS
			return new platform::windows::WindowsKeyboard(window);
			#endif
		}
	}
}