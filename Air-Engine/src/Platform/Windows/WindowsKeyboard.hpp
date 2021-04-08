#pragma once

//Ik ben benieuwd of het mij lukt om dit ook forward te declaren
#include "../../Engine/IO/Keyboard.hpp"

namespace engine {
	namespace events {
		class Event;
	}
}

namespace platform {
	namespace windows {

		class WindowsWindow;

		class WindowsKeyboard : public engine::io::Keyboard {

		public:
			WindowsKeyboard(WindowsWindow* window);

			virtual bool GetKeyDown(int keyCode) const;

			virtual bool GetKeyToggled(int keyCode) const;

		private:
			void OnKeyEvent(engine::events::Event* keyDownEvent);
		};

	}
}