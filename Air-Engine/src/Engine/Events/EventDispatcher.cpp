#include "EventDispatcher.hpp"

#include "Event.hpp"
#include "EventListener.hpp"

namespace engine {
	namespace events {

		EventDispatcher::EventDispatcher() {
			
		}
		//std::unordered_map<unsigned int, PriorityMap*>&
		EventDispatcher::~EventDispatcher() {

		}

		void EventDispatcher::Register(unsigned int event, const EventListener* listener) {
			InsertEvent(event, listener);
		}

		void EventDispatcher::Remove(unsigned int event, const EventListener* listener) {

		}

		void EventDispatcher::Dispatch(Event* event) const {

		}

		bool EventDispatcher::InsertEvent(unsigned int event, const EventListener* listener) {
			return true;
		}
	}
}