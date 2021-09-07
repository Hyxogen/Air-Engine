#include "airpch.h"
#pragma once

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
			std::unordered_set<uint32> m_PressedKeys;
		public:
			WindowsKeyboard(engine::io::Window* window);

			virtual ~WindowsKeyboard();

			virtual bool GetKeyDown(uint32 keyCode) const;

			virtual bool GetKeyToggled(uint32 keyCode) const;

			virtual bool OnEvent(engine::events::Event* event);
		};

	}
}