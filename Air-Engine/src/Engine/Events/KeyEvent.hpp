#pragma once

#include "Event.hpp"
#include "../IO/KeyCodes.hpp"

namespace engine {
	namespace events {

		class KeyEvent : public Event {
		protected:
			io::KeyCode m_KeyCode;

			KeyEvent(io::KeyCode keyCode);

		public:
			inline io::KeyCode GetKeyCode() const { return m_KeyCode; }

			virtual unsigned int GetID() const = 0;
		};
	}
}