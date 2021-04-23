#include "WindowsMouse.hpp"

#include "Events/WindowsMouseEvent.hpp"

#include "../../Engine/Util/Logger/Logger.hpp"
#include "../../Engine/Core/Assert.hpp"
#include "../../Engine/Util/HashUtils.hpp"
#include "../../Engine/Core/Application.hpp"
#include "../../Engine/Events/EventDispatcher.hpp"

#include <windows.h>

namespace platform {
	namespace windows {

		WindowsMouse::WindowsMouse(engine::io::Window* window) : Mouse(window) {
			m_Buttons = new bool[(unsigned int)MouseCode::NONE];

			memset(m_Buttons, 0, sizeof(bool) * (unsigned int)MouseCode::NONE);

			engine::core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_MOUSE_BUTTON_DOWN", 24), this);
			engine::core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_MOUSE_BUTTON_RELEASE", 27), this);
			engine::core::Application::GetApplication()->GetDispatcher()->Register(Hash("EVENT_MOUSE_MOVE", 17), this);
		}

		WindowsMouse::~WindowsMouse() {
			delete m_Buttons;
		}

		bool WindowsMouse::HasScrollWheel() const {
			return GetSystemMetrics(SM_MOUSEWHEELPRESENT);
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
			return m_Buttons[(unsigned int) mouseCode];
		}

		bool WindowsMouse::OnEvent(engine::events::Event& event) {
			engine::events::MouseEvent& mouseEvent = (engine::events::MouseEvent&)event;

			if (mouseEvent.GetWindow() != m_Window) return false;
			
			if (mouseEvent.GetID() == Hash("EVENT_MOUSE_MOVE", 17)) {
				AIR_CORE_LOG_TRACE("EVENT_MOUSE_MOVE");
			}
			else if (mouseEvent.GetID() == Hash("EVENT_MOUSE_BUTTON_DOWN", 24)) {
				m_Buttons[(unsigned int)((engine::events::MouseButtonEvent&)mouseEvent).GetMouseCode()] = true;
			}
			else {
				m_Buttons[(unsigned int)((engine::events::MouseButtonEvent&)mouseEvent).GetMouseCode()] = false;
			}
			return false;
		}
	}
}