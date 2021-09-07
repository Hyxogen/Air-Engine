#pragma once

#include "../../Engine/IO/Mouse.hpp"
#include "../../Engine/Events/EventListener.hpp"

namespace platform {
	namespace windows {

		//Have a separate class for handling mouse events? Like WindowsMouseEventHandler?
		class WindowsMouse : public engine::io::Mouse, public engine::events::EventListener {
		protected:
			uint32 m_ButtonsMask;
			int32 m_X, m_Y, m_ScrollDelta;
		public:
			WindowsMouse(engine::io::Window* window);

			~WindowsMouse();

			virtual bool HasScrollWheel() const;

			int32 GetScrollDelta() const { return m_ScrollDelta; }

			inline int32 GetXCoord() const { return m_X; }

			inline int32 GetYCoord() const { return m_Y; };

			virtual bool GetButtonDown(uint32 button) const;

			virtual bool OnEvent(engine::events::Event* event);
		};

	}
}