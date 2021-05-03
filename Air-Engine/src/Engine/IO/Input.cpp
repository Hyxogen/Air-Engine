#include "Input.hpp"

#include "Keyboard.hpp"
#include "Mouse.hpp"

#include "../Core/Application.hpp"

namespace engine {
	namespace io {

		Input* Input::s_Instance = nullptr;

		bool Input::Initialize() {
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