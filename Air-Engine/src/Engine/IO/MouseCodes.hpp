#pragma once

#ifdef AIR_PLATFORM_WINDOWS
#include "../../Platform/Windows/WindowsMouseCodes.hpp"
#else
#error Air Engine only supports windows at the moment
#endif

namespace engine {
	namespace io {

		enum class MouseCode : unsigned int {
			#ifdef AIR_PLATFORM_WINDOWS
			LEFT			= platform::windows::MouseCode::LEFT,
			MIDDLE			= platform::windows::MouseCode::MIDDLE,
			RIGHT			= platform::windows::MouseCode::RIGHT,

			XONE			= platform::windows::MouseCode::XONE,
			XTWO			= platform::windows::MouseCode::XTWO,

			NONE			= platform::windows::MouseCode::NONE
			#endif
		};

	}
}