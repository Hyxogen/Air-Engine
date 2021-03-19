#include "Logger.hpp"
#include <cstdio>

namespace engine {
	namespace util {

		Logger* Logger::CORE_LOGGER = nullptr;

		Logger::Logger(const char* prefix) : mPrefix(prefix) {

		}

		void Logger::Log(unsigned int verbosity, unsigned int channel, const char* data...) const {
			printf("[%s] [%i]	%s\n", mPrefix, verbosity, data);
		}

		const Logger* Logger::GetCoreLogger() {
			if (CORE_LOGGER == nullptr) {
				CORE_LOGGER = new Logger("CORE");
			}

			return CORE_LOGGER;
		}
	}
}