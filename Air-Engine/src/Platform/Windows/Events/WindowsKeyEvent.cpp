#include "WindowsKeyEvent.hpp"

#include "../WindowsWindow.hpp"
#include "../../../Engine/IO/KeyCodes.hpp"
#include "WindowsKeyEvent.hpp"
#include "../WindowsKeyMappings.hpp"

namespace platform {
	namespace windows {

		WindowsKeyDownEvent::WindowsKeyDownEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam, bool repeat)
		: engine::events::KeyDownEvent(window, WindowsKeyMap::GetKeyCode(wParam)), m_Event(event), m_WParam(wParam), m_LParam(lParam){
			m_Repeat = (lParam & (1 << 30)) == 1;
		}

		WindowsKeyReleaseEvent::WindowsKeyReleaseEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam)
		: engine::events::KeyReleaseEvent(window, WindowsKeyMap::GetKeyCode(wParam)), m_Event(event), m_WParam(wParam), m_LParam(lParam) {

		}
	}
}