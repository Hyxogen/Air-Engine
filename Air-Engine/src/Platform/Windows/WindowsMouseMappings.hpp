#pragma once

namespace platform {
	namespace windows {

		struct WinButtonPair {
			//Code used by the Air Engine
			uint32 m_SysCode;
			//Code used by the platform
			uint32 m_BtnCode;
		};

		class WindowsButtonMap {
			WindowsButtonMap() {}

		public:
			//Returns code that Air Engine uses that corresponds to the passed platform code
			static uint32 GetSysCode(uint32 btnCode);

			//Returns code that the platform uses that corresponds to the passed Air Engine code
			static uint32 GetButtonCode(uint32 sysCode);

			static uint32 GetButtonMask(uint32 button);
		};
	}
}