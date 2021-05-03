#include "airpch.h"
#include "WindowsMouseMappings.hpp"

#include "../../Engine/IO/MouseCodes.hpp"

namespace platform {
	namespace windows {

		static WinButtonPair winButtonPairs[] = {
			{engine::io::BUTTON_LEFT, MK_LBUTTON},
			{engine::io::BUTTON_MIDDLE, MK_MBUTTON},
			{engine::io::BUTTON_RIGHT, MK_RBUTTON},
			{engine::io::BUTTON_XONE, MK_XBUTTON1},
			{engine::io::BUTTON_XTWO, MK_XBUTTON2},

			{engine::io::BUTTON_UNKNOWN, 0x00}
		};

		unsigned int WindowsButtonMap::GetSysCode(unsigned int button) {
			for (int i = 0; winButtonPairs[i].m_BtnCode != engine::io::BUTTON_UNKNOWN; i++) {
				if (winButtonPairs[i].m_BtnCode == button)
					return winButtonPairs[i].m_SysCode;
			}
			return engine::io::BUTTON_UNKNOWN;
		}

		unsigned int platform::windows::WindowsButtonMap::GetButtonCode(unsigned int sysCode) {
			for (int i = 0; winButtonPairs[i].m_BtnCode != engine::io::BUTTON_UNKNOWN; i++) {
				if (winButtonPairs[i].m_SysCode == sysCode)
					return winButtonPairs[i].m_BtnCode;
			}
			return engine::io::BUTTON_UNKNOWN;
		}

		unsigned int WindowsButtonMap::GetButtonMask(unsigned int button) {
			return 1 << button;
		}

	}
}