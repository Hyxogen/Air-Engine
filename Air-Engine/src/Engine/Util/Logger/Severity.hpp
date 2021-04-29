#pragma once

namespace engine {
	namespace util {

		struct Severity {

			static const Severity SV_TRACE;
			static const Severity SV_INFO;
			static const Severity SV_WARN;
			static const Severity SV_ERROR;
			static const Severity SV_CRITICAL;

			const char* const m_Name;
			const unsigned int m_Level;

			Severity(const char* name, unsigned int level);
		};

	}
}

#define AIR_LOG_TRACE engine::util::Severity::SV_TRACE
#define AIR_LOG_INFO engine::util::Severity::SV_INFO
#define AIR_LOG_WARN engine::util::Severity::SV_WARN
#define AIR_LOG_ERROR engine::util::Severity::SV_ERROR
#define AIR_LOG_CRITICAL engine::util::Severity::SV_CRITICAL