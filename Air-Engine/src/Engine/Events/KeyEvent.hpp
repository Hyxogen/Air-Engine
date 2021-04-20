#pragma once

#include "Event.hpp"
#include "../IO/KeyCodes.hpp"
#include "../Util/HashUtils.hpp"

namespace engine {
	namespace events {

		class KeyEvent : public Event {
		protected:
			io::KeyCode m_KeyCode;

			KeyEvent(io::KeyCode keyCode) : m_KeyCode(keyCode) {}

		public:
			inline io::KeyCode GetKeyCode() const { return m_KeyCode; }

			virtual unsigned int GetID() const = 0;
		};

		class KeyDownEvent : public KeyEvent {
		protected:
			unsigned short m_RepeatCount;

		public:
			KeyDownEvent(io::KeyCode keyCode, unsigned short repeatCount) : KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

			unsigned int GetID() const override { return Hash("EVENT_KEY_DOWN", 15) }

			inline unsigned short GetRepeatCount() const { return m_RepeatCount; }
		};

		class KeyReleaseEvent : public KeyEvent {
		public:
			KeyReleaseEvent(io::KeyCode keyCode) : KeyEvent(keyCode) {}

			unsigned int GetID() const override { return Hash("EVENT_KEY_RELEASE", 18) }
		};
	}
}