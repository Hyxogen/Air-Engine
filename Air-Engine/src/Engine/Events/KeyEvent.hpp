#pragma once

#include "Event.hpp"
#include "../IO/KeyCodes.hpp"
#include "../Util/HashUtils.hpp"

namespace engine {

	namespace io {
		class Window;
	}

	namespace events {

		class KeyEvent : public Event {
		protected:
			io::Window* m_Window = nullptr;
			io::KeyCode m_KeyCode;

			KeyEvent() {}

			KeyEvent(io::Window* window, io::KeyCode keyCode) : m_Window(window), m_KeyCode(keyCode) {}

		public:
			inline io::KeyCode GetKeyCode() const { return m_KeyCode; }

			virtual unsigned int GetID() const = 0;
		};

		class KeyDownEvent : public KeyEvent {
		protected:
			bool m_Repeat;

			KeyDownEvent() {}
		public:
			KeyDownEvent(io::Window* window, io::KeyCode keyCode, bool repeat) : KeyEvent(window, keyCode), m_Repeat(repeat) {}

			unsigned int GetID() const override { return Hash("EVENT_KEY_DOWN", 15); }

			inline bool IsRepeat() const { return m_Repeat; }
		};

		class KeyReleaseEvent : public KeyEvent {
		protected:
			
			KeyReleaseEvent();
		public:
			KeyReleaseEvent(io::Window* window, io::KeyCode keyCode) : KeyEvent(window, keyCode) {}

			unsigned int GetID() const override { return Hash("EVENT_KEY_RELEASE", 18); }
		};
	}
}