#include "WindowsKeyMappings.hpp"

#include "../../Engine/IO/KeyCodes.hpp"
#include <windows.h>

namespace platform {
	namespace windows {

		WinKeyPair winKeyPairs[] = {
			{engine::io::KeyCode::ZERO, 0x30},		//'0' Key
			{engine::io::KeyCode::ONE, 0x31},		//'1' Key
			{engine::io::KeyCode::TWO, 0x32},		//'2' Key
			{engine::io::KeyCode::THREE, 0x32},		//'3' Key
			{engine::io::KeyCode::FOUR, 0x32},		//'4' Key
			{engine::io::KeyCode::FIVE, 0x32},		//'5' Key
			{engine::io::KeyCode::SIX, 0x32},		//'6' Key
			{engine::io::KeyCode::SEVEN, 0x32},		//'7' Key
			{engine::io::KeyCode::EIGHT, 0x32},		//'8' Key
			{engine::io::KeyCode::NINE, 0x32},		//'9' Key

			{engine::io::KeyCode::A, 0x41},			//'A' Key
			{engine::io::KeyCode::B, 0x42},			//'B' Key
			{engine::io::KeyCode::C, 0x43},			//'C' Key
			{engine::io::KeyCode::D, 0x44},			//'D' Key
			{engine::io::KeyCode::E, 0x45},			//'E' Key
			{engine::io::KeyCode::F, 0x46},			//'F' Key
			{engine::io::KeyCode::G, 0x47},			//'G' Key
			{engine::io::KeyCode::H, 0x48},			//'H' Key
			{engine::io::KeyCode::I, 0x49},			//'I' Key
			{engine::io::KeyCode::J, 0x4A},			//'J' Key
			{engine::io::KeyCode::K, 0x4B},			//'K' Key
			{engine::io::KeyCode::L, 0x4C},			//'L' Key
			{engine::io::KeyCode::M, 0x4D},			//'M' Key
			{engine::io::KeyCode::N, 0x4E},			//'N' Key
			{engine::io::KeyCode::O, 0x4F},			//'O' Key
			{engine::io::KeyCode::P, 0x50},			//'P' Key
			{engine::io::KeyCode::Q, 0x51},			//'Q' Key
			{engine::io::KeyCode::R, 0x52},			//'R' Key
			{engine::io::KeyCode::S, 0x53},			//'S' Key
			{engine::io::KeyCode::T, 0x54},			//'T' Key
			{engine::io::KeyCode::U, 0x55},			//'U' Key
			{engine::io::KeyCode::V, 0x56},			//'V' Key
			{engine::io::KeyCode::W, 0x57},			//'W' Key
			{engine::io::KeyCode::X, 0x58},			//'X' Key
			{engine::io::KeyCode::Y, 0x59},			//'Y' Key
			{engine::io::KeyCode::Z, 0x5A},			//'Z' Key

			{engine::io::KeyCode::UNKNOWN, 0x00}	//Used for undefined keys
		};

		unsigned int WindowsKeyMap::GetKeyCode(unsigned int keyCode) {
			for (unsigned int i = 0; winKeyPairs[i].m_SysCode != engine::io::UNKNOWN; i++) {
				if (winKeyPairs[i].m_SysCode == keyCode)
					return winKeyPairs[i].m_SysCode;
			}
			return engine::io::KeyCode::UNKNOWN;
		}
	}
}