#include "Application.hpp"
#include "../../Platform/Windows/WindowsWindow.hpp"
#include "../../Platform/Windows/Console.hpp"

namespace engine {
	namespace core {

		Application::Application() {
			if (!Initialize())
				Run();
		}

		Application::~Application() {
			delete mWindow;
		}

		bool Application::Initialize() {
			mConsole = new platform::windows::Console();
			if (mConsole->Initialize())
				return true;

			mWindow = new platform::windows::WindowsWindow(500, 600, L"Application");
			mWindow->Initialize();

			mWindow->SetVisibility(AIR_W_SHOW);
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