#include "airpch.h"
#include "WindowsWindow.hpp"

#include <glad\wgl.h>
#include <glad\gl.h>

#include "GLContextAdapter.hpp"

namespace platform {
	namespace windows {

		GLContextAdapter::GLContextAdapter(WindowsWindow* window, uint16 major, uint16 minor) : m_Window(window), m_MajorVersion(major), m_MinorVersion(minor) {
		}

		//TODO replace current glad with glad that has wgl extensions
		GLContextAdapter::~GLContextAdapter() {
			AIR_CORE_INFO("Destroying OpenGL context");
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(mContext);
		}

		bool GLContextAdapter::Initialize() {
			AIR_CORE_INFO("Initializing OpenGL context adapter");
			HDC hdc = m_Window->GetHDC();

			if (hdc == nullptr) {
				AIR_CORE_ERROR("Window HDC not found! Did you initialize your window?");
				return true;
			}

			PIXELFORMATDESCRIPTOR pfd = GetPixelDescriptor();

			int32 pixelFormat = ChoosePixelFormat(hdc, &pfd);
			if (pixelFormat == 0) {
				AIR_CORE_ERROR("Failed to find pixel format");
				return 1;
			}
			SetPixelFormat(hdc, pixelFormat, &pfd);
			mContext = wglCreateContext(hdc);
			wglMakeCurrent(hdc, mContext);

			if (!gladLoaderLoadWGL(hdc)) {
				AIR_CORE_ERROR("Failed to load wgl");
				return true;
			}

			HGLRC check = wglGetCurrentContext();

			if (wglGetCurrentContext() == NULL) {
				AIR_CORE_ERROR("Failed to create OpenGL context");
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
				AIR_CORE_ERROR("Failed to load OpenGL");
				return true;

			}
			const char* version = (char*)glGetString(GL_VERSION);

			wglSwapIntervalEXT(0);

			AIR_CORE_INFO("Succesfully created OpenGL context");
			AIR_CORE_INFO("OpenGL version: ", version);
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

			return pfd;
		}
	}
}