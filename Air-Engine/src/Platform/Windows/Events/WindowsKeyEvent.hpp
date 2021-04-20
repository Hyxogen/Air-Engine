#pragma once

#include "../../../Engine/Events/KeyEvent.hpp"

namespace platform {
	namespace windows {

		class WindowsKeyDownEvent : public engine::events::KeyDownEvent {
		protected:
			unsigned int m_Event, m_WParam;
			unsigned long m_LParam;
			const bool m_Repeat;

		public:
			WindowsKeyDownEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam, bool repeat = false);

			inline unsigned int GetEvent() const { return m_Event; }

			inline unsigned int GetWParam() const { return m_WParam; }

			inline unsigned long GetLParam() const { return m_LParam; }
		};

		class WindowsKeyReleaseEvent : public engine::events::KeyReleaseEvent {
		protected:
			unsigned int m_Event, m_WParam;
			unsigned long m_LParam;

		public:
			WindowsKeyReleaseEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam);

			inline unsigned int GetEvent() const { return m_Event; }

			inline unsigned int GetWParam() const { return m_WParam; }

			inline unsigned long GetLParam() const { return m_LParam; }
		};
	}
}