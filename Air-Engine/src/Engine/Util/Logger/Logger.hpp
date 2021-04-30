#pragma once

#include <unordered_set>
#include "Sink.hpp"

#include <iostream>
#include <sstream>

namespace engine {
	namespace util {

		typedef std::unordered_set<Sink*> SinkList;

		enum Severity : unsigned char {
			SE_TRACE = 0,
			SE_INFO = 1,
			SE_WARN = 2,
			SE_ERROR = 3,
			SE_CRITICAL = 4
		};

		class Logger {
		protected:
			const char* m_Name;
			unsigned char m_CurrentSev;
			std::ostringstream m_Output;

			SinkList m_Sinks;

			static Logger* s_CoreLogger;

		public:
			Logger(const char* name);

			~Logger();

			template<typename... Ts>
			void Log(unsigned char severity, Ts... ts) {
				m_CurrentSev = severity;
				LogInternal(true, ts...);
				Flush();
			}

			bool AddSink(Sink* sink);

			static Logger* GetCoreLogger();

		protected:
			void ClearBuffer();

			template<typename First>
			void LogInternalS(First&& first) {
				m_Output << first;
			}

			template<typename First, typename... Args>
			void LogInternalS(First&& first, Args&&... args) {
				LogInternalS(first);
				if (sizeof...(Args))
					LogInternalS(args...);
			}

			template<typename... Args>
			void LogInternal(bool newLine, Args... args) {
				ClearBuffer();

				m_Output << "[" << m_Name << "]" << GetSeverityString(m_CurrentSev);

				LogInternalS(std::forward<Args>(args)...);

				if (newLine)
					m_Output << "\n";
			}

			void Flush();

		public:
			static const char* GetSeverityString(unsigned char severity);
		};

	}
}

#define AIR_CORE_LOG_TRACE(x)
#define AIR_CORE_LOG_INFO(x) 
#define AIR_CORE_LOG_WARN(x)
#define AIR_CORE_LOG_ERROR(x)
#define AIR_CORE_LOG_CRITICAL(x)
#define AIR_CORE_VERBOSITY(x)

#define AIR_CORE_ERR_IF(s, x)