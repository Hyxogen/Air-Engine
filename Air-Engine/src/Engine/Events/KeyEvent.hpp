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
			uint32 m_KeyCode = io::KeyCode::KEY_UNKNOWN;

			KeyEvent(io::Window* window, uint32 keyCode) : m_Window(window), m_KeyCode(keyCode) {}

		public:
			inline uint32 GetKeyCode() const { return m_KeyCode; }

			inline io::Window* GetWindow() const { return m_Window; }

			virtual uint32 GetID() const = 0;
		};

		class KeyDownEvent : public KeyEvent {
		protected:
			bool m_Repeat;
		public:
			KeyDownEvent(io::Window* window, uint32 keyCode, bool repeat = false) : KeyEvent(window, keyCode), m_Repeat(repeat) {}

			uint32 GetID() const override { return Hash("EVENT_KEY_DOWN", 15); }

			inline bool IsRepeat() const { return m_Repeat; }
		};

		class KeyReleaseEvent : public KeyEvent {
		public:
			KeyReleaseEvent(io::Window* window, uint32 keyCode) : KeyEvent(window, keyCode) {}

			uint32 GetID() const override { return Hash("EVENT_KEY_RELEASE", 18); }
		};
	}
}