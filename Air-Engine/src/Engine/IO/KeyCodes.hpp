#pragma once

namespace engine {
	namespace io {

		//Add prefix to keys
		enum KeyCode {
			//Non-numpad numbers
			ZERO			= 0x01,
			ONE				= 0x02,
			TWO				= 0x03,
			THREE			= 0x04,
			FOUR			= 0x05,
			FIVE			= 0x06,
			SIX				= 0x07,
			SEVEN			= 0x08,
			EIGHT			= 0x09,
			NINE			= 0x0A,

			//Characters
			A				= 0x0B,
			B				= 0x0C,
			C				= 0x0D,
			D				= 0x0E,
			E				= 0x0F,
			F				= 0x10,
			G				= 0x11,
			H				= 0x12,
			I				= 0x13,
			J				= 0x14,
			K				= 0x15,
			L				= 0x16,
			M				= 0x17,
			N				= 0x18,
			O				= 0x19,
			P				= 0x1A,
			Q				= 0x1B,
			R				= 0x1C,
			S				= 0x1D,
			T				= 0x1E,
			U				= 0x1F,
			V				= 0x20,
			W				= 0x21,
			X				= 0x22,
			Y				= 0x23,
			Z				= 0x24,

			CAPS_LOCK		= 0x25,

			UNKNOWN			= 0x00
		};
	}
}