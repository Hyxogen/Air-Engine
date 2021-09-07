#pragma once

namespace platform {
	namespace windows {

		struct WinKeyPair {
			//Code used by the Air Engine
			uint32 m_SysCode;
			//Code used by the platform
			uint32 m_KeyCode;
		};

		class WindowsKeyMap {
			WindowsKeyMap() {}

		public:
			//Returns code that Air Engine uses that corresponds to the passed platform keycode
			static uint32 GetSysCode(uint32 keyCode);

			//Returns keycode that the platform uses that corresponds to the passed Air Engine code
			static uint32 GetKeyCode(uint32 sysCode);
		};
	}
}