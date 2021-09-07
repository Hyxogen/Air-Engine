#include "airpch.h"
#pragma once

namespace platform {
	namespace windows {

		class WindowsWindow;

		class GLContextAdapter {
			const uint16 m_MajorVersion, m_MinorVersion;
			WindowsWindow* m_Window = nullptr;
			HGLRC mContext = 0;

		public:
			GLContextAdapter(WindowsWindow* window, uint16 major = 3, uint16 minor = 3);

			~GLContextAdapter();

			//Returns false for no errors
			bool Initialize();

		protected:
			//Ik denk dat deze functie toch ergens anders heen moet sinds deze class niet veranderd moet worden mocht ik een andere pixel descriptor willen
			PIXELFORMATDESCRIPTOR GetPixelDescriptor() const;

			inline uint16 GetVersionMajor() const { return m_MajorVersion; }

			inline uint16 GetVersionMinor() const { return m_MinorVersion; }
		};

	}
}