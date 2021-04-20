#include "Keyboard.hpp"

#include "../Core/Application.hpp"
#include "../Events/KeyEvent.hpp"
#include "../Util/HashUtils.hpp"
#include "../Events/EventDispatcher.hpp"
#include "../IO/Window.hpp"
#include "../Core/Assert.hpp"

namespace engine {
	namespace io {

		Keyboard::Keyboard(Window* window) : m_Window(window) {
			m_Keys = new unsigned int[KeyCode::NONE];

			memset(m_Keys, 0, sizeof(unsigned int) * (unsigned int) KeyCode::NONE);
			
			core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_KEY_DOWN", 15), this);
			core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_KEY_RELEASE", 18), this);
		}

		Keyboard::~Keyboard() {
			delete m_Keys;
		}

		bool Keyboard::GetKeyDown(KeyCode keyCode) const {
			return m_Keys[(unsigned int) keyCode] >= 1;
		}

		bool Keyboard::GetKeyToggled(KeyCode keyCode) const {
			return false;
		}

		bool Keyboard::OnEvent(events::Event& event) {
			events::KeyEvent& keyEvent = (events::KeyEvent&)event;

			io::Window* wndPtr =  keyEvent.GetWindow();

			if (keyEvent.GetWindow() != m_Window) return false;

			unsigned int id = keyEvent.GetID();

			if (keyEvent.GetID() == Hash("EVENT_KEY_DOWN", 15)) {
				ASSERT(((unsigned int)keyEvent.GetKeyCode()) < (unsigned int) KeyCode::NONE);

				m_Keys[(unsigned int)keyEvent.GetKeyCode()] += 1;
				return false;
			}
			else if (keyEvent.GetID() == Hash("EVENT_KEY_RELEASE", 18)) {
				ASSERT(((unsigned int)keyEvent.GetKeyCode()) < (unsigned int)KeyCode::NONE);

				m_Keys[(unsigned int)keyEvent.GetKeyCode()] = 0;
				return false;
			}
			return false;
		}
	}
}