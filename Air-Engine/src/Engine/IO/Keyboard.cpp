#include "Keyboard.hpp"

#include "../Events/KeyEvent.hpp"
#include "../Util/HashUtils.hpp"

namespace engine {
	namespace io {

		Keyboard::Keyboard(Window* window) : m_Window(window) {

		}

		bool Keyboard::OnEvent(events::Event& event) {
			events::KeyEvent& keyEvent = (KeyEvent&)event;

			if (keyEvent.GetWindow() != m_Window) return false;

			if (keyEvent.GetID() == Hash("EVENT_KEY_DOWN", 15)) {
				
			}
			return false;
		}
	}
}