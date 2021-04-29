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
			static Application* s_Application;

		protected:
			io::Window* m_Window;
			events::EventDispatcher* m_Dispatcher;
			platform::windows::Console* m_Console;
			platform::windows::GLContextAdapter* m_ContextAdapter;

		public:
			Application();

			virtual ~Application();

			//Returns false if no errors 
			bool Initialize();

			bool Run();

			void Update();

			inline io::Window* GetWindow() const { return m_Window; }

			inline events::EventDispatcher* GetDispatcher() const { return m_Dispatcher; }

			inline platform::windows::GLContextAdapter* GetContextAdapter() const { return m_ContextAdapter; }

			static Application* GetApplication() { return s_Application; }
		};

		Application* CreateApplication();
	}
}