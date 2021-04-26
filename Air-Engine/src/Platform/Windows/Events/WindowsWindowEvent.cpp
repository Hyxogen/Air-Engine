#include "WindowsWindowEvent.hpp"

#include "../../../Engine/Core/Application.hpp"
#include "../../../Engine/Events/EventDispatcher.hpp"
#include "../../../Engine/IO/Window.hpp"
#include "../../../Engine/Util/HashUtils.hpp"

#include <windows.h>

namespace platform {
	namespace windows {

		WindowsWindowEvent::WindowsWindowEvent(WindowsWindow* window, unsigned int event, WPARAM wParam, LPARAM lParam)
			: m_Window(window), m_Event(event), m_WParam(wParam), m_LParam(lParam) {
		}

		unsigned int WindowsWindowEvent::GetID() const {
			return Hash("EVENT_WINDOWS_WINDOW", 21);
		}
	}
}