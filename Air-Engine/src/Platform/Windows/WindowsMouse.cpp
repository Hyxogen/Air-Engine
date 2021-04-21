#include "WindowsMouse.hpp"

namespace platform {
	namespace windows {

		WindowsMouse::WindowsMouse(engine::io::Window* window) : Mouse(window) {
		}

		bool WindowsMouse::HasScrollWheel() const {
			return false;
		}

		unsigned int WindowsMouse::GetScrollDelta() const {
			return 0;
		}

		int WindowsMouse::GetXCoord() const {
			return 0;
		}

		int WindowsMouse::GetYCoord() const {
			return 0;
		}

		bool WindowsMouse::GetButtonDown(engine::io::MouseCode mouseCode) const {
			return false;
		}

		bool WindowsMouse::OnEvent(engine::events::Event& event) {
			return false;
		}
	}
}