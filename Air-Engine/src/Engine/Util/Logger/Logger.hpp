#pragma once
#include "Severity.hpp"

/*
Wat wil ik bereiken?

Ik wil gewoon simpelweg in de code iets zoals dit doen:
AIR_CORE_WARN("Variable was not initialzed!")
Zodat in de console dit komt te staan:
"[CORE][WARN] Variable was not initialzed!"

En ervoor kunnen zorgen dat ik verbosity levels eruit kan filteren en relatief makkelijk nieuwe kan toevoegen
*/

namespace engine {
	namespace util {

		class Logger {
			unsigned int m_Verbosity = 9999;
			const char* m_Prefix;

			static Logger* CORE_LOGGER;

		public:
			Logger(const char* prefix = "");

			void Log(Severity severity, const char* data) const;

			void SetVerbosity(unsigned int verbosity);

			inline unsigned int GetVerbosity() const { return m_Verbosity; }

			static Logger* GetCoreLogger();
		};

	}
}

#define AIR_CORE_LOG_TRACE(x) engine::util::Logger::GetCoreLogger()->Log(AIR_LOG_TRACE, x)
#define AIR_CORE_LOG_INFO(x) engine::util::Logger::GetCoreLogger()->Log(AIR_LOG_INFO, x)
#define AIR_CORE_LOG_WARN(x) engine::util::Logger::GetCoreLogger()->Log(AIR_LOG_WARN, x)
#define AIR_CORE_LOG_ERROR(x) engine::util::Logger::GetCoreLogger()->Log(AIR_LOG_ERROR, x)
#define AIR_CORE_LOG_CRITICAL(x) engine::util::Logger::GetCoreLogger()->Log(AIR_LOG_CRITICAL, x)
#define AIR_CORE_VERBOSITY(x) engine::util::Logger::GetCoreLogger()->SetVerbosity(x.m_Level)

#define AIR_CORE_ERR_IF(s, x) if(s) {AIR_CORE_LOG_ERROR(x);}
/*
#define AIR_CORE_TRACE(...) engine::util::Logger::GetCoreLogger().Log(AIR_TRACE, 0, __VA_ARGS__);
#define AIR_CORE_INFO(...) engine::util::Logger::GetCoreLogger().Log(AIR_INFO, 0, __VA_ARGS__);
#define AIR_CORE_WARN(...) engine::util::Logger::GetCoreLogger().Log(AIR_WARN, 0, __VA_ARGS__);
#define AIR_CORE_ERROR(...) engine::util::Logger::GetCoreLogger().Log(AIR_ERROR, 0, __VA_ARGS__);
#define AIR_CORE_CRITICAL(...) engine::util::Logger::GetCoreLogger().Log(AIR_CRITICAL, 0, __VA_ARGS__);
*/