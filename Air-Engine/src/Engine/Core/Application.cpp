#include "Application.hpp"
#include "../../Platform/Windows/WindowsWindow.hpp"

namespace engine {
	namespace core {

		Application::Application() {
			mWindow = new platform::windows::WindowsWindow(500, 600, L"Application");
			mWindow->Initialize();

			mWindow->SetVisibility(AIR_W_SHOW);
		}

		Application::~Application() {
			delete mWindow;
		}

		bool Application::Run() {
			while (true) {
				mWindow->Update();
			}
			return true;
		}

	}
}