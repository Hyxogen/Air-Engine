#pragma once

#include <unordered_map>
#include <vector>

namespace engine {
	namespace events {

		class Event;
		class EventListener;

		class EventDispatcher {
			std::unordered_map<unsigned int, std::vector<const EventListener*>&>& m_Listeners;

		public:
			EventDispatcher();

			~EventDispatcher();

			void Register(unsigned int event, const EventListener* listener);

			void Remove(unsigned int event, const EventListener* listener);

			//Change events to pointers
			void Dispatch(Event& event) const;
		};

	}
}