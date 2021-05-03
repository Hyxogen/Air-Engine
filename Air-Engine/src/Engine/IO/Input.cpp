#include "Input.hpp"

#include "Keyboard.hpp"
#include "Mouse.hpp"

#include "../Core/Application.hpp"
#include "../Util/Logger/Logger.hpp"

namespace engine {
	namespace io {

		Input* Input::s_Instance = nullptr;

		bool Input::Initialize() {
			AIR_CORE_WARN("This is a simple helper class for handling input. Please be aware that this will most likely be removed or changed once multiple window support gets added")
			m_Keyboard = Keyboard::Create(core::Application::GetApplication()->GetWindow());
			m_Mouse = Mouse::Create(core::Application::GetApplication()->GetWindow());
			return false;
		}

		Input* Input::GetInstance() {
			if (s_Instance == nullptr)
				s_Instance = new Input();

			return s_Instance;
		}
	}
}