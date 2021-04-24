#include "WindowsKeyboard.hpp"

#include "../../Engine/Core/Assert.hpp"
#include "../../Engine/Util/HashUtils.hpp"
#include "../../Engine/Core/Application.hpp"
#include "../../Engine/Events/EventDispatcher.hpp"
#include "../../Engine/Events/KeyEvent.hpp"

#include "../../Engine/Util/Logger/Logger.hpp"


#include <windows.h>

namespace platform {
	namespace windows {

		WindowsKeyboard::WindowsKeyboard(engine::io::Window* window) : engine::io::Keyboard(window) {
			m_Keys = new unsigned int[platform::windows::KeyCode::NONE];

			memset(m_Keys, 0, sizeof(unsigned int) * (unsigned int)KeyCode::NONE);

			engine::core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_KEY_DOWN", 15), this);
			engine::core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_KEY_RELEASE", 18), this);
		}

		WindowsKeyboard::~WindowsKeyboard() {
			delete m_Keys;
		}

		bool WindowsKeyboard::GetKeyDown(engine::io::KeyCode keyCode) const {
			return m_Keys[(unsigned int) keyCode];
		}

		bool WindowsKeyboard::GetKeyToggled(engine::io::KeyCode keyCode) const {
			return (GetKeyState((int) keyCode) & (short) 0b1) == (short) 1;
		}

		bool WindowsKeyboard::OnEvent(engine::events::Event& event) {
			engine::events::KeyEvent& keyEvent = (engine::events::KeyEvent&)event;

			engine::io::Window* wndPtr = keyEvent.GetWindow();

			if (keyEvent.GetWindow() != m_Window) return false;

			unsigned int id = keyEvent.GetID();

			if (keyEvent.GetID() == Hash("EVENT_KEY_DOWN", 15)) {
				ASSERT(((unsigned int)keyEvent.GetKeyCode()) <= (unsigned int)KeyCode::NONE);

				m_Keys[(unsigned int)keyEvent.GetKeyCode()] += 1;
				return false;
			}
			else if (keyEvent.GetID() == Hash("EVENT_KEY_RELEASE", 18)) {
				ASSERT(((unsigned int)keyEvent.GetKeyCode()) <= (unsigned int)KeyCode::NONE);

				m_Keys[(unsigned int)keyEvent.GetKeyCode()] = 0;
				return false;
			}
			return false;

		}
	}
}