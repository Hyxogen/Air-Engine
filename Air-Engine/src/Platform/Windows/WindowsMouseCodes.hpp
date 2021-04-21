#pragma once

namespace platform {
	namespace windows {

		enum class MouseCode : unsigned int {
			LEFT				= 0x1,
			MIDDLE				= 0x2,
			RIGHT				= 0x3,

			XONE				= 0x4,
			XTWO				= 0x5,

			NONE				= 0x5
		};

	}
}