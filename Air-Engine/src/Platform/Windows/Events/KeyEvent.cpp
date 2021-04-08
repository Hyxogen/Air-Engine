#include "KeyEvent.h"

#include "../WindowsWindow.hpp"

namespace platform {
	namespace windows {

		KeyEvent::KeyEvent(WindowsWindow* window, unsigned int event, unsigned int wParam) : mWindow(window), mEvent(event), mParam(wParam) {
			
		}

		unsigned int KeyEvent::GetID() const {
			return 1;
		}

	}
}