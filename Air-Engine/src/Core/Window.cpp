#include <GL/glew.h>
#include <GL/wglew.h>
#include "Window.hpp"
#include <stdlib.h>


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
			InitOpenGL();
			
			return 1;
		}

		int Window::InitOpenGL() {
			//This is a dummy pixelformat
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
			//TODO pointer functions laden

			mHRC = wglCreateContext(mHDC);
			wglMakeCurrent(mHDC, mHRC);
			
			if (glewInit()) {				
				return -1;
			}

			GLint contextAttribs[] =
			{
				// Here we ask for OpenGL 2.1
				WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
				WGL_CONTEXT_MINOR_VERSION_ARB, 0,
				// Uncomment this for forward compatibility mode
				//WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
				// Uncomment this for Compatibility profile
				//WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
				// We are using Core profile here
				WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
				0
			};

			HGLRC advContext = wglCreateContextAttribsARB(mHDC, NULL, contextAttribs);

			wglDeleteContext(mHRC);

			mHRC = advContext;

			wglMakeCurrent(mHDC, mHRC);

			GLint major;
			char* version = (char*) glGetString(GL_VERSION);

			return 0;
		}

		void Window::Update() {
			//UpdateWindow(mWindow);
			SwapBuffers(mHDC);
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
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