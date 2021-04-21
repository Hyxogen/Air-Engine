#include "WindowsMouse.hpp"

#include "Events/WindowsMouseEvent.hpp"

#include "../../Engine/Core/Assert.hpp"
#include "../../Engine/Util/HashUtils.hpp"
#include "../../Engine/Core/Application.hpp"
#include "../../Engine/Events/EventDispatcher.hpp"

namespace platform {
	namespace windows {

		WindowsMouse::WindowsMouse(engine::io::Window* window) : Mouse(window) {
			engine::core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_MOUSE_BUTTON_DOWN", 24), this);
			engine::core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_MOUSE_BUTTON_RELEASE", 27), this);
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
			engine::events::MouseEvent& mouseEvent = (engine::events::MouseEvent&)event;

			if (mouseEvent.GetWindow() != m_Window) return false;

			if (mouseEvent.GetID() == Hash("EVENT_MOUSE_BUTTON_DOWN", 24)) {
				return false;
			}
			return false;
		}
	}
}