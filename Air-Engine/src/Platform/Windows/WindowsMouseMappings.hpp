#pragma once

namespace platform {
	namespace windows {

		struct WinButtonPair {
			unsigned int m_SysCode;
			unsigned int m_BtnCode;
		};

		class WindowsButtonMap {
			WindowsButtonMap() {}

		public:
			static unsigned int GetSysCode(unsigned int btnCode);

			static unsigned int GetButtonMask(unsigned int button);
		};
	}
}