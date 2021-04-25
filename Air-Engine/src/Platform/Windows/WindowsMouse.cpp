#include "WindowsMouse.hpp"

#include <windows.h>

#include "WindowsMouseMappings.hpp"

#include "Events/WindowsMouseEvent.hpp"

#include "../../Engine/Util/HashUtils.hpp"
#include "../../Engine/Core/Application.hpp"
#include "../../Engine/Events/EventDispatcher.hpp"


namespace platform {
	namespace windows {

		WindowsMouse::WindowsMouse(engine::io::Window* window) : Mouse(window), m_X(0), m_Y(0), m_ButtonsMask(0) {
			engine::core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_MOUSE_ANY", 16), this);
		}

		WindowsMouse::~WindowsMouse() {
		}

		bool WindowsMouse::HasScrollWheel() const {
			return GetSystemMetrics(SM_MOUSEWHEELPRESENT);
		}

		unsigned int WindowsMouse::GetScrollDelta() const {
			return 0;
		}

		bool WindowsMouse::GetButtonDown(unsigned int button) const {
			return (m_ButtonsMask & WindowsButtonMap::GetButtonMask(button)) != 0;
		}

		bool WindowsMouse::OnEvent(engine::events::Event& event) {
			engine::events::MouseEvent& mouseEvent = (engine::events::MouseEvent&)event;

			if (mouseEvent.GetWindow() != m_Window) return false;

			m_ButtonsMask = mouseEvent.GetButtonMask();
			bool down = GetButtonDown(engine::io::BUTTON_RIGHT);
			m_X = mouseEvent.GetX();
			m_Y = mouseEvent.GetY();
			return false;
		}
	}
}