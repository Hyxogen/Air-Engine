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
			delete m_Window;
			delete m_Dispatcher;
			delete m_ContextAdapter;
			delete m_Console;
			delete io::Input::GetInstance();
		}

		bool Application::Initialize() {
			m_Dispatcher = new events::EventDispatcher();

			m_Console = new platform::windows::Console();
			if (m_Console->Initialize())
				return true;

			m_Window = new platform::windows::WindowsWindow(500, 600, L"Application");
			m_ContextAdapter = new platform::windows::GLContextAdapter((platform::windows::WindowsWindow*)m_Window, 4, 6);

			m_Window->Initialize();
			m_ContextAdapter->Initialize();

			io::Input::GetInstance()->Initialize();
			platform::windows::ConsoleSink sink;

			util::Logger::GetCoreLogger()->AddSink(&sink);
			util::Logger::GetCoreLogger()->Log(util::SE_ERROR, "Failed succesfully!");
			


			m_Window->SetVisibility(AIR_W_SHOW);
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