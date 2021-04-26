#pragma once

namespace engine {
	namespace events {

		class Event;

		enum Priority : unsigned char {
			PRIORITY_MONITOR		= 0x00,
			PRIORITY_HIGHEST		= 0x01,
			PRIORITY_HIGH			= 0x02,
			PRIORITY_NORMAL			= 0x03,
			PRIORITY_LOW			= 0x04,
			PRIORITY_LOWEST			= 0x05
		};

		class EventListener {
		public:
			//If the function returns true, the event dispatcher will stop with passing the current event to other listeners
			virtual bool OnEvent(Event& event) = 0;

			virtual unsigned char GetPriority() const { return PRIORITY_NORMAL; };
		};

	}
}