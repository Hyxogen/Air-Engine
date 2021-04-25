#include "WindowsMouseEvent.hpp"

#include "../WindowsMouseMappings.hpp"

#include <Windows.h>

namespace platform {
	namespace windows {
		WindowsMouseEvent::WindowsMouseEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam)
			: engine::events::MouseEvent(window, GetButtonMask(wParam), GetXCoord(lParam), GetYCoord(lParam)) {

		}

		int WindowsMouseEvent::GetXCoord(unsigned long lParam) {
			return LOWORD(lParam);
		}

		int WindowsMouseEvent::GetYCoord(unsigned long lParam) {
			return HIWORD(lParam);
		}

		int WindowsMouseEvent::GetScrollDelta(unsigned int wParam) {
			return GET_WHEEL_DELTA_WPARAM(wParam);
		}

		unsigned int WindowsMouseEvent::GetButtonMask(unsigned int wParam) {
			unsigned int ret = 0;

			if (wParam & MK_LBUTTON)
				ret = ret | WindowsButtonMap::GetButtonMask(WindowsButtonMap::GetButtonCode(MK_LBUTTON));
			if (wParam & MK_MBUTTON)
				ret = ret | WindowsButtonMap::GetButtonMask(WindowsButtonMap::GetButtonCode(MK_MBUTTON));
			if (wParam & MK_RBUTTON)
				ret = ret | WindowsButtonMap::GetButtonMask(WindowsButtonMap::GetButtonCode(MK_RBUTTON));
			if (wParam & MK_XBUTTON1)
				ret = ret | WindowsButtonMap::GetButtonMask(WindowsButtonMap::GetButtonCode(MK_XBUTTON1));
			if (wParam & MK_XBUTTON2)
				ret = ret | WindowsButtonMap::GetButtonMask(WindowsButtonMap::GetButtonCode(MK_XBUTTON2));

			return ret;
		}

		WindowsMouseScrollEvent::WindowsMouseScrollEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam) 
		: engine::events::MouseScrollEvent(window, GetButtonMask(wParam), GetXCoord(lParam), GetYCoord(lParam), GetScrollDelta(wParam)) {
			
		}


		int WindowsMouseScrollEvent::GetXCoord(unsigned long lParam) {
			return LOWORD(lParam);
		}

		int WindowsMouseScrollEvent::GetYCoord(unsigned long lParam) {
			return HIWORD(lParam);
		}

		int WindowsMouseScrollEvent::GetScrollDelta(unsigned int wParam) {
			return GET_WHEEL_DELTA_WPARAM(wParam);
		}

		unsigned int WindowsMouseScrollEvent::GetButtonMask(unsigned int wParam) {
			unsigned int ret = 0;

			if (wParam & MK_LBUTTON)
				ret = ret | WindowsButtonMap::GetButtonMask(WindowsButtonMap::GetButtonCode(MK_LBUTTON));
			if (wParam & MK_MBUTTON)
				ret = ret | WindowsButtonMap::GetButtonMask(WindowsButtonMap::GetButtonCode(MK_MBUTTON));
			if (wParam & MK_RBUTTON)
				ret = ret | WindowsButtonMap::GetButtonMask(WindowsButtonMap::GetButtonCode(MK_RBUTTON));
			if (wParam & MK_XBUTTON1)
				ret = ret | WindowsButtonMap::GetButtonMask(WindowsButtonMap::GetButtonCode(MK_XBUTTON1));
			if (wParam & MK_XBUTTON2)
				ret = ret | WindowsButtonMap::GetButtonMask(WindowsButtonMap::GetButtonCode(MK_XBUTTON2));

			return ret;
		}

	}
}