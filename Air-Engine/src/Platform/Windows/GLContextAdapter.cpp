#include <GL/glew.h>
#include <GL/wglew.h>
#include "GLContextAdapter.hpp"
#include "WindowsWindow.hpp"

namespace platform {
	namespace windows {

		GLContextAdapter::GLContextAdapter(WindowsWindow* window, unsigned short major, unsigned short minor) : mWindow(window), mMajorVersion(major), mMinorVersion(minor) {
		}

		GLContextAdapter::~GLContextAdapter() {
			wglMakeCurrent(mWindow->GetHDC(), NULL);
			wglDeleteContext(mContext);
		}

		bool GLContextAdapter::Initialize() {
			HDC hdc = GetDC(mWindow->getWindowHandle());

			PIXELFORMATDESCRIPTOR pfd = GetPixelDescriptor();

			int pixelFormat = ChoosePixelFormat(hdc, &pfd);
			if (pixelFormat == 0) {
				return 1;
			}
			SetPixelFormat(hdc, pixelFormat, &pfd);
			mContext = wglCreateContext(hdc);
			wglMakeCurrent(hdc, mContext);
			
			GLint error = glewInit();

			if (error) {
				return 1;
			}

			HGLRC check = wglGetCurrentContext();

			if (wglGetCurrentContext() == NULL) {
				return 1;
			}


			GLint contextAttribs[] =
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, GetVersionMajor(),
				WGL_CONTEXT_MINOR_VERSION_ARB, GetVersionMinor(),
				// Uncomment this for forward compatibility mode
				//WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
				// Uncomment this for Compatibility profile
				//WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
				// We are using Core profile here
				WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
				0
			};

			HGLRC advContext = wglCreateContextAttribsARB(hdc, NULL, contextAttribs);

			wglDeleteContext(mContext);

			mContext = advContext;

			wglMakeCurrent(hdc, mContext);

			GLint major;
			char* version = (char*)glGetString(GL_VERSION);
			
			return 0;
		}

		PIXELFORMATDESCRIPTOR GLContextAdapter::GetPixelDescriptor() const {
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

			return pfd;
		}
	}
}