#pragma once

#include "../../Engine/IO/Mouse.hpp"
#include "../../Engine/Events/EventListener.hpp"

namespace platform {
	namespace windows {

		//Have a separate class for handling mouse events? Like WindowsMouseEventHandler?
		class WindowsMouse : public engine::io::Mouse, public engine::events::EventListener {
		protected:
			unsigned int m_ButtonsMask;
			int m_X, m_Y, m_ScrollDelta;
		public:
			WindowsMouse(engine::io::Window* window);

			~WindowsMouse();

			virtual bool HasScrollWheel() const;

			int GetScrollDelta() const { return m_ScrollDelta; }

			inline int GetXCoord() const { return m_X; }

			inline int GetYCoord() const { return m_Y; };

			virtual bool GetButtonDown(unsigned int button) const;

			virtual bool OnEvent(engine::events::Event& event);
		};

	}
}