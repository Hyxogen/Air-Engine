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
			static unsigned int GetKeyCode(unsigned int keyCode);
		};
	}
}