#pragma once

namespace platform {
	namespace windows {

		struct WinKeyPair {
			unsigned int m_SysCode;
			unsigned int m_KeyCode;
		};

		class WindowsKeyMap {
			WindowsKeyMap() {}

		public:
			//This returns the Air Engine version of the key
			static unsigned int GetSysCode(unsigned int keyCode);

			static unsigned int GetKeyCode(unsigned int sysCode);
		};
	}
}