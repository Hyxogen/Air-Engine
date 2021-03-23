#pragma once

namespace engine {
	namespace core {

		class Window {

		protected:
			int mWidth, mHeight;
			const wchar_t* mTitle;
			
			Window(const wchar_t* title, int width, int height) : mTitle(title), mWidth(width), mHeight(height) {}

		public:
			virtual ~Window() {};

			virtual bool Initialize() = 0;

			virtual void Update() = 0;

			virtual void SetVisibility(short visibility) = 0;

			inline int GetWidth() const { return mWidth; }

			inline int GetHeight() const { return mHeight; }
		};

	}
}