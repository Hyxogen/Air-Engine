#include "ConsoleSink.h"

#include "../../Engine/Util/Logger/Logger.hpp"

#include <iostream>

namespace platform {
	namespace windows {
	
		PriorityColorPair defaultColorPair[] = {
			{engine::util::SE_TRACE, COLOR_DARK_MAGENTA},
			{engine::util::SE_INFO, COLOR_GREEN},
			{engine::util::SE_WARN, COLOR_YELLOW},
			{engine::util::SE_ERROR, COLOR_RED},
			{engine::util::SE_CRITICAL, COLOR_RED | BACKGROUND_RED},
			{engine::util::SE_UNKNOWN, 0x00}
		};

		ConsoleSink::ConsoleSink() : Sink("WinConsole"), m_ConsoleHandle(GetStdHandle(STD_OUTPUT_HANDLE)){
			
		}

		ConsoleSink::~ConsoleSink() {
			
		}

		bool ConsoleSink::Print(unsigned char severity, const char* str) {
			SetColor(severity);
			std::cout << str;
			SetColor(COLOR_GREY);
			return false;
		}

		void ConsoleSink::SetColor(unsigned char color) {
			SetConsoleTextAttribute(m_ConsoleHandle, GetColor(color));
		}

		unsigned char ConsoleSink::GetColor(unsigned char priority) {
			for (int i = 0; defaultColorPair[i].m_Priority != engine::util::SE_UNKNOWN; i++) {
				if (defaultColorPair[i].m_Priority == priority)
					return defaultColorPair[i].m_Color;
			}
			return COLOR_WHITE;
		}
	}
}