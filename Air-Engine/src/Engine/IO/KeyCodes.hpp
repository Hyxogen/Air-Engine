#pragma once

namespace engine {
	namespace io {

		//Add prefix to keys
		enum KeyCode {
			//Non-numpad numbers
			KEY_0				= 0x01,
			KEY_1				= 0x02,
			KEY_2				= 0x03,
			KEY_3				= 0x04,
			KEY_4				= 0x05,
			KEY_5				= 0x06,
			KEY_6				= 0x07,
			KEY_7				= 0x08,
			KEY_8				= 0x09,
			KEY_9				= 0x0A,

			//Characters
			KEY_A				= 0x0B,
			KEY_B				= 0x0C,
			KEY_C				= 0x0D,
			KEY_D				= 0x0E,
			KEY_E				= 0x0F,
			KEY_F				= 0x10,
			KEY_G				= 0x11,
			KEY_H				= 0x12,
			KEY_I				= 0x13,
			KEY_J				= 0x14,
			KEY_K				= 0x15,
			KEY_L				= 0x16,
			KEY_M				= 0x17,
			KEY_N				= 0x18,
			KEY_O				= 0x19,
			KEY_P				= 0x1A,
			KEY_Q				= 0x1B,
			KEY_R				= 0x1C,
			KEY_S				= 0x1D,
			KEY_T				= 0x1E,
			KEY_U				= 0x1F,
			KEY_V				= 0x20,
			KEY_W				= 0x21,
			KEY_X				= 0x22,
			KEY_Y				= 0x23,
			KEY_Z				= 0x24,

			KEY_CAPS_LOCK		= 0x25,

			KEY_UNKNOWN			= 0x00
		};
	}
}