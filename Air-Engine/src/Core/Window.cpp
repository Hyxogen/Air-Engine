#include "Window.hpp"

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
			wglMakeCurrent(NULL, NULL);
			ReleaseDC(mWindow, mHDC);
			wglDeleteContext(mHRC);
			DestroyWindow(mWindow);
		}


		bool Window::Initialize() {
			mShouldClose = false;

			WNDCLASS wndClass = { };

			int length = strlen(mName) + 1;
			wchar_t* CLASS_NAME = new wchar_t[length];

			mbstowcs_s(nullptr, CLASS_NAME, length, mName, length);

			HINSTANCE instance = GetModuleHandleA(0);

			wndClass.lpfnWndProc = (WNDPROC)WindowProc;
			wndClass.hInstance = instance;
			wndClass.lpszClassName = CLASS_NAME;

			RegisterClass(&wndClass);
			
			mWindow = CreateWindowEx(CS_OWNDC, CLASS_NAME, CLASS_NAME, WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				NULL, NULL, instance, NULL);

			if (mWindow == NULL) {
				return 0;
			}

			PIXELFORMATDESCRIPTOR test =
			{
				sizeof(PIXELFORMATDESCRIPTOR),
				1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
				PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
				32,                   // Colordepth of the framebuffer.
				0, 0, 0, 0, 0, 0,
				0,
				0,
				0,
				0, 0, 0, 0,
				24,                   // Number of bits for the depthbuffer
				8,                    // Number of bits for the stencilbuffer
				0,                    // Number of Aux buffers in the framebuffer.
				PFD_MAIN_PLANE,
				0,
				0, 0, 0 
			};

			PIXELFORMATDESCRIPTOR pfd;
			//https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL)
			// Get DC
			// Create dummy pixel format with PIXELFORMATDESCRIPTOR 
			// Make contects using dummy pixel format

			memset(&pfd, 0, sizeof(pfd));
			pfd.nSize = sizeof(pfd);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 32;
			pfd.cDepthBits = 24;
			pfd.cStencilBits = 8;
			pfd.iLayerType = PFD_MAIN_PLANE;

			mHDC = GetDC(mWindow);
			int pfn = ChoosePixelFormat(mHDC, &pfd);
			if (pfn == 0) {
				MessageBox(NULL, L"ERR", L"ERR", MB_OK);
				return -1;
			}
			SetPixelFormat(mHDC, pfn, &pfd);
			
			//DescribePixelFormat(mHDC, pfn, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

			//ReleaseDC((HWND)mWindow, hdc);

			mHRC = wglCreateContext(mHDC);
			wglMakeCurrent(mHDC, mHRC);
			return 1;
		}

		void Window::Update() {
			//UpdateWindow(mWindow);
			SwapBuffers(mHDC);
			glClear(GL_COLOR_BUFFER_BIT);
			glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2i(0, 1);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2i(-1, -1);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex2i(1, -1);
			glEnd();
			glFlush();
			MSG msg;
			if (GetMessage(&msg, mWindow, 0, 0) > 0) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else {
				mShouldClose = true;
			}

			return;
		}

		void Window::SetVisibility(short visibility) {
			ShowWindow(mWindow, visibility);
		}

		void Window::Close() {
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