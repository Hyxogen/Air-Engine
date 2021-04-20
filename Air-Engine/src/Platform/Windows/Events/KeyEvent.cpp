#include "KeyEvent.hpp"

#include "../WindowsWindow.hpp"
#include "../../../Engine/IO/KeyCodes.hpp"

namespace platform {
	namespace windows {

		WindowsKeyEvent::WindowsKeyEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam) {
			m_Window = window;
			m_KeyCode = static_cast<engine::io::KeyCode>(wParam);
			
			m_Event = event;
			m_WParam = wParam;
			m_LParam = lParam;
		}

		WindowsKeyDownEvent::WindowsKeyDownEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam, bool repeat) {
			m_Window = window;
			m_KeyCode = static_cast<engine::io::KeyCode>(wParam);

			m_Event = event;
			m_WParam = wParam;
			m_LParam = lParam;

			m_Repeat = (lParam & (1 << 30)) == true;
		}
	}
}