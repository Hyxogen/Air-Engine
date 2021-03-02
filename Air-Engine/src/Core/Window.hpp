#pragma once

namespace engine {
	namespace core {

		class Window {

			int mWidth, mHeight;
			const char* mName;
		public:
			void* mWindow;

			Window(int width, int height, const char* name);

			~Window();

			bool Initialize();

		};

	}
}