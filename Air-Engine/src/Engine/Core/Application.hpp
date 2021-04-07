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

	namespace core {

		class Window;

		class Application {
		protected:
			Window* mWindow;
			events::EventDispatcher* mDispatcher;
			platform::windows::Console* mConsole;

		public:
			Application();

			virtual ~Application();

			//Returns false if no errors 
			bool Initialize();

			bool Run();

			void Update();

			inline Window* GetWindow() const { return mWindow; }
		};

		Application* CreateApplication();
	}
}