#include "WindowsMouseEvent.hpp"

#include <Windows.h>

namespace platform {
	namespace windows {

		WindowsMouseButtonDownEvent::WindowsMouseButtonDownEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam) {
			m_Window = window;
			m_MouseCode = GetMouseCode(event);

			m_Event = event;
			m_WParam = wParam;
			m_LParam = lParam;
		}

		engine::io::MouseCode WindowsMouseButtonDownEvent::GetMouseCode(unsigned int event) const {
			switch (event) {
			case WM_LBUTTONDOWN:
				return engine::io::MouseCode::LEFT;
			default:
				return engine::io::MouseCode::NONE;
			}
		}

		WindowsMouseButtonReleaseEvent::WindowsMouseButtonReleaseEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam) {
			m_Window = window;
			m_MouseCode = GetMouseCode(event);

			m_Event = event;
			m_WParam = wParam;
			m_LParam = lParam;
		}

		engine::io::MouseCode WindowsMouseButtonReleaseEvent::GetMouseCode(unsigned int event) const {
			switch (event) {
			case WM_LBUTTONDOWN:
				return engine::io::MouseCode::LEFT;
			default:
				return engine::io::MouseCode::NONE;
			}
		}

		WindowsMouseMoveEvent::WindowsMouseMoveEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam) {
			m_Window = window;

			m_Event = event;
			m_WParam = wParam;
			m_LParam = lParam;

			m_X = GetX(lParam);
			m_Y = GetY(lParam);
		}

		int WindowsMouseMoveEvent::GetX(unsigned long lParam) const {
			return LOWORD(lParam);
		}

		int WindowsMouseMoveEvent::GetY(unsigned long lParam) const {
			return HIWORD(lParam);
		}
	}
}