#pragma once

#include "../../../Engine/Events/MouseEvent.hpp"

namespace platform {
	namespace windows {

		class WindowsMouseButtonDownEvent : public engine::events::MouseButtonDownEvent {
		protected:
			unsigned int m_Event, m_WParam;
			unsigned long m_LParam;
		public:
			WindowsMouseButtonDownEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam);

			inline unsigned int GetEvent() const { return m_Event; }

			inline unsigned int GetWParam() const { return m_WParam; }

			inline unsigned long GetLParam() const { return m_LParam; }

		protected:
			engine::io::MouseCode GetMouseCode(unsigned int event) const;
		};

	}
}