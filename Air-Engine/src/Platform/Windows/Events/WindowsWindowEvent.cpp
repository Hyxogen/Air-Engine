#include "WindowsWindowEvent.hpp"

#include "WindowsKeyEvent.hpp"
#include "WindowsMouseEvent.hpp"

#include "../../../Engine/Core/Application.hpp"
#include "../../../Engine/Events/EventDispatcher.hpp"
#include "../../../Engine/IO/Window.hpp"
#include "../../../Engine/Util/HashUtils.hpp"

#include <windows.h>

namespace platform {
	namespace windows {

		WindowsWindowEvent::WindowsWindowEvent(WindowsWindow* window, unsigned int event, unsigned int wParam, unsigned long lParam)
			: m_Window(window), m_Event(event), m_WParam(wParam), m_LParam(lParam) {

			if (event == WM_KEYDOWN) {
				WindowsKeyDownEvent keyEvent((engine::io::Window*)window, event, wParam, lParam);
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(keyEvent);
			}
			else if (event == WM_KEYUP) {
				WindowsKeyReleaseEvent keyEvent((engine::io::Window*)window, event, wParam, lParam);
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(keyEvent);
			}
			else if (event == WM_LBUTTONDOWN || event == WM_MBUTTONDOWN || event == WM_RBUTTONDOWN || event == WM_XBUTTONDOWN) {
				WindowsMouseButtonDownEvent mouseEvent((engine::io::Window*)window, event, wParam, lParam);
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(mouseEvent);
			}
			else if (event == WM_LBUTTONUP || event == WM_MBUTTONUP || event == WM_RBUTTONUP || event == WM_XBUTTONUP) {
				WindowsMouseButtonReleaseEvent mouseEvent((engine::io::Window*)window, event, wParam, lParam);
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(mouseEvent);
			}
		}

		unsigned int WindowsWindowEvent::GetID() const {
			return Hash("EVENT_WINDOWS_WINDOW", 21);
		}
	}
}