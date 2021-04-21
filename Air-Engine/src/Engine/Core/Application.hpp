#pragma once

namespace platform {
	namespace windows {
		class Console;
	}
}

namespace engine {

	namespace events {
		class EventDispatcher;
	}

	namespace io {
		class Window;
		class Keyboard;
	}

	namespace core {

		class Application {
			static Application* s_Application;

		protected:
			io::Window* mWindow;
			events::EventDispatcher* mDispatcher;
			platform::windows::Console* mConsole;

			io::Keyboard* m_Keyboard;

		public:
			Application();

			virtual ~Application();

			//Returns false if no errors 
			bool Initialize();

			bool Run();

			void Update();

			inline io::Window* GetWindow() const { return mWindow; }

			inline events::EventDispatcher* GetDispatcher() const { return mDispatcher; }

			static Application* GetApplication() { return s_Application; }
		};

		Application* CreateApplication();
	}
}