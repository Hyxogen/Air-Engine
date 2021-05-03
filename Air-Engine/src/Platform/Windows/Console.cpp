#include "airpch.h"
#include "Console.hpp"

namespace platform {
	namespace windows {

		Console::Console(const wchar_t* title) : m_Title(title) {

		}

		Console::~Console() {

		}

		bool Console::Initialize() {
			if (AllocConsole() == 0)
				return true;
			SetConsoleTitle(m_Title);

			FILE* pCout;
			if (freopen_s(&pCout, "CONOUT$", "w", stdout) != 0)
				return true;

			FILE* pErr;
			if (freopen_s(&pErr, "CONOUT$", "w", stderr) != 0)
				return true;

			FILE* pIn;
			if (freopen_s(&pIn, "CONOUT$", "r", stdin) != 0)
				return true;

			std::wclog.clear();
			std::clog.clear();
			std::wcout.clear();
			std::cout.clear();
			std::wcerr.clear();
			std::cerr.clear();
			std::wcin.clear();
			std::cin.clear();
			return false;
		}

		bool Console::SetTitle(const wchar_t* title) {
			return SetConsoleTitle(title) == 0;
		}
	}
}