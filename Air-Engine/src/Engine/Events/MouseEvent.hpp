#pragma once

#include "Event.hpp"
#include "../IO/MouseCodes.hpp"
#include "../Util/HashUtils.hpp"

namespace engine {

	namespace io {
		class Window;
	}

	namespace events {

		//TODO Remove protected constructors with no parameters
		class MouseEvent : public Event {
		protected:
			io::Window* m_Window = nullptr;
			
			MouseEvent() {}

			MouseEvent(io::Window* window) : m_Window(window) {}

		public:
			inline io::Window* GetWindow() const { return m_Window; }
		};

		class MouseButtonEvent : public MouseEvent {
		protected:
			io::MouseCode m_MouseCode = io::MouseCode::NONE;

			MouseButtonEvent() {}

			MouseButtonEvent(io::Window* window, io::MouseCode mouseCode) : MouseEvent(window) { }

		public:
			inline io::MouseCode GetMouseCode() const { return m_MouseCode; }
		};

		class MouseMoveEvent : public MouseEvent {
		protected:
			int m_X = 0;
			int m_Y = 0;
			MouseMoveEvent() {} 
		
		public:
			MouseMoveEvent(io::Window* window, int x, int y) : MouseEvent(window), m_X(x), m_Y(y) {}

			inline int GetX() const { return m_X; }

			inline int GetY() const { return m_Y; }

			unsigned int GetID() const { return Hash("EVENT_MOUSE_MOVE", 17); }
		};

		class MouseButtonDownEvent : public MouseButtonEvent {
		protected:

			MouseButtonDownEvent() {}
		public:
			MouseButtonDownEvent(io::Window* window, io::MouseCode mouseCode) : MouseButtonEvent(window, mouseCode) { }

			unsigned int GetID() const { return Hash("EVENT_MOUSE_BUTTON_DOWN", 24); }
		};

		class MouseButtonReleaseEvent : public MouseButtonEvent {
		protected:

			MouseButtonReleaseEvent() {}
		public:
			MouseButtonReleaseEvent(io::Window* window, io::MouseCode mouseCode) : MouseButtonEvent(window, mouseCode) {}

			unsigned int GetID() const { return Hash("EVENT_MOUSE_BUTTON_RELEASE", 27); }
		};
	}
}