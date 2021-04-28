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
		class Keyboard;
		class Mouse;
	}

	namespace core {

		class Application {
			static Application* s_Application;

		protected:
			io::Window* mWindow;
			events::EventDispatcher* mDispatcher;
			platform::windows::Console* mConsole;
			platform::windows::GLContextAdapter* m_ContextAdapter;

			io::Keyboard* m_Keyboard;
			io::Mouse* m_Mouse;

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