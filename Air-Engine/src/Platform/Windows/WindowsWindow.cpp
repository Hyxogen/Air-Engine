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
			m_Window = nullptr;
		}

		WindowsWindow::~WindowsWindow() {
			AIR_CORE_LOG_INFO("Destroying windows window");
			ReleaseDC(m_Window, GetHDC());
			DestroyWindow(m_Window);
			delete m_EventHandler;
			AIR_CORE_LOG_INFO("Succesfully destroyed window");
		}

		bool WindowsWindow::Initialize() {
			AIR_CORE_LOG_INFO("Initializing WindowsWindow");
			m_ShouldClose = false;

			WNDCLASS wndClass = { };
			HINSTANCE instance = GetModuleHandleA(0);

			wndClass.lpfnWndProc = (WNDPROC)WindowProc;
			wndClass.hInstance = instance;
			wndClass.lpszClassName = m_Title;

			RegisterClass(&wndClass);

			m_Window = CreateWindowEx(CS_OWNDC, m_Title, m_Title, WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				NULL, NULL, instance, NULL);

			if (m_Window == NULL) {
				AIR_CORE_LOG_ERROR("Failed to create window handle");
				return 1;
			}
			SetWindowLongPtr(m_Window, GWLP_USERDATA, (LONG_PTR)this);

			m_DeviceContext = GetDC(m_Window);
			m_EventHandler = new WindowsWindowEventHandler(this);

			AIR_CORE_LOG_INFO("Succesfully created a windows window");
			return 0;
		}

		void WindowsWindow::Update() {
			MSG msg;
			while (PeekMessageW(&msg, m_Window, 0, 0, PM_REMOVE)) {
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
			ShowWindow(m_Window, visibility);
		}

		void WindowsWindow::Close() {
			m_ShouldClose = true;
		}

		LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
			if (uMsg == WM_CLOSE || uMsg == WM_QUIT || uMsg == WM_DESTROY) {
				WindowsWindow* window = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
				window->Close();
				PostQuitMessage(0);
				return 0;
			} else {
				WindowsWindow* window = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
				if (window != nullptr) {
					WindowsWindowEvent event(window, uMsg, wParam, lParam);
					if (engine::core::Application::GetApplication()->GetDispatcher()->Dispatch(&event))
						return 0;
				}
			}
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
}