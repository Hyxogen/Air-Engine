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

			return HandleEvent(windowEvent);
		}

		bool WindowsWindowEventHandler::HandleEvent(WindowsWindowEvent& event) {
			if (event.GetEvent() == WM_KEYDOWN || event.GetEvent() == WM_KEYUP) {
				HandleKeyEvent(event);
				return true;
			}
			else if (event.GetEvent() == WM_LBUTTONDOWN || event.GetEvent() == WM_MBUTTONDOWN || event.GetEvent() == WM_RBUTTONDOWN || event.GetEvent() == WM_XBUTTONDOWN
				|| event.GetEvent() == WM_LBUTTONUP || event.GetEvent() == WM_MBUTTONUP || event.GetEvent() == WM_RBUTTONUP || event.GetEvent() == WM_XBUTTONUP) {
				return HandleMouseEvent(event);
			}
			else if (event.GetEvent() == WM_MOUSEMOVE) {
				return HandleMouseEvent(event);
			}
			else if (event.GetEvent() == WM_MOUSEWHEEL) {
				return HandleMouseEvent(event);
			}
			return false;
		}

		bool WindowsWindowEventHandler::HandleKeyEvent(WindowsWindowEvent& event) {
			if (event.GetEvent() == WM_KEYDOWN) {
				WindowsKeyDownEvent keyEvent((engine::io::Window*)event.GetWindow(), event.GetEvent(), event.GetWParam(), event.GetLParam());
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(keyEvent);
				return true;
			}
			else {
				WindowsKeyReleaseEvent keyEvent((engine::io::Window*)event.GetWindow(), event.GetEvent(), event.GetWParam(), event.GetLParam());
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(keyEvent);
				return true;
			}
		}

		bool WindowsWindowEventHandler::HandleMouseEvent(WindowsWindowEvent& event) {
			if (event.GetEvent() == WM_MOUSEWHEEL) {
				WindowsMouseScrollEvent mouseEvent((engine::io::Window*)event.GetWindow(), event.GetEvent(), event.GetWParam(), event.GetLParam());
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(mouseEvent);
				return true;
			}
			else {
				WindowsMouseEvent mouseEvent((engine::io::Window*)event.GetWindow(), event.GetEvent(), event.GetWParam(), event.GetLParam());
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(mouseEvent);
				return true;
			}
		}

		bool WindowsWindowEventHandler::HandleOtherEvent(WindowsWindowEvent& event) {
			return false;
		}
	}
}