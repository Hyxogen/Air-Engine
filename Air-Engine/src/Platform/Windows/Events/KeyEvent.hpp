#pragma once

#include "../../../Engine/Events/KeyEvent.hpp"

namespace platform {
	namespace windows {

		//This is probably useless
		class WindowsKeyEvent : public engine::events::KeyEvent {
		protected:
			const unsigned int m_Event, m_WParam;
			const unsigned long m_LParam;

			//wParam could perhaps not work on 64bit platforms
			WindowsKeyEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam);
		public:
			inline unsigned int GetEvent() const { return m_Event; }

			inline unsigned int GetWParam() const { return m_WParam; }

			inline unsigned long GetLParam() const { return m_LParam; }

			virtual unsigned int GetID() const = 0;
		};

		class WindowsKeyDownEvent : public engine::events::KeyDownEvent {
		protected:
			const bool m_Repeat;
		public:
			WindowsKeyDownEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam, bool repeat = false);
		};
	}
}