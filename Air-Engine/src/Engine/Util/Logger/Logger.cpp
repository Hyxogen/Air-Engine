#include "Logger.hpp"


namespace engine {
	namespace util {

		Logger* Logger::s_CoreLogger = nullptr;

		Logger::Logger(const char* name) : m_Name(name) {

		}

		Logger::~Logger() {

		}

		bool Logger::AddSink(Sink* sink) {
			m_Sinks.insert(sink);
			return false;
		}

		Logger* Logger::GetCoreLogger() {
			if (s_CoreLogger == nullptr) {
				s_CoreLogger = new Logger("CORE");
			}

			return s_CoreLogger;
		}

		void Logger::ClearBuffer() {
			m_Output.str("");
		}

		void Logger::Flush(unsigned char severity) {
			SinkList::iterator it;

			std::string string = m_Output.str();

			for (it = m_Sinks.begin(); it != m_Sinks.end(); ++it) {
				((Sink*)*it)->Print(severity, string.c_str());
			}
			ClearBuffer();
		}

		const char* Logger::GetSeverityString(unsigned char severity) {
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