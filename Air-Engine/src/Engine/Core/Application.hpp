#pragma once

namespace platform {
	namespace windows {
		class Console;
	}
}

namespace engine {
	namespace core {

		class Window;

		class Application {
		protected:
			Window* mWindow;
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