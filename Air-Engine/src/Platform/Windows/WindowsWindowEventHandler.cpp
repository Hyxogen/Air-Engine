#include "airpch.h"
#include "WindowsWindowEventHandler.hpp"

#include "Events/WindowsWindowEvent.hpp"

#include "../../Engine/Core/Application.hpp"

#include "../../Engine/Events/Event.hpp"
#include "../../Engine/Events/KeyEvent.hpp"
#include "../../Engine/Events/MouseEvent.hpp"
#include "../../Engine/Events/EventDispatcher.hpp"

#include "WindowsKeyMappings.hpp"
#include "WindowsMouseMappings.hpp"

namespace platform {
	namespace windows {

		WindowsWindowEventHandler::WindowsWindowEventHandler(WindowsWindow* window) : m_Window(window) {
			engine::core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_WINDOWS_WINDOW", 21), this);
		}

		bool WindowsWindowEventHandler::OnEvent(engine::events::Event* event) {
			WindowsWindowEvent* windowEvent = (WindowsWindowEvent*)event;

			if (windowEvent->GetWindow() != m_Window) return false;

			return HandleEvent(windowEvent);
		}

		bool WindowsWindowEventHandler::HandleEvent(WindowsWindowEvent* event) {
			uint32 message = event->GetEvent();
			if (message == WM_KEYDOWN || message == WM_KEYUP) {
				return HandleKeyEvent(event);
			}
			else if (message == WM_LBUTTONDOWN || message == WM_MBUTTONDOWN || message == WM_RBUTTONDOWN || message == WM_XBUTTONDOWN
				|| message == WM_LBUTTONUP || message == WM_MBUTTONUP || message == WM_RBUTTONUP || message == WM_XBUTTONUP) {
				return HandleMouseEvent(event);
			}
			else if (message == WM_MOUSEMOVE || message == WM_MOUSEWHEEL) {
				return HandleMouseEvent(event);
			}
			return false;
		}

		bool WindowsWindowEventHandler::HandleKeyEvent(WindowsWindowEvent* event) {
			if (event->GetEvent() == WM_KEYDOWN) {
				engine::events::KeyDownEvent keyEvent((engine::io::Window*)event->GetWindow(), GetKeyCode(event->GetWParam()), IsRepeat(event->GetLParam()));
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(&keyEvent);
				return true;
			}
			else {
				engine::events::KeyReleaseEvent keyEvent((engine::io::Window*)event->GetWindow(), GetKeyCode(event->GetWParam()));
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(&keyEvent);
				return true;
			}
		}

		bool WindowsWindowEventHandler::HandleMouseEvent(WindowsWindowEvent* event) {
			if (event->GetEvent() == WM_MOUSEWHEEL) {
				engine::events::MouseScrollEvent mouseEvent(
					(engine::io::Window*)event->GetWindow(), GetButtonMask(event->GetWParam()), GetXCoord(event->GetLParam()), GetYCoord(event->GetLParam()), GetScrollDelta(event->GetWParam()));
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(&mouseEvent);
				return true;
			}
			else {
				engine::events::MouseEvent mouseEvent((engine::io::Window*)event->GetWindow(), GetButtonMask(event->GetWParam()), GetXCoord(event->GetLParam()), GetYCoord(event->GetLParam()));
				engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(&mouseEvent);
				return true;
			}
		}

		bool WindowsWindowEventHandler::HandleOtherEvent(WindowsWindowEvent* event) {
			return false;
		}

		int32 WindowsWindowEventHandler::GetXCoord(LPARAM lParam) {
			return LOWORD(lParam);
		}

		int32 WindowsWindowEventHandler::GetYCoord(LPARAM lParam) {
			return HIWORD(lParam);
		}

		bool WindowsWindowEventHandler::IsRepeat(LPARAM lParam) {
			return (lParam & (1 << 30)) == 1;
		}

		int32 WindowsWindowEventHandler::GetScrollDelta(WPARAM wParam) {
			return GET_WHEEL_DELTA_WPARAM(wParam);
		}

		uint32 WindowsWindowEventHandler::GetButtonMask(WPARAM wParam) {
			uint32 ret = 0;

			if (wParam & MK_LBUTTON)
				ret = ret | WindowsButtonMap::GetButtonMask(WindowsButtonMap::GetSysCode(MK_LBUTTON));
			if (wParam & MK_MBUTTON)
				ret = ret | WindowsButtonMap::GetButtonMask(WindowsButtonMap::GetSysCode(MK_MBUTTON));
			if (wParam & MK_RBUTTON)
				ret = ret | WindowsButtonMap::GetButtonMask(WindowsButtonMap::GetSysCode(MK_RBUTTON));
			if (wParam & MK_XBUTTON1)
				ret = ret | WindowsButtonMap::GetButtonMask(WindowsButtonMap::GetSysCode(MK_XBUTTON1));
			if (wParam & MK_XBUTTON2)
				ret = ret | WindowsButtonMap::GetButtonMask(WindowsButtonMap::GetSysCode(MK_XBUTTON2));

			return ret;
		}

		uint32 WindowsWindowEventHandler::GetKeyCode(WPARAM wParam) {
			return WindowsKeyMap::GetSysCode(wParam);
		}
	}
}