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
			std::ostringstream m_Output;

			SinkList m_Sinks;

			static Logger* s_CoreLogger;
		public:
			Logger(const char* name);

			~Logger();

			template<typename... Ts>
			void Log(unsigned char severity, Ts... ts) {
				Log(severity, true, ts...);
			}

			template<typename... Ts>
			void Log(unsigned char severity, bool newLine, Ts... ts) {
				LogInternal(severity, newLine, ts...);
				Flush(severity);
			}

			bool AddSink(Sink* sink);

			static Logger* GetCoreLogger();

		protected:
			void ClearBuffer();

			template<typename First>
			void LogInternal(First&& first) {
				m_Output << first;
			}

			template<typename First, typename... Args>
			void LogInternal(First&& first, Args&&... args) {
				LogInternal(first);
				if (sizeof...(Args))
					LogInternal(args...);
			}

			template<typename... Args>
			void LogInternal(unsigned char severity, bool newLine, Args... args) {
				m_Output << "[" << m_Name << "]" << GetSeverityString(severity) << " ";

				LogInternal(std::forward<Args>(args)...);

				if (newLine)
					m_Output << "\n";
			}

			void Flush(unsigned char severity);

		public:
			static const char* GetSeverityString(unsigned char severity);
		};

	}
}

#define AIR_CORE_LOG_TRACE(...)		engine::util::Logger::GetCoreLogger()->Log(engine::util::SE_TRACE, __VA_ARGS__);
#define AIR_CORE_LOG_INFO(...)		engine::util::Logger::GetCoreLogger()->Log(engine::util::SE_INFO, __VA_ARGS__);
#define AIR_CORE_LOG_WARN(...)		engine::util::Logger::GetCoreLogger()->Log(engine::util::SE_WARN, __VA_ARGS__);
#define AIR_CORE_LOG_ERROR(...)		engine::util::Logger::GetCoreLogger()->Log(engine::util::SE_ERROR, __VA_ARGS__);
#define AIR_CORE_LOG_CRITICAL(...)	engine::util::Logger::GetCoreLogger()->Log(engine::util::SE_CRITICAL, __VA_ARGS__);
#define AIR_CORE_VERBOSITY(x)

#define AIR_CORE_ERR_IF(s, x)