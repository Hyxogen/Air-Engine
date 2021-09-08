#include "airpch.h"

#include "Application.hpp"
#include "../Events/EventDispatcher.hpp"

#include "../IO/Input.hpp"

#include "../../Platform/Windows/WindowsKeyboard.hpp"
#include "../../Platform/Windows/WindowsMouse.hpp"

#include "../../Platform/Windows/WindowsWindow.hpp"
#include "../../Platform/Windows/Console.hpp"
#include "../../Platform/Windows/GLContextAdapter.hpp"
#include "../../Platform/Windows/ConsoleSink.h"

#include "../Events/EventDispatcher.hpp"

#include "../Math/Vector2.hpp"
#include "../Math/Vector3.hpp"

#include <glad\wgl.h>
#include <glad\gl.h>

namespace engine {
	namespace core {

		Application* Application::s_Application = nullptr;

		Application::Application() : m_Window(nullptr), m_Dispatcher(nullptr), m_ContextAdapter(nullptr), m_Console(nullptr) {
			ASSERT(s_Application == nullptr);
			s_Application = this;
			ASSERT(!Initialize());
		}

		Application::~Application() {
			AIR_CORE_INFO("Shutting down Air Engine...")
			delete m_Window;
			delete m_Dispatcher;
			delete m_ContextAdapter;
			delete m_Console;
			delete io::Input::GetInstance();
			delete util::Logger::GetCoreLogger();
		}

		bool Application::Initialize() {
			m_Console = new platform::windows::Console();
			if (m_Console->Initialize())
				return true;

			AIR_CORE_INFO("Starting Air Engine...");

			m_Dispatcher = new events::EventDispatcher();

			m_Window = new platform::windows::WindowsWindow(500, 600, L"Application");
			m_ContextAdapter = new platform::windows::GLContextAdapter((platform::windows::WindowsWindow*)m_Window, 4, 6);

			if (io::Input::GetInstance()->Initialize())
				return true;

			math::Vector3f vector(std::move(math::Vector3f(4.0f, 5.0f, 6.0f)));
			math::Vector3f zero = math::Vector3f(6.0f, 5.0f, 4.0f);

			math::Vector3f invert = -vector;
			math::Vector3f addition(vector);
			//math::Vector3f between = ((0.5f * vector) - (0.5f * zero));
			math::Vector3f between = math::Vector3f::Lerp(vector, zero, 0.3f);
			bool check = invert < (addition);

			bool equal = (vector == (addition * 0));

			int32 i = 1;

			//float x = vector.Dot(zero + math::Vector3f::Zero());
			float y = addition[i];

			//AIR_CORE_INFO((addition + math::Vector3f::Zero()));

			if (m_Window->Initialize())
				return true;
			if (m_ContextAdapter->Initialize())
				return true;

			m_Window->SetVisibility(AIR_W_SHOW);
			
			AIR_CORE_INFO("Finished initializing");
			return false;
		}

		bool Application::Run() {
			while (!m_Window->ShouldClose()) {
				if (io::Input::GetInstance()->GetKeyboard()->GetKeyDown(io::KEY_W))
					AIR_CORE_INFO("Key down!");
				Update();
			}
			return true;
		}

		void Application::Update() {
			m_Window->Update();
			m_Window->Draw();

			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		}

	}
}