#pragma once

namespace engine {
	namespace core {

		class Window {

		protected:
			int mWidth, mHeight;
			const wchar_t* mTitle;
			
			Window();

			Window(const wchar_t* title, int width, int height);

			virtual ~Window() = 0;

			virtual bool Initialize() = 0;
		};

	}
}