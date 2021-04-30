#pragma once

#include <unordered_set>
#include "Sink.hpp"

#include <iostream>
#include <string>

namespace engine {
	namespace util {




		class Logger {
		protected:
			const char* m_Name;

			static Logger* s_CoreLogger;

		public:
			Logger(const char* name);

			~Logger();

			template<typename... Ts>
			void Log(unsigned char severity, const char* format, Ts... ts) {
				const char* ckstring = "Hallo";
				LogInternal(severity, "Hallo", " dit", " is" , " mijn", " logger");
				return;
			}

			template<typename T>
			const char* ToString(T t) {
				return ToString(t);
			}

			template<>
			const char* ToString(const char* t) {
				return t;
			}

			static Logger* GetCoreLogger();

		protected:
			template<typename First>
			void LogInternal(First&& first) {
				printf(ToString(first));
			}

			template<typename First, typename... Args>
			void LogInternal(First&& first, Args&&... args) {
				printf(ToString(first));
				if (sizeof...(Args))
					LogInternal(args...);
			}

			template<typename... Args>
			void LogInternal(unsigned char severity, Args... args) {
				return LogInternal(std::forward<Args>(args)...);
			}
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