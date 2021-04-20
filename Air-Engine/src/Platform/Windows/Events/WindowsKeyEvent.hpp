#pragma once

#include "../../../Engine/Events/KeyEvent.hpp"

namespace platform {
	namespace windows {

		class WindowsKeyDownEvent : public engine::events::KeyDownEvent {
		protected:
			const bool m_Repeat;
		public:
			WindowsKeyDownEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam, bool repeat = false);
		};

		class WindowsKeyReleaseEvent : public engine::events::KeyReleaseEvent {
		public:
			WindowsKeyReleaseEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam);
		};
	}
}