#pragma once

#include "../IO/Window.hpp"

namespace engine {
	namespace core {

		class Application {
		protected:
			Window* mWindow;

		public:
			Application();

			virtual ~Application();

			bool Run();
		};

		Application* CreateApplication();
	}
}