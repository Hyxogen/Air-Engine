#include "WindowsKeyMappings.hpp"

#include "../../Engine/IO/KeyCodes.hpp"
#include <windows.h>

namespace platform {
	namespace windows {

		WinKeyPair winKeyPairs[] = {
			{engine::io::KeyCode::KEY_ZERO, 0x30},		//'0' Key
			{engine::io::KeyCode::KEY_ONE, 0x31},		//'1' Key
			{engine::io::KeyCode::KEY_TWO, 0x32},		//'2' Key
			{engine::io::KeyCode::KEY_THREE, 0x32},		//'3' Key
			{engine::io::KeyCode::KEY_FOUR, 0x32},		//'4' Key
			{engine::io::KeyCode::KEY_FIVE, 0x32},		//'5' Key
			{engine::io::KeyCode::KEY_SIX, 0x32},		//'6' Key
			{engine::io::KeyCode::KEY_SEVEN, 0x32},		//'7' Key
			{engine::io::KeyCode::KEY_EIGHT, 0x32},		//'8' Key
			{engine::io::KeyCode::KEY_NINE, 0x32},		//'9' Key

			{engine::io::KeyCode::KEY_A, 0x41},			//'A' Key
			{engine::io::KeyCode::KEY_B, 0x42},			//'B' Key
			{engine::io::KeyCode::KEY_C, 0x43},			//'C' Key
			{engine::io::KeyCode::KEY_D, 0x44},			//'D' Key
			{engine::io::KeyCode::KEY_E, 0x45},			//'E' Key
			{engine::io::KeyCode::KEY_F, 0x46},			//'F' Key
			{engine::io::KeyCode::KEY_G, 0x47},			//'G' Key
			{engine::io::KeyCode::KEY_H, 0x48},			//'H' Key
			{engine::io::KeyCode::KEY_I, 0x49},			//'I' Key
			{engine::io::KeyCode::KEY_J, 0x4A},			//'J' Key
			{engine::io::KeyCode::KEY_K, 0x4B},			//'K' Key
			{engine::io::KeyCode::KEY_L, 0x4C},			//'L' Key
			{engine::io::KeyCode::KEY_M, 0x4D},			//'M' Key
			{engine::io::KeyCode::KEY_N, 0x4E},			//'N' Key
			{engine::io::KeyCode::KEY_O, 0x4F},			//'O' Key
			{engine::io::KeyCode::KEY_P, 0x50},			//'P' Key
			{engine::io::KeyCode::KEY_Q, 0x51},			//'Q' Key
			{engine::io::KeyCode::KEY_R, 0x52},			//'R' Key
			{engine::io::KeyCode::KEY_S, 0x53},			//'S' Key
			{engine::io::KeyCode::KEY_T, 0x54},			//'T' Key
			{engine::io::KeyCode::KEY_U, 0x55},			//'U' Key
			{engine::io::KeyCode::KEY_V, 0x56},			//'V' Key
			{engine::io::KeyCode::KEY_W, 0x57},			//'W' Key
			{engine::io::KeyCode::KEY_X, 0x58},			//'X' Key
			{engine::io::KeyCode::KEY_Y, 0x59},			//'Y' Key
			{engine::io::KeyCode::KEY_Z, 0x5A},			//'Z' Key

			{engine::io::KeyCode::KEY_UNKNOWN, 0x00}	//Used for undefined keys
		};

		unsigned int WindowsKeyMap::GetKeyCode(unsigned int keyCode) {
			for (unsigned int i = 0; winKeyPairs[i].m_SysCode != engine::io::KEY_UNKNOWN; i++) {
				if (winKeyPairs[i].m_KeyCode == keyCode)
					return winKeyPairs[i].m_SysCode;
			}
			return engine::io::KeyCode::KEY_UNKNOWN;
		}
	}
}