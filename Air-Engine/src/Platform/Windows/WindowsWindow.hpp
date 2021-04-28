#pragma once

#include "..\..\Engine\IO\Window.hpp"
#include <windows.h>

/*
SetVisibility() values
*/
#define AIR_W_SHOW SW_SHOW
#define AIR_W_HIDE SW_HIDE

namespace platform {
	namespace windows {

		class WindowsWindow : public engine::io::Window {

		protected:
			HWND mWindow;
			HDC m_DeviceContext;
			bool mShouldClose = false;

		public:
			WindowsWindow(int width, int height, const wchar_t* title);

			virtual ~WindowsWindow();

			void Update();
			
			void Draw();

			void Close();
			
			bool Initialize() override;

			void SetVisibility(short visibilty);

			/*
			Informs the program the window should close and stops the updates
			*/

			inline bool ShouldClose() const { return mShouldClose; }

			inline HDC GetHDC() const { return m_DeviceContext; }

			inline HWND GetWindowHandle() const { return mWindow; }
			//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		};

	}
}