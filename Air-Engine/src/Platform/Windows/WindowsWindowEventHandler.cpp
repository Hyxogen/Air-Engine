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

			if (windowEvent.GetWindow() != m_Window) return false;

			if (windowEvent.GetEvent() == WM_KEYDOWN || windowEvent.GetEvent() == WM_KEYUP) {
				HandleKeyEvent(windowEvent);
				return true;
			}
			else if (windowEvent.GetEvent() == WM_LBUTTONDOWN || windowEvent.GetEvent() == WM_MBUTTONDOWN || windowEvent.GetEvent() == WM_RBUTTONDOWN || windowEvent.GetEvent() == WM_XBUTTONDOWN
				|| windowEvent.GetEvent() == WM_LBUTTONUP || windowEvent.GetEvent() == WM_MBUTTONUP || windowEvent.GetEvent() == WM_RBUTTONUP || windowEvent.GetEvent() == WM_XBUTTONUP) {
				HandleMouseEvent(windowEvent);
				return true;
			}
			else if (windowEvent.GetEvent() == WM_MOUSEMOVE) {
				HandleMouseEvent(windowEvent);
				return true;
			}
			else if (windowEvent.GetEvent() == WM_MOUSEWHEEL) {
				HandleMouseEvent(windowEvent);
				return true;
			}
			return false;
		}

		void WindowsWindowEventHandler::HandleKeyEvent(WindowsWindowEvent& event) {
			if (event.GetEvent() == WM_KEYDOWN) {
				WindowsKeyDownEvent keyEvent((engine::io::Window*)event.GetWindow(), event.GetEvent(), event.GetWParam(), event.GetLParam());
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(keyEvent);
				return;
			}
			else {
				WindowsKeyReleaseEvent keyEvent((engine::io::Window*)event.GetWindow(), event.GetEvent(), event.GetWParam(), event.GetLParam());
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(keyEvent);
				return;
			}
		}

		void WindowsWindowEventHandler::HandleMouseEvent(WindowsWindowEvent& event) {
			if (event.GetEvent() == WM_MOUSEWHEEL) {
				WindowsMouseScrollEvent mouseEvent((engine::io::Window*)event.GetWindow(), event.GetEvent(), event.GetWParam(), event.GetLParam());
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(mouseEvent);
			}
			else {
				WindowsMouseEvent mouseEvent((engine::io::Window*)event.GetWindow(), event.GetEvent(), event.GetWParam(), event.GetLParam());
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(mouseEvent);
			}
		}

		void WindowsWindowEventHandler::HandleOtherEvent(WindowsWindowEvent& event) {

		}
	}
}