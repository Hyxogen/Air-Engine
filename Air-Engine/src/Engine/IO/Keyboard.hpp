#pragma once

#include "KeyCodes.hpp"

namespace engine {
	namespace io {

		class Window;

		class Keyboard {
		protected:
			Window* m_Window;
		public:
			Keyboard(Window* window);

			virtual bool GetKeyDown(uint32 keyCode) const = 0;

			virtual bool GetKeyToggled(uint32 keyCode) const = 0;

			inline Window* GetWindow() const { return m_Window; }

			static Keyboard* Create(Window* window);
		};
	}
}