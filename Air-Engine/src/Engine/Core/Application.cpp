#include "Application.hpp"
#include "../../Platform/Windows/WindowsWindow.hpp"
#include "../../Platform/Windows/Console.hpp"
#include "Assert.hpp"
#include "../Events/EventDispatcher.hpp"
#include "../Events/TestEvent.hpp"
#include "../Events/FooEvent.hpp"


namespace engine {
	namespace core {

		void OnEvent(const events::Event* event);

		Application::Application() {
			if (!Initialize())
				Run();
		}

		Application::~Application() {
			delete mWindow;
			delete mDispatcher;
		}

		bool Application::Initialize() {
			mConsole = new platform::windows::Console();
			if (mConsole->Initialize())
				return true;

			mWindow = new platform::windows::WindowsWindow(500, 600, L"Application");
			mWindow->Initialize();

			mWindow->SetVisibility(AIR_W_SHOW);

			mDispatcher = new events::EventDispatcher();
			mDispatcher->RegisterListener<events::TestEvent>((LISTENER_FUNCTION)OnEvent);

			events::TestEvent* testEvent = new events::TestEvent(5);

			mDispatcher->DispatchEvent(testEvent);

			delete testEvent;
			delete mDispatcher;
			return false;
		}

		void OnEvent(const events::Event* event) {
			return;
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