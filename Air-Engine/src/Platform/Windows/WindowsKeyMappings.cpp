#include "WindowsKeyMappings.hpp"

#include "../../Engine/IO/KeyCodes.hpp"
#include <windows.h>

namespace platform {
	namespace windows {

		WinKeyPair winKeyPairs[] = {
		{engine::io::KeyCode::KEY_0, 0x30},//'0' Key
		{engine::io::KeyCode::KEY_1, 0x31},//'1' Key
		{engine::io::KeyCode::KEY_2, 0x32},//'2' Key
		{engine::io::KeyCode::KEY_3, 0x32},//'3' Key
		{engine::io::KeyCode::KEY_4, 0x32},//'4' Key
		{engine::io::KeyCode::KEY_5, 0x32},//'5' Key
		{engine::io::KeyCode::KEY_6, 0x32},//'6' Key
		{engine::io::KeyCode::KEY_7, 0x32},//'7' Key
		{engine::io::KeyCode::KEY_8, 0x32},//'8' Key
		{engine::io::KeyCode::KEY_9, 0x32},//'9' Key

		{engine::io::KeyCode::KEY_A, 0x41},//'A' Key
		{engine::io::KeyCode::KEY_B, 0x42},//'B' Key
		{engine::io::KeyCode::KEY_C, 0x43},//'C' Key
		{engine::io::KeyCode::KEY_D, 0x44},//'D' Key
		{engine::io::KeyCode::KEY_E, 0x45},//'E' Key
		{engine::io::KeyCode::KEY_F, 0x46},//'F' Key
		{engine::io::KeyCode::KEY_G, 0x47},//'G' Key
		{engine::io::KeyCode::KEY_H, 0x48},//'H' Key
		{engine::io::KeyCode::KEY_I, 0x49},//'I' Key
		{engine::io::KeyCode::KEY_J, 0x4A},//'J' Key
		{engine::io::KeyCode::KEY_K, 0x4B},//'K' Key
		{engine::io::KeyCode::KEY_L, 0x4C},//'L' Key
		{engine::io::KeyCode::KEY_M, 0x4D},//'M' Key
		{engine::io::KeyCode::KEY_N, 0x4E},//'N' Key
		{engine::io::KeyCode::KEY_O, 0x4F},//'O' Key
		{engine::io::KeyCode::KEY_P, 0x50},//'P' Key
		{engine::io::KeyCode::KEY_Q, 0x51},//'Q' Key
		{engine::io::KeyCode::KEY_R, 0x52},//'R' Key
		{engine::io::KeyCode::KEY_S, 0x53},//'S' Key
		{engine::io::KeyCode::KEY_T, 0x54},//'T' Key
		{engine::io::KeyCode::KEY_U, 0x55},//'U' Key
		{engine::io::KeyCode::KEY_V, 0x56},//'V' Key
		{engine::io::KeyCode::KEY_W, 0x57},//'W' Key
		{engine::io::KeyCode::KEY_X, 0x58},//'X' Key
		{engine::io::KeyCode::KEY_Y, 0x59},//'Y' Key
		{engine::io::KeyCode::KEY_Z, 0x5A},//'Z' Key

		{engine::io::KeyCode::KEY_ESCAPE,VK_ESCAPE},
		{engine::io::KeyCode::KEY_TILDE,VK_OEM_3},//`~
		{engine::io::KeyCode::KEY_TAB,VK_TAB},
		{engine::io::KeyCode::KEY_CAPS_LOCK,VK_CAPITAL},
		{engine::io::KeyCode::KEY_PRINTSCR,VK_SNAPSHOT},
		{engine::io::KeyCode::KEY_INSERT,VK_INSERT},
		{engine::io::KeyCode::KEY_DELETE,VK_DELETE},
		{engine::io::KeyCode::KEY_SCRLCK,VK_SCROLL},
		{engine::io::KeyCode::KEY_HOME,VK_HOME},
		{engine::io::KeyCode::KEY_END,VK_END},
		{engine::io::KeyCode::KEY_PAUSE,VK_PAUSE},
		{engine::io::KeyCode::KEY_PAGEUP,VK_PRIOR},
		{engine::io::KeyCode::KEY_PAGEDOWN,VK_NEXT},
		{engine::io::KeyCode::KEY_UP,VK_UP},
		{engine::io::KeyCode::KEY_LEFT,VK_LEFT},
		{engine::io::KeyCode::KEY_RIGHT,VK_RIGHT},
		{engine::io::KeyCode::KEY_DOWN,VK_DOWN},

		{engine::io::KeyCode::KEY_F1,VK_F1},
		{engine::io::KeyCode::KEY_F2,VK_F2},
		{engine::io::KeyCode::KEY_F3,VK_F3},
		{engine::io::KeyCode::KEY_F4,VK_F4},
		{engine::io::KeyCode::KEY_F5,VK_F5},
		{engine::io::KeyCode::KEY_F6,VK_F6},
		{engine::io::KeyCode::KEY_F7,VK_F7},
		{engine::io::KeyCode::KEY_F8,VK_F8},
		{engine::io::KeyCode::KEY_F9,VK_F9},
		{engine::io::KeyCode::KEY_F10,VK_F10},
		{engine::io::KeyCode::KEY_F11,VK_F11},
		{engine::io::KeyCode::KEY_F12,VK_F12},
		{engine::io::KeyCode::KEY_F13,VK_F13},
		{engine::io::KeyCode::KEY_F14,VK_F14},
		{engine::io::KeyCode::KEY_F15,VK_F15},
		{engine::io::KeyCode::KEY_F16,VK_F16},

		{engine::io::KeyCode::KEY_KP_MULTIPLY,VK_MULTIPLY},
		{engine::io::KeyCode::KEY_KP_DIVIDE,VK_DIVIDE},
		{engine::io::KeyCode::KEY_KP_SUBTRACT,VK_SUBTRACT},
		{engine::io::KeyCode::KEY_KP_PERIOD,VK_OEM_PERIOD},
		{engine::io::KeyCode::KEY_KP_ADD,VK_ADD},
		{engine::io::KeyCode::KEY_KP_0,VK_NUMPAD0},
		{engine::io::KeyCode::KEY_KP_1,VK_NUMPAD1},
		{engine::io::KeyCode::KEY_KP_2,VK_NUMPAD2},
		{engine::io::KeyCode::KEY_KP_3,VK_NUMPAD3},
		{engine::io::KeyCode::KEY_KP_4,VK_NUMPAD4},
		{engine::io::KeyCode::KEY_KP_5,VK_NUMPAD5},
		{engine::io::KeyCode::KEY_KP_6,VK_NUMPAD6},
		{engine::io::KeyCode::KEY_KP_7,VK_NUMPAD7},
		{engine::io::KeyCode::KEY_KP_8,VK_NUMPAD8},
		{engine::io::KeyCode::KEY_KP_9,VK_NUMPAD9},

		{engine::io::KeyCode::KEY_LSHIFT,VK_LSHIFT},
		{engine::io::KeyCode::KEY_LCTRL,VK_LCONTROL},
		{engine::io::KeyCode::KEY_RSHIFT,VK_RSHIFT},
		{engine::io::KeyCode::KEY_RCTRL,VK_RCONTROL},
		{engine::io::KeyCode::KEY_ENTER,VK_RETURN},
		{engine::io::KeyCode::KEY_BACKSLASH,VK_OEM_102},

		{engine::io::KeyCode::KEY_UNKNOWN, 0x00}//Used for undefined keys
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