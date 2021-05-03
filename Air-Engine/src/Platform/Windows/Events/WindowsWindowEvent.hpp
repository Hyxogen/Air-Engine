#include "airpch.h"
#pragma once

#include "../../../Engine/Events/Event.hpp"

namespace platform {
	namespace windows {

		class WindowsWindow;

		class WindowsWindowEvent : public engine::events::Event {
		protected:
			WindowsWindow* m_Window;
			unsigned int m_Event;
			WPARAM m_WParam;
			LPARAM m_LParam;

		public:
			WindowsWindowEvent(WindowsWindow* window, unsigned int event, WPARAM wParam, LPARAM lParam);

			inline unsigned int GetEvent() const { return m_Event; }
			inline WPARAM GetWParam() const { return m_WParam; }
			inline LPARAM GetLParam() const { return m_LParam; }
			inline WindowsWindow* GetWindow() const { return m_Window; }

			virtual unsigned int GetID() const;
		};
	}
}