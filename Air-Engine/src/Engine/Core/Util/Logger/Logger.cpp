#include "Logger.hpp"
#include <cstdio>

namespace engine {
	namespace util {

		Logger* Logger::CORE_LOGGER = nullptr;

		Logger::Logger(const char* prefix) : mPrefix(prefix) {

		}

		void Logger::Log(Severity severity, const char* data) const {
			if (severity.mLevel > mVerbosity) 
				return;
			printf("[%s] [%s]	%s\n", mPrefix, severity.mName, data);
		}

		Logger* Logger::GetCoreLogger() {
			if (CORE_LOGGER == nullptr) {
				CORE_LOGGER = new Logger("CORE");
			}

			return CORE_LOGGER;
		}

		void Logger::SetVerbosity(unsigned int level) {
			mVerbosity = level;
		}
	}
}

