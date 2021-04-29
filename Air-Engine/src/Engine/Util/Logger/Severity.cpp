#include "Severity.hpp"

namespace engine {
	namespace util {

		const Severity Severity::SV_TRACE = Severity("TRACE", 4);
		const Severity Severity::SV_INFO = Severity("INFO", 3);
		const Severity Severity::SV_WARN = Severity("WARN", 2);
		const Severity Severity::SV_ERROR = Severity("ERROR", 1);
		const Severity Severity::SV_CRITICAL = Severity("CRITICAL", 0);

		Severity::Severity(const char* name, unsigned int level) : m_Name(name), m_Level(level) {

		}

	}
}