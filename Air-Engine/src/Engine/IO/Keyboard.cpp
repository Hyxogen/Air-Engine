#include "Keyboard.hpp"

#include "../Core/Application.hpp"
#include "../Events/KeyEvent.hpp"
#include "../Util/HashUtils.hpp"
#include "../Events/EventDispatcher.hpp"
#include "../IO/Window.hpp"

namespace engine {
	namespace io {

		Keyboard::Keyboard(Window* window) : m_Window(window) {
			core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_KEY_DOWN", 15), this);
			core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_KEY_RELEASE", 18), this);

		}

		bool Keyboard::GetKeyDown(int keyCode) const {
			return false;
		}

		bool Keyboard::GetKeyToggled(int keyCode) const {
			return false;
		}

		bool Keyboard::OnEvent(events::Event& event) {
			events::KeyEvent& keyEvent = (events::KeyEvent&)event;

			io::Window* wndPtr =  keyEvent.GetWindow();

			if (keyEvent.GetWindow() != m_Window) return false;

			unsigned int id = keyEvent.GetID();

			if (keyEvent.GetID() == Hash("EVENT_KEY_DOWN", 15)) {
				return false;
			}
			else if (keyEvent.GetID() == Hash("EVENT_KEY_RELEASE", 18)) {
				return false;
			}
			return false;
		}
	}
}