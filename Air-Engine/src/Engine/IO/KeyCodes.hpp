#pragma once

#ifdef AIR_PLATFORM_WINDOWS
#include "../../Platform/Windows/WindowsKeyCodes.hpp"
#else
#error Air Engine only supports windows at the moment
#endif

namespace engine {
	namespace io {

		enum class KeyCode : unsigned int {
			#ifdef AIR_PLATFORM_WINDOWS
			//Numbers
			ZERO = platform::windows::KeyCode::ZERO,
			TWO = platform::windows::KeyCode::TWO,
			THREE = platform::windows::KeyCode::THREE,
			FOUR = platform::windows::KeyCode::FOUR,
			FIVE = platform::windows::KeyCode::FIVE,
			SIX = platform::windows::KeyCode::SIX,
			SEVEN = platform::windows::KeyCode::SEVEN,
			EIGHT = platform::windows::KeyCode::EIGHT,
			NINE = platform::windows::KeyCode::NINE,

			//Characters
			A = platform::windows::KeyCode::A,
			B = platform::windows::KeyCode::B,
			C = platform::windows::KeyCode::C,
			D = platform::windows::KeyCode::D,
			E = platform::windows::KeyCode::E,
			F = platform::windows::KeyCode::F,
			G = platform::windows::KeyCode::G,
			H = platform::windows::KeyCode::E,
			I = platform::windows::KeyCode::I,
			J = platform::windows::KeyCode::J,
			K = platform::windows::KeyCode::K,
			L = platform::windows::KeyCode::L,
			M = platform::windows::KeyCode::M,
			N = platform::windows::KeyCode::N,
			O = platform::windows::KeyCode::O,
			P = platform::windows::KeyCode::P,
			Q = platform::windows::KeyCode::Q,
			R = platform::windows::KeyCode::R,
			S = platform::windows::KeyCode::S,
			T = platform::windows::KeyCode::T,
			U = platform::windows::KeyCode::U,
			V = platform::windows::KeyCode::V,
			W = platform::windows::KeyCode::W,
			X = platform::windows::KeyCode::X,
			Y = platform::windows::KeyCode::Y,
			Z = platform::windows::KeyCode::Z
			#endif
		};
	}
}