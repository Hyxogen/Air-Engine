#include "WindowsWindow.hpp"
#include <glad\wgl.h>
#include <glad\gl.h>
#include "GLContextAdapter.hpp"
#include "../../Engine/Util/Logger/Logger.hpp"

namespace platform {
	namespace windows {

		GLContextAdapter::GLContextAdapter(WindowsWindow* window, unsigned short major, unsigned short minor) : mWindow(window), mMajorVersion(major), mMinorVersion(minor) {
		}

		//TODO replace current glad with glad that has wgl extensions
		GLContextAdapter::~GLContextAdapter() {
			AIR_CORE_LOG_INFO("Destroying OpenGL context");
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(mContext);
		}

		bool GLContextAdapter::Initialize() {
			AIR_CORE_LOG_INFO("Initializing OpenGL context adapter");
			HDC hdc = GetDC(mWindow->getWindowHandle());

			PIXELFORMATDESCRIPTOR pfd = GetPixelDescriptor();

			int pixelFormat = ChoosePixelFormat(hdc, &pfd);
			if (pixelFormat == 0) {
				AIR_CORE_LOG_ERROR("Failed to find pixel format");
				return 1;
			}
			SetPixelFormat(hdc, pixelFormat, &pfd);
			mContext = wglCreateContext(hdc);
			wglMakeCurrent(hdc, mContext);
			
			if (!gladLoaderLoadWGL(hdc)) {
				AIR_CORE_LOG_ERROR("Failed to load wgl");
				return true;
			}

			HGLRC check = wglGetCurrentContext();

			if (wglGetCurrentContext() == NULL) {
				AIR_CORE_LOG_ERROR("Failed to create OpenGL context");
				return true;
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

			if (!gladLoaderLoadGL()) {
				AIR_CORE_LOG_ERROR("Failed to load OpenGL");
				return true;

			}
			const char* version = (char*)glGetString(GL_VERSION);
			
			wglSwapIntervalEXT(0);

			AIR_CORE_LOG_INFO("Succesfully created OpenGL context");
			AIR_CORE_LOG_INFO(version);
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