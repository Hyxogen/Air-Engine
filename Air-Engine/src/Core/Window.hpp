#pragma once

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

/*
SetVisibility() values
*/
#define AIR_W_SHOW SW_SHOW
#define AIR_W_HIDE SW_HIDE

namespace engine {
	namespace core {

		class Window {

			int mWidth, mHeight;
			const char* mName;
			HWND mWindow;
			HDC mHDC;
			HGLRC mHRC;
			bool mShouldClose = false;

		public:

			Window(int width, int height, const char* name);

			~Window();

			bool Initialize();

			void Update();

			void SetVisibility(short visibilty);

			/*
			Informs the program the window should close and stops the updates
			*/
			void Close();

			inline bool ShouldClose() const { return mShouldClose; }

			//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		};

	}
}