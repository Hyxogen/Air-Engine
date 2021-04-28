#pragma once

namespace platform {
	namespace windows {
		class Console;
		class GLContextAdapter;
	}
}

namespace engine {

	namespace events {
		class EventDispatcher;
	}

	namespace io {
		class Window;
	}

	namespace core {

		class Application {
		protected:
			io::Window* mWindow;
			events::EventDispatcher* mDispatcher;
			platform::windows::Console* mConsole;
			platform::windows::GLContextAdapter* m_ContextAdapter;

		public:
			Application();

			virtual ~Application();

			//Returns false if no errors 
			bool Initialize();

			bool Run();

			void Update();

			inline io::Window* GetWindow() const { return mWindow; }

			inline events::EventDispatcher* GetDispatcher() const { return mDispatcher; }

			inline platform::windows::GLContextAdapter* GetContextAdapter() const { return m_ContextAdapter; }
		};

		Application* CreateApplication();
	}
}