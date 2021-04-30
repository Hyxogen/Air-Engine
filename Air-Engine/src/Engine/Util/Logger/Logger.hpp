#pragma once

#include <unordered_set>
#include "Sink.hpp"

namespace engine {
	namespace util {

		class Logger {
		protected:
			const char* m_Name;
			char m_Buffer[1024];

			static Logger* s_CoreLogger;

		public:
			Logger(const char* name);

			~Logger();

			template<typename... Ts>
			void Log(unsigned char severity, const char* format, Ts... ts) {
				const char* ckstring = "Hallo";
				LogInternal(true, "Test", "Appels");
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
			void ClearBuffer();

			template<typename First>
			void LogInternalS(unsigned int& position, First&& first) {
				const char* string = ToString(first);
				unsigned int length = strnlen_s(string, 1024);
				memcpy(&m_Buffer[position], string, length);
				position += length;
			}

			template<typename First, typename... Args>
			void LogInternalS(unsigned int& position, First&& first, Args&&... args) {
				LogInternalS(position,first);
				if (sizeof...(Args))
					LogInternalS(position, args...);
			}

			template<typename... Args>
			void LogInternal(bool safety, Args... args) {
				ClearBuffer();
				unsigned int position = 0;
				LogInternalS(position, std::forward<Args>(args)...);
				printf("%s", m_Buffer);
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