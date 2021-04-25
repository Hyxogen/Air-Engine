#include "WindowsKeyEvent.hpp"

#include "../WindowsWindow.hpp"
#include "../../../Engine/IO/KeyCodes.hpp"
#include "WindowsKeyEvent.hpp"
#include "../WindowsKeyMappings.hpp"

namespace platform {
	namespace windows {

		WindowsKeyDownEvent::WindowsKeyDownEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam, bool repeat) {
			m_Window = window;

			m_KeyCode = WindowsKeyMap::GetKeyCode(wParam);

			m_Event = event;
			m_WParam = wParam;
			m_LParam = lParam;

			m_Repeat = (lParam & (1 << 30)) == 1;
		}

		WindowsKeyReleaseEvent::WindowsKeyReleaseEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam) {
			m_Window = window;
			m_KeyCode = static_cast<engine::io::KeyCode>(wParam);

			m_Event = event;
			m_WParam = wParam;
			m_LParam = lParam;
		}
	}
}