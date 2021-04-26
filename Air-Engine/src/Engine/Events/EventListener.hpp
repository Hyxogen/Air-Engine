#pragma once

namespace engine {
	namespace events {

		class Event;
		
		enum Priority : unsigned char {
			PRIORITY_MONITOR		= 0x00,			//Listeners with this priority will be called very first, should only be used when not manipulating data and/or handling the event (i.e. OnEvent returns true)
			PRIORITY_HIGHEST		= 0x01,			//Highest priority, listeners with this priority will be called after PRIORITY_MONITOR
			PRIORITY_HIGH			= 0x02,			//Second highest priority, listeners with this priority will be called after PRIORITY_HIGHEST
			PRIORITY_NORMAL			= 0x03,			//Normal priority, listeners with this priority will be called after PRIORITY_HIGH. Default priority of listeners
			PRIORITY_LOW			= 0x04,			//Second lowest priority, listeners with this priority will be called after PRIORITY_NORMAL
			PRIORITY_LOWEST			= 0x05			//Lowest priority, listeners with this priority will be called very last
		};

		class EventListener {
		public:
			//If the function returns true, the event dispatcher will stop with passing the current event to other listeners
			virtual bool OnEvent(Event* event) = 0;

			virtual unsigned char GetPriority() const { return PRIORITY_NORMAL; };
		};

	}
}