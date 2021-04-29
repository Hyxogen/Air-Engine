#pragma once

namespace platform {
	namespace windows {

		struct WinKeyPair {
			//Code used by the Air Engine
			unsigned int m_SysCode;
			//Code used by the platform
			unsigned int m_KeyCode;
		};

		class WindowsKeyMap {
			WindowsKeyMap() {}

		public:
			//Returns code that Air Engine uses that corresponds to the passed platform keycode
			static unsigned int GetSysCode(unsigned int keyCode);

			//Returns keycode that the platform uses that corresponds to the passed Air Engine code
			static unsigned int GetKeyCode(unsigned int sysCode);
		};
	}
}