#include "Application.hpp"
#include "Assert.hpp"

#include "../Events/EventDispatcher.hpp"

#include "../IO/Input.hpp"

#include "../../Platform/Windows/WindowsKeyboard.hpp"
#include "../../Platform/Windows/WindowsMouse.hpp"

#include "../../Platform/Windows/WindowsWindow.hpp"
#include "../../Platform/Windows/Console.hpp"
#include "Assert.hpp"
#include "../Events/EventDispatcher.hpp"
#include "../../Platform/Windows/GLContextAdapter.hpp"

#include <glad\gl.h>

#include <chrono>
#include <iostream>

namespace engine {
	namespace core {

		Application* Application::s_Application = nullptr;

		Application::Application() {
			ASSERT(s_Application == nullptr);
			s_Application = this;
			ASSERT(!Initialize());
		}

		Application::~Application() {
			delete mWindow;
			delete mDispatcher;
			delete m_ContextAdapter;
			delete mConsole;
			delete io::Input::GetInstance();
		}

		bool Application::Initialize() {
			mDispatcher = new events::EventDispatcher();

			mConsole = new platform::windows::Console();
			if (mConsole->Initialize())
				return true;

			mWindow = new platform::windows::WindowsWindow(500, 600, L"Application");
			m_ContextAdapter = new platform::windows::GLContextAdapter((platform::windows::WindowsWindow*)mWindow, 4, 6);

			mWindow->Initialize();
			m_ContextAdapter->Initialize();

			io::Input::GetInstance()->Initialize();


			mWindow->SetVisibility(AIR_W_SHOW);
			return false;
		}

		bool Application::Run() {
			while (!mWindow->ShouldClose()) {
				auto beg = std::chrono::system_clock::now();
				Update();
				auto end = std::chrono::system_clock::now();
				std::chrono::duration<float> diff = end - beg;

				//std::chrono::milliseconds mic = std::chrono::duration_cast<std::chrono::microseconds>(diff);
				
				printf("Took %f\n", diff.count());
			}
			return true;
		}

		static float red = 0.0f;
		void Application::Update() {
			mWindow->Update();
			mWindow->Draw();

			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(red, 0.5f, 0.5f, 1.0f);
			red += 0.01f;
			if (red >= 1.0f)
				red = 0.0f;
		}

	}
}