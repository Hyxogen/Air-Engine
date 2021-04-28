#pragma once

namespace engine {
	namespace io {

		class Keyboard;
		class Mouse;

		/// <summary>
		/// This is a temporary class to allow for quick input access
		/// </summary>
		class Input {
			static Input* s_Instance;

			Keyboard* m_Keyboard;
			Mouse* m_Mouse;

		public:
			bool Initialize();

			inline Keyboard* GetKeyboard() const { return m_Keyboard; }

			inline Mouse* GetMouse() const { return m_Mouse; }

			static Input* GetInstance();
		};

	}
}