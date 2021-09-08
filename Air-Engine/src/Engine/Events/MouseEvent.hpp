#include "airpch.h"
#pragma once

#include "Event.hpp"
#include "../IO/MouseCodes.hpp"

namespace engine {

	namespace io {
		class Window;
	}

	namespace events {

		//TODO Remove protected constructors with no parameters
		//All mouse events should contain information about key and position
		class MouseEvent : public Event {
		protected:
			io::Window* m_Window;
			uint32 m_ButtonMask;
			uint32 m_X, m_Y;

		public:
			MouseEvent(io::Window* window, uint32 buttonMask, int32 x, int32 y) : m_Window(window), m_ButtonMask(buttonMask), m_X(x), m_Y(y) {}

			inline io::Window* GetWindow() const { return m_Window; }

			inline uint32 GetX() const { return m_X; }

			inline uint32 GetY() const { return m_Y; }

			inline uint32 GetButtonMask() const { return m_ButtonMask; }

			virtual uint32 GetID() const { return Hash("EVENT_MOUSE_GENERAL", 20); }
		};

		class MouseScrollEvent : public MouseEvent {
		protected:
			int32 m_ScrollDelta;
		public:
			MouseScrollEvent(io::Window* window, uint32 buttonMask, int32 x, int32 y, int32 scrollDelta) : MouseEvent(window, buttonMask, x, y), m_ScrollDelta(scrollDelta) {}

			inline int32 GetScrollDelta() const { return m_ScrollDelta; }

			virtual uint32 GetID() const { return Hash("EVENT_MOUSE_SCROLL", 19); }
		};
	}
}