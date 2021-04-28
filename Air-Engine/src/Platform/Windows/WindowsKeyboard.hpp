#pragma once

#include <set>

//Ik ben benieuwd of het mij lukt om dit ook forward te declaren
#include "../../Engine/IO/Keyboard.hpp"
#include "../../Engine/Events/EventListener.hpp"

namespace engine {
	namespace events {
		class Event;
	}

	namespace io {
		class Window;
	}
}

namespace platform {

	namespace windows {

		class WindowsKeyboard : public engine::io::Keyboard, public engine::events::EventListener {
		protected:
			std::set<unsigned int> m_PressedKeys;
		public:
			WindowsKeyboard(engine::io::Window* window);

			virtual ~WindowsKeyboard();

			virtual bool GetKeyDown(unsigned int keyCode) const;

			virtual bool GetKeyToggled(unsigned int keyCode) const;

			virtual bool OnEvent(engine::events::Event* event);
		};

	}
}