#pragma once

namespace engine {
	namespace core {

		class Window {

		protected:
			int mWidth, mHeight;
			const wchar_t* mTitle;
			
			Window(const wchar_t* title, int width, int height) : mTitle(title), mWidth(width), mHeight(height) {}

			virtual ~Window() {};

			virtual bool Initialize() = 0;
		};

	}
}