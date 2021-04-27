#include <GL/glew.h>
#include <GL/wglew.h>
#include <stdlib.h>

#include "WindowsWindow.hpp"
#include "WindowsWindowEventHandler.hpp"
#include "Events/WindowsWindowEvent.hpp"

#include "../../Engine/Core/Application.hpp"
#include "../../Engine/Events/EventDispatcher.hpp"
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
			delete m_EventHandler;
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

			SetWindowLongPtr(mWindow, GWLP_USERDATA, (LONG_PTR)this);

			m_EventHandler = new WindowsWindowEventHandler(this);

			AIR_CORE_LOG_INFO("Succesfully created a windows window");
			return 0;
		}

		void WindowsWindow::Update() {
			SwapBuffers(GetHDC()); //Dit moet in theorie alleen gebeuren als het dual buffers zijn
			MSG msg;
			if (GetMessage(&msg, mWindow, 0, 0) > 0) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
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
			if (uMsg == WM_CLOSE || uMsg == WM_QUIT || uMsg == WM_DESTROY) {
				WindowsWindow* window = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
				window->Close();
				PostQuitMessage(0);
				return 0;
			} if (uMsg == WM_GETICON) {
				return 0;
			}
			else {
				WindowsWindow* window = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
				WindowsWindowEvent event(window, uMsg, wParam, lParam);
				if (engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(&event))
					return 0;
			}
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
}