#include "airpch.h"
#include "WindowsWindowEvent.hpp"

#include "../../../Engine/Core/Application.hpp"
#include "../../../Engine/Events/EventDispatcher.hpp"
#include "../../../Engine/IO/Window.hpp"

namespace platform {
	namespace windows {

		WindowsWindowEvent::WindowsWindowEvent(WindowsWindow* window, uint32 event, WPARAM wParam, LPARAM lParam)
			: m_Window(window), m_Event(event), m_WParam(wParam), m_LParam(lParam) {
		}

		uint32 WindowsWindowEvent::GetID() const {
			return Hash("EVENT_WINDOWS_WINDOW", 21);
		}
	}
}