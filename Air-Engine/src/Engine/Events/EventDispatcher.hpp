#pragma once

#include <map>
#include <unordered_map>
#include <vector>

namespace engine {
	namespace events {

		class Event;
		class EventListener;

		class EventPriorityMap {
		protected:

		};

		class EventDispatcher {

		public:
			EventDispatcher();

			~EventDispatcher();

			void Register(unsigned int event, const EventListener* listener);

			void Remove(unsigned int event, const EventListener* listener);

			void Dispatch(Event* event) const;

		private:
			bool InsertEvent(unsigned int event, const EventListener* listener);
		};

	}
}