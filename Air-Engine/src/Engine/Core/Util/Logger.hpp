#pragma once

namespace engine {
	namespace util {

		class Logger {
			unsigned int mVerbosity = 0;
			unsigned int mChannelMask = 0;
			const char* mPrefix;

			const static Logger* CORE_LOGGER;

		public:
			Logger(const char* mPrefix = "");

			void Log(unsigned int verbosity, unsigned int channel, const char* data...);

			void SetVerbosity(unsigned int verbosity);

			void SetChannelMask(unsigned int channelMask);

			inline unsigned int GetVerbosity() const { return mVerbosity; }

			inline unsigned int GetChannelMask() const { return mChannelMask; }

		private:
			static Logger* GetCoreLogger();
		};

	}
}