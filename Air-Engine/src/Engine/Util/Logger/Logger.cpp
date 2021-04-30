#include "Logger.hpp"

#include <iostream>

namespace engine {
	namespace util {
		
		Logger* Logger::s_CoreLogger = nullptr;

		Logger::Logger(const char* name) : m_Name(name) {
		
		}
		
		Logger::~Logger() {

		}

		Logger* Logger::GetCoreLogger() {
			if (s_CoreLogger == nullptr) {
				s_CoreLogger = new Logger("CORE");
			}

			return s_CoreLogger;
		}

		void Logger::ClearBuffer() {
			memset(m_Buffer, 0, sizeof(char*) * 1024);
		}
	}
}