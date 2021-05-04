#include "airpch.h"
#include "WindowsMouse.hpp"

#include "WindowsMouseMappings.hpp"

#include "Events/WindowsWindowEvent.hpp"

#include "../../Engine/Core/Application.hpp"
#include "../../Engine/Events/EventDispatcher.hpp"
#include "../../Engine/Events/MouseEvent.hpp"

namespace platform {
	namespace windows {

		WindowsMouse::WindowsMouse(engine::io::Window* window) : Mouse(window), m_X(0), m_Y(0), m_ButtonsMask(0), m_ScrollDelta(0) {
			engine::core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_MOUSE_GENERAL", 20), this);
			engine::core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_MOUSE_SCROLL", 19), this);
		}

		WindowsMouse::~WindowsMouse() {
		}

		bool WindowsMouse::HasScrollWheel() const {
			return GetSystemMetrics(SM_MOUSEWHEELPRESENT);
		}

		bool WindowsMouse::GetButtonDown(unsigned int button) const {
			return (m_ButtonsMask & WindowsButtonMap::GetButtonMask(button)) != 0;
		}

		bool WindowsMouse::OnEvent(engine::events::Event* event) {
			engine::events::MouseEvent* mouseEvent = (engine::events::MouseEvent*)event;

			if (mouseEvent->GetWindow() != m_Window) return false;

			m_ButtonsMask = mouseEvent->GetButtonMask();
			bool down = GetButtonDown(engine::io::BUTTON_RIGHT);
			m_X = mouseEvent->GetX();
			m_Y = mouseEvent->GetY();

			if (event->GetID() == Hash("EVENT_MOUSE_SCROLL", 19))
				m_ScrollDelta = ((engine::events::MouseScrollEvent&)mouseEvent).GetScrollDelta();
			return false;
		}
	}
}