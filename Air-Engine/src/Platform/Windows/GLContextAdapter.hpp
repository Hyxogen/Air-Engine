#include <windows.h>

namespace platform {
	namespace windows {

		class WindowsWindow;

		class GLContextAdapter {
			const unsigned short mMajorVersion, mMinorVersion;
			WindowsWindow* mWindow = nullptr;
			HGLRC mContext = 0;

		public:
			GLContextAdapter(WindowsWindow* window, unsigned short major = 3, unsigned short minor = 3);

			~GLContextAdapter();

			//Returns 0 for no errors
			bool Initialize();

		protected:
			PIXELFORMATDESCRIPTOR GetPixelDescriptor() const;

			inline unsigned short GetVersionMajor() const { return mMajorVersion; }

			inline unsigned short GetVersionMinor() const { return mMinorVersion; }
		};

	}
}