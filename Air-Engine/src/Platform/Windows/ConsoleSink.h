#pragma once

#include <windows.h>

#include "../../Engine/Util/Logger/Sink.hpp"

namespace platform {
	namespace windows {

		class ConsoleSink : public engine::util::Sink {
		protected:
			HANDLE m_ConsoleHandle;
		public:
			ConsoleSink();

			virtual ~ConsoleSink();

			virtual bool Print(unsigned char severity, const char* str);

			void SetColor(unsigned char color);

			inline HANDLE GetConsoleHandle() const { return m_ConsoleHandle; }
		};
	}
}