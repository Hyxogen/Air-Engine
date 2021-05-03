#include "airpch.h"
#pragma once

namespace platform {
	namespace windows {

		enum Color {
			COLOR_RED			= FOREGROUND_RED	| FOREGROUND_INTENSITY,
			COLOR_BLUE			= FOREGROUND_BLUE	| FOREGROUND_INTENSITY,
			COLOR_GREEN			= FOREGROUND_GREEN	| FOREGROUND_INTENSITY,
			COLOR_YELLOW		= FOREGROUND_GREEN	| FOREGROUND_RED	| FOREGROUND_INTENSITY,
			COLOR_MAGENTA		= FOREGROUND_BLUE	| FOREGROUND_RED	| FOREGROUND_INTENSITY,
			COLOR_CYAN			= FOREGROUND_BLUE	| FOREGROUND_GREEN	| FOREGROUND_INTENSITY,
			COLOR_GREY			= FOREGROUND_BLUE	| FOREGROUND_GREEN	| FOREGROUND_RED,
			COLOR_WHITE			= FOREGROUND_BLUE	| FOREGROUND_GREEN	| FOREGROUND_RED | FOREGROUND_INTENSITY,

			COLOR_DARK_RED		= FOREGROUND_RED,
			COLOR_DARK_BLUE		= FOREGROUND_BLUE,
			COLOR_DARK_GREEN	= FOREGROUND_GREEN | FOREGROUND_GREEN,
			COLOR_DARK_YELLOW	= FOREGROUND_GREEN | FOREGROUND_RED,
			COLOR_DARK_MAGENTA	= FOREGROUND_BLUE | FOREGROUND_RED,
			COLOR_DARK_CYAN		= FOREGROUND_BLUE | FOREGROUND_GREEN
		};
		
		struct PriorityColorPair {
			unsigned char m_Priority;
			unsigned char m_Color;
		};

		class ConsoleSink : public engine::util::Sink {
		protected:
			HANDLE m_ConsoleHandle;
			PriorityColorPair* m_Colors;
		public:
			ConsoleSink();

			ConsoleSink(PriorityColorPair* colors);

			virtual ~ConsoleSink();

			virtual bool Print(unsigned char severity, const char* str);

			inline HANDLE GetConsoleHandle() const { return m_ConsoleHandle; }

		protected:
			void ResetColor();

			void SetColor(unsigned char color);

			unsigned char GetColor(unsigned char priority);
		};
	}
}