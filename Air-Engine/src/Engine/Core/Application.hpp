#pragma once

namespace engine {
	namespace core {

		class Application {
		public:
			Application();

			virtual ~Application();

			bool Run();
		};

		Application* CreateApplication();
	}
}