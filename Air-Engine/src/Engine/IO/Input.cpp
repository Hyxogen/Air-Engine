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
		}

		Input* Input::GetInstance() {
			if (s_Instance == nullptr)
				return new Input();

			return s_Instance;
		}
	}
}