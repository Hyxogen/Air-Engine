#pragma once

#include "../../Engine/IO/Mouse.hpp"
#include "../../Engine/Events/EventListener.hpp"

namespace platform {
	namespace windows {

		//Have a separate class for handling mouse events? Like WindowsMouseEventHandler?
		class WindowsMouse : public engine::io::Mouse, public engine::events::EventListener {
		protected:
			bool* m_Buttons;
			int m_X, m_Y;
		public:
			WindowsMouse(engine::io::Window* window);

			~WindowsMouse();

			virtual bool HasScrollWheel() const;

			virtual unsigned int GetScrollDelta() const;

			virtual int GetXCoord() const;

			virtual int GetYCoord() const;

			virtual bool GetButtonDown(engine::io::MouseCode mouseCode) const;

			virtual bool OnEvent(engine::events::Event& event);
		};

	}
}