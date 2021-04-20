#include "WindowsKeyboard.hpp"

#include "../../Engine/Core/Application.hpp"
#include "../../Engine/Events/EventDispatcher.hpp"

namespace platform {
	namespace windows {

		WindowsKeyboard::WindowsKeyboard(WindowsWindow* window) : engine::io::Keyboard(nullptr) {
			
		}

		bool WindowsKeyboard::GetKeyDown(int keyCode) const {
			return false;
		}

		bool WindowsKeyboard::GetKeyToggled(int keyCode) const {
			return false;
		}

		void WindowsKeyboard::OnKeyEvent(engine::events::Event* keyDownEvent) {

		}
	}
}