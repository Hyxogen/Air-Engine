#include <GL/glew.h>
#include <GL/wglew.h>
#include <stdlib.h>
#include "WindowsWindow.hpp"


namespace platform {
	namespace windows {
		LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


		WindowsWindow::WindowsWindow(int width, int height, const wchar_t* title) : Window(title, width, height) {
			mWindow = nullptr;
		}

		WindowsWindow::~WindowsWindow() {
			ReleaseDC(mWindow, GetHDC());
			DestroyWindow(mWindow);
		}

		bool WindowsWindow::Initialize() {
			mShouldClose = false;

			WNDCLASS wndClass = { };
			HINSTANCE instance = GetModuleHandleA(0);

			wndClass.lpfnWndProc = (WNDPROC)WindowProc;
			wndClass.hInstance = instance;
			wndClass.lpszClassName = mTitle;

			RegisterClass(&wndClass);
			
			mWindow = CreateWindowEx(CS_OWNDC, mTitle, mTitle, WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				NULL, NULL, instance, NULL);

			if (mWindow == NULL) {
				return 1;
			}

			return 0;
		}

		void WindowsWindow::Update() {
			SwapBuffers(GetHDC()); //Dit moet in theorie alleen gebeuren als het dual buffers zijn
			MSG msg;
			if (GetMessage(&msg, mWindow, 0, 0) > 0) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else {
				mShouldClose = true;
			}

			return;
		}

		void WindowsWindow::SetVisibility(short visibility) {
			ShowWindow(mWindow, visibility);
		}

		void WindowsWindow::Close() {
			mShouldClose = true;
		}

		LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
			switch (uMsg) {
			case WM_CLOSE:
				PostQuitMessage(0);
				return 0;
			case WM_QUIT:
				PostQuitMessage(0);
				return 0;
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
			case WM_PAINT:
				return 0;
			}
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
}