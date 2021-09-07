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

		uint32 WindowsButtonMap::GetSysCode(uint32 button) {
			for (int32 i = 0; winButtonPairs[i].m_BtnCode != engine::io::BUTTON_UNKNOWN; i++) {
				if (winButtonPairs[i].m_BtnCode == button)
					return winButtonPairs[i].m_SysCode;
			}
			return engine::io::BUTTON_UNKNOWN;
		}

		uint32 platform::windows::WindowsButtonMap::GetButtonCode(uint32 sysCode) {
			for (int32 i = 0; winButtonPairs[i].m_BtnCode != engine::io::BUTTON_UNKNOWN; i++) {
				if (winButtonPairs[i].m_SysCode == sysCode)
					return winButtonPairs[i].m_BtnCode;
			}
			return engine::io::BUTTON_UNKNOWN;
		}

		uint32 WindowsButtonMap::GetButtonMask(uint32 button) {
			return 1 << button;
		}

	}
}