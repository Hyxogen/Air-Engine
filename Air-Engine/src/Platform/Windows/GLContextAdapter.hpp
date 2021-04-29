#include <windows.h>

namespace platform {
	namespace windows {

		class WindowsWindow;

		class GLContextAdapter {
			const unsigned short m_MajorVersion, m_MinorVersion;
			WindowsWindow* m_Window = nullptr;
			HGLRC mContext = 0;

		public:
			GLContextAdapter(WindowsWindow* window, unsigned short major = 3, unsigned short minor = 3);

			~GLContextAdapter();

			//Returns false for no errors
			bool Initialize();

		protected:
			//Ik denk dat deze functie toch ergens anders heen moet sinds deze class niet veranderd moet worden mocht ik een andere pixel descriptor willen
			PIXELFORMATDESCRIPTOR GetPixelDescriptor() const;

			inline unsigned short GetVersionMajor() const { return m_MajorVersion; }

			inline unsigned short GetVersionMinor() const { return m_MinorVersion; }
		};

	}
}