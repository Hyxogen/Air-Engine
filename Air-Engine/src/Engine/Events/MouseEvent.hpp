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
		//All mouse events should contain information about key and position
		class MouseEvent : public Event {
		protected:
			io::Window* m_Window;
			unsigned int m_ButtonMask;
			unsigned int m_X, m_Y;

		public:
			MouseEvent(io::Window* window, unsigned int buttonMask, int x, int y) : m_Window(window), m_ButtonMask(buttonMask), m_X(x), m_Y(y) {}

			inline io::Window* GetWindow() const { return m_Window; }

			inline unsigned int GetX() const { return m_X; }

			inline unsigned int GetY() const { return m_Y; }

			inline unsigned int GetButtonMask() const { return m_ButtonMask; }

			virtual unsigned int GetID() const { return Hash("EVENT_MOUSE_ANY", 16); }
		};
	}
}