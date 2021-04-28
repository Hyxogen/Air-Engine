#include "Application.hpp"
#include "../../Platform/Windows/WindowsWindow.hpp"
#include "../../Platform/Windows/Console.hpp"
#include "Assert.hpp"
#include "../Events/EventDispatcher.hpp"
#include "../../Platform/Windows/GLContextAdapter.hpp"

#include <glad\gl.h>

namespace engine {
	namespace core {

		Application::Application() {
			ASSERT(!Initialize());
		}

		Application::~Application() {
			delete mWindow;
			delete mDispatcher;
			delete m_ContextAdapter;
		}

		bool Application::Initialize() {
			mConsole = new platform::windows::Console();
			if (mConsole->Initialize())
				return true;

			mWindow = new platform::windows::WindowsWindow(500, 600, L"Application");
			m_ContextAdapter = new platform::windows::GLContextAdapter((platform::windows::WindowsWindow*)mWindow, 4, 6);

			mWindow->Initialize();
			m_ContextAdapter->Initialize();

			mWindow->SetVisibility(AIR_W_SHOW);
			mDispatcher = new events::EventDispatcher();

			return false;
		}

		bool Application::Run() {
			while (!mWindow->ShouldClose()) {
				Update();
			}
			return true;
		}

		void Application::Update() {
			mWindow->Update();
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.2f, 0.5f, 0.5f, 1.0f);
		}

	}
}