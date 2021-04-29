#pragma once

namespace platform {
	namespace windows {

		struct WinButtonPair {
			//Code used by the Air Engine
			unsigned int m_SysCode;
			//Code used by the platform
			unsigned int m_BtnCode;
		};

		class WindowsButtonMap {
			WindowsButtonMap() {}

		public:
			//Returns code that Air Engine uses that corresponds to the passed platform code
			static unsigned int GetSysCode(unsigned int btnCode);

			//Returns code that the platform uses that corresponds to the passed Air Engine code
			static unsigned int GetButtonCode(unsigned int sysCode);

			static unsigned int GetButtonMask(unsigned int button);
		};
	}
}