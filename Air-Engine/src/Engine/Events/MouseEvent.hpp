#pragma once

#include "Event.hpp"
#include "../IO/MouseCodes.hpp"
#include "../Util/HashUtils.hpp"

namespace engine {

	namespace io {
		class Window;
	}

	namespace events {

		class MouseEvent : public Event {
		protected:
			io::Window m_Window* = nullptr;
			io::MouseCode m_MouseCode = io::MouseCode::NONE;

			MouseEvent() {}

			MouseEvent(io::Window* window, io::MouseCode mouseCode) : m_Window(window), m_MouseCode(mouseCode) {}

		public:
			inline io::MouseCode GetMouseCode() const { return m_MouseCode; }
		};

		class MouseButtonDownEvent : public MouseEvent {
		protected:

			MouseButtonDownEvent() {}
		public:
			MouseButtonDownEvent(io::Window* window, io::MouseCode mouseCode) : MouseEvent(window, mouseCode) { }

			unsigned int GetID() const { return Hash("EVENT_MOUSE_BUTTON_DOWN", 24); }
		};

		class MouseButtonReleaseEvent : public MouseEvent {
		protected:

			MouseButtonReleaseEvent() {}
		public:
			MouseButtonReleaseEvent(io::Window* window, io::MouseCode mouseCode) : MouseEvent(window, mouseCode) {}

			unsigned int GetID() const { return Hash("EVENT_MOUSE_BUTTON_RELEASE", 27); }
		};
	}
}