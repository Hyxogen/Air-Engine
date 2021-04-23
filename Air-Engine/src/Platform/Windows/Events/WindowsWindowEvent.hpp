#pragma once

#include "../../../Engine/Events/Event.hpp"

namespace platform {
	namespace windows {

		class WindowsWindow;

		class WindowsWindowEvent : public engine::events::Event {
		protected:
			WindowsWindow* m_Window;
			unsigned int m_Event, m_WParam;
			unsigned long m_LParam;

		public:
			WindowsWindowEvent(WindowsWindow* window, unsigned int event, unsigned int wParam, unsigned long lParam);

			inline unsigned int GetEvent() const { return m_Event; }

			inline unsigned int GetWParam() const { return m_WParam; }

			inline unsigned int GetLParam() const { return m_LParam; }

			inline WindowsWindow* GetWindow() const { return m_Window; }

			virtual unsigned int GetID() const;
		};

	}
}