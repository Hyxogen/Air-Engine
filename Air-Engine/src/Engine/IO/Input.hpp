/*
This is a simple helper class for handling input. Please be aware that this will most likely be removed or changed once multiple window support gets added
*/
#pragma once


namespace engine {
	namespace io {

		class Keyboard;
		class Mouse;

		class Input {
			static Input* s_Instance;

			Keyboard* m_Keyboard;
			Mouse* m_Mouse;

		public:
			//Returns false if no errors
			bool Initialize();

			inline Keyboard* GetKeyboard() const { return m_Keyboard; }

			inline Mouse* GetMouse() const { return m_Mouse; }

			static Input* GetInstance();
		};

	}
}