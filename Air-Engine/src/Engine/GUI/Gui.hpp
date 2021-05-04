#pragma once

namespace engine {

	namespace io {
		class Keyboard;
		class Mouse;
	}

	namespace gui {

		class GuiContext {
			io::Keyboard* m_Keyboard;
			io::Mouse* m_Mouse;

		public:
			bool BeginMenu(const char* name, bool* open = 0);
		};

	}
}