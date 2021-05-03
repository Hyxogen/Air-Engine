#include "airpch.h"
#include "WindowsKeyboard.hpp"

#include "../../Engine/Util/HashUtils.hpp"
#include "../../Engine/Core/Application.hpp"
#include "../../Engine/Events/EventDispatcher.hpp"
#include "../../Engine/Events/KeyEvent.hpp"

#include "WindowsKeyMappings.hpp"

#include <windows.h>

namespace platform {
	namespace windows {

		WindowsKeyboard::WindowsKeyboard(engine::io::Window* window) : engine::io::Keyboard(window) {
			engine::core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_KEY_DOWN", 15), this);
			engine::core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_KEY_RELEASE", 18), this);
		}

		WindowsKeyboard::~WindowsKeyboard() {
		}

		bool WindowsKeyboard::GetKeyDown(unsigned int keyCode) const {
			return m_PressedKeys.find(keyCode) != m_PressedKeys.end();
		}

		bool WindowsKeyboard::GetKeyToggled(unsigned int keyCode) const {
			return GetKeyState(WindowsKeyMap::GetKeyCode(keyCode)) & 0b1;
		}

		bool WindowsKeyboard::OnEvent(engine::events::Event* event) {
			engine::events::KeyEvent* keyEvent = (engine::events::KeyEvent*)event;

			engine::io::Window* wndPtr = keyEvent->GetWindow();

			if (keyEvent->GetWindow() != m_Window) return false;

			unsigned int id = keyEvent->GetID();

			if (keyEvent->GetID() == Hash("EVENT_KEY_DOWN", 15)) {
				m_PressedKeys.insert(keyEvent->GetKeyCode());
				return false;
			}
			else if (keyEvent->GetID() == Hash("EVENT_KEY_RELEASE", 18)) {
				m_PressedKeys.erase(keyEvent->GetKeyCode());
				return false;
			}
			return false;
		}
	}
}