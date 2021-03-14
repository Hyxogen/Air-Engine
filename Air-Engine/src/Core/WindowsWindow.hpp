#pragma once

#include "Window.hpp"
#include <windows.h>

/*
SetVisibility() values
*/
#define AIR_W_SHOW SW_SHOW
#define AIR_W_HIDE SW_HIDE

namespace engine {
	namespace core {

		class WindowsWindow : public Window {

			HWND mWindow;
			HDC mHDC;
			HGLRC mHRC;
			bool mShouldClose = false;

			int InitOpenGL();

		public:
			WindowsWindow(int width, int height, const wchar_t* title);

			~WindowsWindow() override;

			void Update();

			void SetVisibility(short visibilty);

			/*
			Informs the program the window should close and stops the updates
			*/
			void Close();

			inline bool ShouldClose() const { return mShouldClose; }

			bool Initialize() override;

			//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		};

	}
}