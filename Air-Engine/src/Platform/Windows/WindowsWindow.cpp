#include "airpch.h"
#include "WindowsWindow.hpp"
#include "WindowsWindowEventHandler.hpp"
#include "Events/WindowsWindowEvent.hpp"

#include "../../Engine/Core/Application.hpp"
#include "../../Engine/Events/EventDispatcher.hpp"
#include "../../Engine/Util/Logger/Logger.hpp"

namespace platform {
	namespace windows {
		LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


		WindowsWindow::WindowsWindow(int32 width, int32 height, const wchar_t* title) : Window(title, width, height), m_DeviceContext(nullptr), m_EventHandler(nullptr) {
			m_Window = nullptr;
		}

		WindowsWindow::~WindowsWindow() {
			AIR_CORE_INFO("Destroying windows window");
			ReleaseDC(m_Window, GetHDC());
			DestroyWindow(m_Window);
			delete m_EventHandler;
			AIR_CORE_INFO("Succesfully destroyed window");
		}

		bool WindowsWindow::Initialize() {
			AIR_CORE_INFO("Initializing WindowsWindow");
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
				AIR_CORE_ERROR("Failed to create window handle");
				return 1;
			}
			SetWindowLongPtr(m_Window, GWLP_USERDATA, (LONG_PTR)this);

			m_DeviceContext = GetDC(m_Window);
			m_EventHandler = new WindowsWindowEventHandler(this);

			AIR_CORE_INFO("Succesfully created a windows window");
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

		void WindowsWindow::SetVisibility(int16 visibility) {
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
			}
			else {
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