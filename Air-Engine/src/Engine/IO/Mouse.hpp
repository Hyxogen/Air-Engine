#pragma once

#include "MouseCodes.hpp"

namespace engine {
	namespace io {

		class Window;

		class Mouse {
		protected:
			Window* m_Window;
		public:
			Mouse(Window* window);

			virtual bool HasScrollWheel() const = 0;

			virtual unsigned int GetScrollDelta() const = 0;

			virtual int GetXCoord() const = 0;

			virtual int GetYCoord() const = 0;

			virtual bool GetButtonDown(MouseCode mouseCode) const = 0;

			inline Window* GetWindow() const { return m_Window; }

			static Mouse* Create(Window* window);
		};

	}
}