#include "Window.hpp"
#include <windows.h>



namespace engine {
	namespace core {
		LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


		Window::Window(int width, int height, const char* name) {
			mWidth = width;
			mHeight = height;
			mName = name;
			mWindow = nullptr;
		}

		Window::~Window() {
			DestroyWindow((HWND)mWindow);
		}

		
		bool Window::Initialize() {
			mShouldClose = false;

			WNDCLASS wndClass = { };

			int length = strlen(mName) + 1;
			wchar_t* CLASS_NAME = new wchar_t[length];

			mbstowcs_s(nullptr, CLASS_NAME, length, mName, length);

			HINSTANCE instance = GetModuleHandleA(0);

			wndClass.lpfnWndProc = WindowProc;
			wndClass.hInstance = instance;
			wndClass.lpszClassName = CLASS_NAME;

			RegisterClass(&wndClass);

			mWindow = CreateWindowEx(0, CLASS_NAME, CLASS_NAME, WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				NULL, NULL, instance, NULL);

			if (mWindow == NULL) {
				return 0;
			}
			ShowWindow((HWND)mWindow, 10);;

			return 1;
		}

		void Window::Update() {
			MSG msg;
			if (!(mShouldClose = (GetMessage(&msg, (HWND)mWindow, 0, 0) == 0))) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			return;
		}

		LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
}