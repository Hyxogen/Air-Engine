#include "airpch.h"
#pragma once

#include "Sink.hpp"

namespace engine {
	namespace util {

		typedef std::unordered_set<Sink*> SinkList;

		enum Severity : uint8 {
			SE_TRACE = 1,
			SE_INFO = 2,
			SE_WARN = 3,
			SE_ERROR = 4,
			SE_CRITICAL = 5,

			SE_UNKNOWN = 0
		};

		class Logger {
		protected:
			const char* m_Name;
			uint8 m_Verbosity;
			std::ostringstream m_Output;

			SinkList m_Sinks;

			static Logger* s_CoreLogger;
		public:
			Logger(const char* name);

			~Logger();

			template<typename... Ts>
			void Log(uint8 severity, Ts&... ts) {
				Log(severity, true, ts...);
			}

			template<typename... Ts>
			void Log(uint8 severity, bool newLine, Ts&... ts) {
				Log(severity, newLine, std::move(ts)...);
			}

			template<typename... Ts>
			void Log(uint8 severity, Ts&&... ts) {
				Log(severity, true, ts...);
			}

			template<typename... Ts>
			void Log(uint8 severity, bool newLine, Ts&&... ts) {
				if (!ShouldPrint(severity)) return;
				LogInternal(severity, newLine, ts...);
				Flush(severity);
			}

			bool AddSink(Sink* sink);

			void SetVerbosity(uint8 verbosity);

			uint8 GetVerbosity() const { return m_Verbosity; }
		protected:
			void ClearBuffer();

			void Destroy();

			void InsertTimeString();

			bool ShouldPrint(uint8 severity);

			void Flush(uint8 severity);

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

			//It is posible that naming this function the same as the other internal functions will cause weird behaviour
			template<typename... Args>
			void LogInternal(uint8 severity, bool newLine, Args&&... args) {
				InsertTimeString();
				m_Output << "[" << m_Name << "]" << GetSeverityString(severity) << " ";

				LogInternal(std::forward<Args>(args)...);

				if (newLine)
					m_Output << "\n";
			}
		public:
			static Logger* GetCoreLogger();

			static const char* GetSeverityString(uint8 severity);
		};

	}
}

#ifdef AIR_ENABLE_LOGGING
#define AIR_CORE_TRACE(...)		engine::util::Logger::GetCoreLogger()->Log(engine::util::SE_TRACE, __VA_ARGS__);
#define AIR_CORE_INFO(...)		engine::util::Logger::GetCoreLogger()->Log(engine::util::SE_INFO, __VA_ARGS__);
#define AIR_CORE_WARN(...)		engine::util::Logger::GetCoreLogger()->Log(engine::util::SE_WARN, __VA_ARGS__);
#define AIR_CORE_ERROR(...)		engine::util::Logger::GetCoreLogger()->Log(engine::util::SE_ERROR, __VA_ARGS__);
#define AIR_CORE_CRITICAL(...)	engine::util::Logger::GetCoreLogger()->Log(engine::util::SE_CRITICAL, __VA_ARGS__);

#define AIR_CORE_TRACE_IF(s, ...) if(s) { AIR_CORE_TRACE(__VA_ARGS__)} else {}
#define AIR_CORE_INFO_IF(s, ...) if(s) { AIR_CORE_INFO(__VA_ARGS__)} else {}
#define AIR_CORE_WARN_IF(s, ...) if(s) { AIR_CORE_WARN(__VA_ARGS__)} else {}
#define AIR_CORE_ERROR_IF(s, ...) if(s) { AIR_CORE_ERROR(__VA_ARGS__)} else {}
#define AIR_CORE_CRITICAL_IF(s, ...) if(s) { AIR_CORE_CRITICAL(__VA_ARGS__)} else {}
#else
#define AIR_CORE_TRACE(...)
#define AIR_CORE_INFO(...)
#define AIR_CORE_WARN(...)
#define AIR_CORE_ERROR(...)
#define AIR_CORE_CRITICAL(...)

#define AIR_CORE_TRACE_IF(s, ...) s
#define AIR_CORE_INFO_IF(s, ...) s
#define AIR_CORE_WARN_IF(s, ...) s
#define AIR_CORE_ERROR_IF(s, ...) s
#define AIR_CORE_CRITICAL_IF(s, ...) s
#endif