#pragma once

#define AIR_TRACE 4
#define AIR_INFO 3
#define AIR_WARN 2
#define AIR_ERROR 1
#define AIR_CRITICAL 0

namespace engine {
	namespace util {

		class Logger {
			unsigned int mVerbosity = 0;
			unsigned int mChannelMask = 0;
			const char* mPrefix;

			static Logger* CORE_LOGGER;

		public:
			Logger(const char* mPrefix = "");

			void Log(unsigned int verbosity, unsigned int channel, const char* data...) const;

			void SetVerbosity(unsigned int verbosity);

			void SetChannelMask(unsigned int channelMask);

			inline unsigned int GetVerbosity() const { return mVerbosity; }

			inline unsigned int GetChannelMask() const { return mChannelMask; }

			static const Logger* GetCoreLogger();
		};

	}
}

/*
#define AIR_CORE_TRACE(...) engine::util::Logger::GetCoreLogger().Log(AIR_TRACE, 0, __VA_ARGS__);
#define AIR_CORE_INFO(...) engine::util::Logger::GetCoreLogger().Log(AIR_INFO, 0, __VA_ARGS__);
#define AIR_CORE_WARN(...) engine::util::Logger::GetCoreLogger().Log(AIR_WARN, 0, __VA_ARGS__);
#define AIR_CORE_ERROR(...) engine::util::Logger::GetCoreLogger().Log(AIR_ERROR, 0, __VA_ARGS__);
#define AIR_CORE_CRITICAL(...) engine::util::Logger::GetCoreLogger().Log(AIR_CRITICAL, 0, __VA_ARGS__);
*/