#include "Application.hpp"
#include "Assert.hpp"

#include "../Events/EventDispatcher.hpp"
#include "../IO/Keyboard.hpp"

#include "../../Platform/Windows/WindowsWindow.hpp"
#include "../../Platform/Windows/Console.hpp"

namespace engine {
	namespace core {

		Application* Application::sAPPLICATION = nullptr;

		Application::Application() {
			ASSERT(sAPPLICATION == nullptr);
			sAPPLICATION = this;
			ASSERT(!Initialize());
		}

		Application::~Application() {
			delete mWindow;
			delete mDispatcher;
			delete m_Keyboard;
		}

		bool Application::Initialize() {
			mDispatcher = new events::EventDispatcher();

			mConsole = new platform::windows::Console();
			if (mConsole->Initialize())
				return true;

			mWindow = new platform::windows::WindowsWindow(500, 600, L"Application");
			mWindow->Initialize();

			mWindow->SetVisibility(AIR_W_SHOW);

			m_Keyboard = new io::Keyboard(mWindow);

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
		}

	}
}