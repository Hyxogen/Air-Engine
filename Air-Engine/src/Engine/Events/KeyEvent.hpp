#include "airpch.h"
#pragma once

#include "Event.hpp"
#include "../IO/KeyCodes.hpp"

namespace engine {

	namespace io {
		class Window;
	}

	namespace events {

		class KeyEvent : public Event {
		protected:
			io::Window* m_Window = nullptr;
			unsigned int m_KeyCode = io::KeyCode::KEY_UNKNOWN;

			KeyEvent(io::Window* window, unsigned int keyCode) : m_Window(window), m_KeyCode(keyCode) {}

		public:
			inline unsigned int GetKeyCode() const { return m_KeyCode; }

			inline io::Window* GetWindow() const { return m_Window; }

			virtual unsigned int GetID() const = 0;
		};

		class KeyDownEvent : public KeyEvent {
		protected:
			bool m_Repeat;
		public:
			KeyDownEvent(io::Window* window, unsigned int keyCode, bool repeat = false) : KeyEvent(window, keyCode), m_Repeat(repeat) {}

			unsigned int GetID() const override { return Hash("EVENT_KEY_DOWN", 15); }

			inline bool IsRepeat() const { return m_Repeat; }
		};

		class KeyReleaseEvent : public KeyEvent {
		public:
			KeyReleaseEvent(io::Window* window, unsigned int keyCode) : KeyEvent(window, keyCode) {}

			unsigned int GetID() const override { return Hash("EVENT_KEY_RELEASE", 18); }
		};
	}
}