#pragma once

#include "../../../Engine/Events/MouseEvent.hpp"

namespace platform {
	namespace windows {

		class WindowsMouseMoveEvent : public engine::events::MouseMoveEvent {
		protected:
			unsigned int m_Event, m_WParam;
			unsigned long m_LParam;
		public:
			WindowsMouseMoveEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam);

			int GetX(unsigned long lParam) const;
			
			int GetY(unsigned long lParam) const;
		};

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

		class WindowsMouseButtonReleaseEvent : public engine::events::MouseButtonReleaseEvent {
		protected:
			unsigned int m_Event, m_WParam;
			unsigned long m_LParam;
		public:
			WindowsMouseButtonReleaseEvent(engine::io::Window* window, unsigned int event, unsigned int wParam, unsigned long lParam);

			inline unsigned int GetEvent() const { return m_Event; }

			inline unsigned int GetWParam() const { return m_WParam; }

			inline unsigned long GetLParam() const { return m_LParam; }

		protected:
			engine::io::MouseCode GetMouseCode(unsigned int event) const;
		};
	}
}