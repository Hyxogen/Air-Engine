#pragma once

#include "KeyCodes.hpp"

namespace engine {
	namespace io {

		class Window;

		class Keyboard {
		protected:
			Window* m_Window;
		public:
			Keyboard(Window* window) : m_Window(window) {}

			virtual bool GetKeyDown(KeyCode keyCode) const = 0;

			virtual bool GetKeyToggled(KeyCode keyCode) const = 0;

			inline Window* GetWindow() const { return m_Window; }
		};
	}
}