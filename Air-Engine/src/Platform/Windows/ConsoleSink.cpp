#include "airpch.h"
#include "ConsoleSink.h"

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

		ConsoleSink::ConsoleSink() : ConsoleSink(defaultColorPair) {

		}

		ConsoleSink::ConsoleSink(PriorityColorPair* colors) : Sink("WinConsole"), m_Colors(colors), m_ConsoleHandle(GetStdHandle(STD_OUTPUT_HANDLE)) {

		}


		ConsoleSink::~ConsoleSink() {
			
		}

		bool ConsoleSink::Print(unsigned char severity, const char* str) {
			SetColor(GetColor(severity));
			std::cout << str;
			ResetColor();
			return false;
		}

		void ConsoleSink::ResetColor() {
			SetColor(COLOR_GREY);
		}

		void ConsoleSink::SetColor(unsigned char color) {
			SetConsoleTextAttribute(m_ConsoleHandle, color);
		}

		unsigned char ConsoleSink::GetColor(unsigned char priority) {
			for (int32 i = 0; m_Colors[i].m_Priority != engine::util::SE_UNKNOWN; i++) {
				if (m_Colors[i].m_Priority == priority)
					return m_Colors[i].m_Color;
			}
			return COLOR_WHITE;
		}
	}
}