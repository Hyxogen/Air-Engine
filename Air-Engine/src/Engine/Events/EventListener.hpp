#pragma once

namespace engine {
	namespace events {

		class Event;

		class EventListener {
		public:
			//If the function returns true, the event dispatcher will stop with passing the current event to other listeners
			virtual bool OnEvent(Event& event);
		};

	}
}