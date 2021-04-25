#pragma once

#include "../../../Engine/Events/MouseEvent.hpp"

namespace platform {
	namespace windows {

		class WindowsMouseEvent : public engine::events::MouseEvent {
			unsigned int m_Event, m_WParam;
			unsigned long m_LParam;
		public:
			WindowsMouseEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam);
		
			inline unsigned int GetEvent() const { return m_Event; }

			inline unsigned int GetWParam() const { return m_WParam; }

			inline unsigned long GetLParam() const { return m_LParam; }

			static int GetXCoord(unsigned long lParam);

			static int GetYCoord(unsigned long lParam);

			static unsigned int GetButtonMask(unsigned int wParam);
		};
	}
}