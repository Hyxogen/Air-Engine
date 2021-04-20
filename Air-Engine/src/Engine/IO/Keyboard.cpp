#include "Keyboard.hpp"

#include "../Core/Application.hpp"
#include "../Events/KeyEvent.hpp"
#include "../Util/HashUtils.hpp"
#include "../Events/EventDispatcher.hpp"

namespace engine {
	namespace io {

		Keyboard::Keyboard(Window* window) : m_Window(window) {
			core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_KEY_DOWN", 15), this);
			core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_KEY_RELEASE", 18), this);

		}

		bool Keyboard::OnEvent(events::Event& event) {
			events::KeyEvent& keyEvent = (events::KeyEvent&)event;

			if (keyEvent.GetWindow() != m_Window) return false;

			if (keyEvent.GetID() == Hash("EVENT_KEY_DOWN", 15)) {
				
			}
			else if (keyEvent.GetID() == Hash("EVENT_KEY_RELEASE", 18)) {

			}
			return false;
		}
	}
}