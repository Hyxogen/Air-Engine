#include "ConsoleSink.h"

#include <iostream>

namespace platform {
	namespace windows {
	
		ConsoleSink::ConsoleSink() : Sink("WinConsole"), m_ConsoleHandle(GetStdHandle(STD_OUTPUT_HANDLE)){
			
		}

		ConsoleSink::~ConsoleSink() {
			
		}

		bool ConsoleSink::Print(unsigned char severity, const char* str) {
			SetColor(FOREGROUND_RED | FOREGROUND_GREEN);
			std::cout << str;
			return false;
		}

		void ConsoleSink::SetColor(unsigned char color) {
			SetConsoleTextAttribute(m_ConsoleHandle, color);
		}
	}
}