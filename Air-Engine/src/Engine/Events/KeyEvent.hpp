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
			io::Window* m_Window;
			io::KeyCode m_KeyCode;

			KeyEvent(io::Window* window, io::KeyCode keyCode) : m_Window(window), m_KeyCode(keyCode) {}

		public:
			inline io::KeyCode GetKeyCode() const { return m_KeyCode; }

			virtual unsigned int GetID() const = 0;
		};

		class KeyDownEvent : public KeyEvent {
		protected:
			unsigned short m_RepeatCount;

		public:
			KeyDownEvent(io::Window* window, io::KeyCode keyCode, unsigned short repeatCount) : KeyEvent(window, keyCode), m_RepeatCount(repeatCount) {}

			unsigned int GetID() const override { return Hash("EVENT_KEY_DOWN", 15) }

			inline unsigned short GetRepeatCount() const { return m_RepeatCount; }
		};

		class KeyReleaseEvent : public KeyEvent {
		public:
			KeyReleaseEvent(io::Window* window, io::KeyCode keyCode) : KeyEvent(window, keyCode) {}

			unsigned int GetID() const override { return Hash("EVENT_KEY_RELEASE", 18) }
		};
	}
}