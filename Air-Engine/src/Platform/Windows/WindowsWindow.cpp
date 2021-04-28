#include <stdlib.h>
#include "WindowsWindow.hpp"
#include "../../Engine/Util/Logger/Logger.hpp"

namespace platform {
	namespace windows {
		LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


		WindowsWindow::WindowsWindow(int width, int height, const wchar_t* title) : Window(title, width, height) {
			mWindow = nullptr;
		}

		WindowsWindow::~WindowsWindow() {
			AIR_CORE_LOG_INFO("Destroying windows window");
			ReleaseDC(mWindow, GetHDC());
			DestroyWindow(mWindow);
			AIR_CORE_LOG_INFO("Succesfully destroyed window");
		}

		bool WindowsWindow::Initialize() {
			AIR_CORE_LOG_INFO("Initializing WindowsWindow");
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
				AIR_CORE_LOG_ERROR("Failed to create window handle");
				return 1;
			}

			m_DeviceContext = GetDC(mWindow);

			AIR_CORE_LOG_INFO("Succesfully created a windows window");
			return 0;
		}

		void WindowsWindow::Update() {
			MSG msg;
			while (PeekMessageW(&msg, mWindow, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
			return;
		}

		void WindowsWindow::Draw() {
			if (GetHDC() == nullptr) return;
			SwapBuffers(GetHDC()); //Dit moet in theorie alleen gebeuren als het dual buffers zijn
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
				return 0;
			case WM_QUIT:
				return 0;
			case WM_DESTROY:
				return 0;
			}
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
}