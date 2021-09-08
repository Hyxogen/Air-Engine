#include "airpch.h"
#include "Logger.hpp"

#ifdef AIR_PLATFORM_WINDOWS
#include "../../../Platform/Windows/ConsoleSink.h"
#endif

namespace engine {
	namespace util {

		Logger* Logger::s_CoreLogger = nullptr;

		Logger::Logger(const char* name) : m_Name(name), m_Verbosity(0) {

		}

		Logger::~Logger() {
			Destroy();
		}

		bool Logger::AddSink(Sink* sink) {
			m_Sinks.insert(sink);
			return false;
		}

		bool Logger::ShouldPrint(uint8 severity) {
			return severity >= m_Verbosity;
		}

		void Logger::SetVerbosity(uint8 verbosity) {
			if (verbosity > SE_CRITICAL) {
				m_Verbosity = SE_CRITICAL;
				return;
			}
			m_Verbosity = verbosity;
		}

		Logger* Logger::GetCoreLogger() {
			if (s_CoreLogger == nullptr) {
				s_CoreLogger = new Logger("CORE");
				#ifdef AIR_PLATFORM_WINDOWS
				s_CoreLogger->AddSink(new platform::windows::ConsoleSink());
				#endif
			}

			return s_CoreLogger;
		}

		void Logger::ClearBuffer() {
			m_Output.str("");
		}

		void Logger::Destroy() {
			SinkList::iterator it;

			for (it = m_Sinks.begin(); it != m_Sinks.end(); ++it) {
				delete* it;
			}
		}

		void Logger::InsertTimeString() {
			std::time_t now = std::time(0);
			std::tm time;
			localtime_s(&time, &now);
			m_Output << "[" << time.tm_hour << ":" << time.tm_min << ":" << time.tm_sec << "]";
		}

		void Logger::Flush(uint8 severity) {
			SinkList::iterator it;

			std::string string = m_Output.str();

			for (it = m_Sinks.begin(); it != m_Sinks.end(); ++it) {
				((Sink*)*it)->Print(severity, string.c_str());
			}
			ClearBuffer();
		}

		const char* Logger::GetSeverityString(uint8 severity) {
			switch (severity) {
			case SE_TRACE:
				return "[TRACE]";
			case SE_INFO:
				return "[INFO]";
			case SE_WARN:
				return "[WARN]";
			case SE_ERROR:
				return "[ERROR]";
			case SE_CRITICAL:
				return "[CRITICAL]";
			default:
				return "[UNK]";
			}
		}
	}
}