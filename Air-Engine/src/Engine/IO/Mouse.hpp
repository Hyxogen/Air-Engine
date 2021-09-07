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

			virtual int32 GetScrollDelta() const = 0;

			virtual int32 GetXCoord() const = 0;

			virtual int32 GetYCoord() const = 0;

			virtual bool GetButtonDown(uint32 button) const = 0;

			inline Window* GetWindow() const { return m_Window; }

			static Mouse* Create(Window* window);
		};

	}
}