#include "WindowsWindowEventHandler.hpp"

#include "Events/WindowsWindowEvent.hpp"
#include "Events/WindowsKeyEvent.hpp"
#include "Events/WindowsMouseEvent.hpp"

#include "../../Engine/Core/Application.hpp"
#include "../../Engine/Util/HashUtils.hpp"

#include "../../Engine/Events/Event.hpp"
#include "../../Engine/Events/EventDispatcher.hpp"

#include <windows.h>

namespace platform {
	namespace windows {

		WindowsWindowEventHandler::WindowsWindowEventHandler(WindowsWindow* window) : m_Window(window) {
			engine::core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_WINDOWS_WINDOW", 21), this);
		}

		bool WindowsWindowEventHandler::OnEvent(engine::events::Event& event) {
			WindowsWindowEvent& windowEvent = (WindowsWindowEvent&)event;

			if (windowEvent.GetEvent() == WM_KEYDOWN) {
				WindowsKeyDownEvent keyEvent((engine::io::Window*)windowEvent.GetWindow(), windowEvent.GetEvent(), windowEvent.GetWParam(), windowEvent.GetLParam());
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(keyEvent);
				true;
			}
			else if (windowEvent.GetEvent() == WM_KEYUP) {
				WindowsKeyReleaseEvent keyEvent((engine::io::Window*)windowEvent.GetWindow(), windowEvent.GetEvent(), windowEvent.GetWParam(), windowEvent.GetLParam());
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(keyEvent);
				return true;
			}
			else if (windowEvent.GetEvent() == WM_LBUTTONDOWN || windowEvent.GetEvent() == WM_MBUTTONDOWN || windowEvent.GetEvent() == WM_RBUTTONDOWN || windowEvent.GetEvent() == WM_XBUTTONDOWN) {
				WindowsMouseButtonDownEvent mouseEvent((engine::io::Window*)windowEvent.GetWindow(), windowEvent.GetEvent(), windowEvent.GetWParam(), windowEvent.GetLParam());
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(mouseEvent);
				return true;
			}
			else if (windowEvent.GetEvent() == WM_LBUTTONUP || windowEvent.GetEvent() == WM_MBUTTONUP || windowEvent.GetEvent() == WM_RBUTTONUP || windowEvent.GetEvent() == WM_XBUTTONUP) {
				WindowsMouseButtonReleaseEvent mouseEvent((engine::io::Window*)windowEvent.GetWindow(), windowEvent.GetEvent(), windowEvent.GetWParam(), windowEvent.GetLParam());
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(mouseEvent);
				return true;
			}
			else if (windowEvent.GetEvent() == WM_MOUSEMOVE) {
				WindowsMouseMoveEvent mouseEvent((engine::io::Window*)windowEvent.GetWindow(), windowEvent.GetEvent(), windowEvent.GetWParam(), windowEvent.GetLParam());
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(mouseEvent);
				return true;
			}
			return false;
		}
	}
}