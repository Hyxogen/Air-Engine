#include "Logger.hpp"
#include <cstdio>

namespace engine {
	namespace util {

		Logger* Logger::CORE_LOGGER = nullptr;

		Logger::Logger(const char* prefix) : m_Prefix(prefix) {

		}

		void Logger::Log(Severity severity, const char* data) const {
			if (severity.m_Level > m_Verbosity) 
				return;
			printf("[%s] [%s]	%s\n", m_Prefix, severity.m_Name, data);
		}

		Logger* Logger::GetCoreLogger() {
			if (CORE_LOGGER == nullptr) {
				CORE_LOGGER = new Logger("CORE");
			}

			return CORE_LOGGER;
		}

		void Logger::SetVerbosity(unsigned int level) {
			m_Verbosity = level;
		}
	}
}

