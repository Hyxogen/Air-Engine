#include "Application.hpp"
#include "Assert.hpp"

#include "Assert.hpp"
#include "../Events/EventDispatcher.hpp"

#include "../IO/Input.hpp"

#include "../Util/Logger/Logger.hpp"

#include "../../Platform/Windows/WindowsKeyboard.hpp"
#include "../../Platform/Windows/WindowsMouse.hpp"

#include "../../Platform/Windows/WindowsWindow.hpp"
#include "../../Platform/Windows/Console.hpp"
#include "../../Platform/Windows/GLContextAdapter.hpp"
#include "../../Platform/Windows/ConsoleSink.h"

#include "../Events/EventDispatcher.hpp"

#include <glad\gl.h>

namespace engine {
	namespace core {

		Application* Application::s_Application = nullptr;

		Application::Application() {
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

			AIR_CORE_ERROR_IF(io::Input::GetInstance()->Initialize(), "Failed to initialize input helper class");

			m_Window = new platform::windows::WindowsWindow(500, 600, L"Application");
			m_ContextAdapter = new platform::windows::GLContextAdapter((platform::windows::WindowsWindow*)m_Window, 4, 6);

			AIR_CORE_ERROR_IF(m_Window->Initialize(), "Failed to initialize window");
			AIR_CORE_ERROR_IF(m_ContextAdapter->Initialize(), "Failed to initialize a OpenGL context");

			m_Window->SetVisibility(AIR_W_SHOW);
			
			AIR_CORE_INFO("Finished initializing");
			return false;
		}

		bool Application::Run() {
			while (!m_Window->ShouldClose()) {
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