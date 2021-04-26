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
			std::unordered_map<long long, std::vector<const EventListener*>*>* m_PrioMap;

		public:
			EventPriorityMap();

			~EventPriorityMap();

			void Add(unsigned int event, const EventListener* listener);

			void Remove(unsigned int event, const EventListener* listener);

			std::vector<const EventListener*>* GetListeners(unsigned int event, unsigned char priority) const;

			static long long GetKeyMask(unsigned int event, unsigned char priority);
		protected:
			std::vector<const EventListener*>* CreateEntry(unsigned int event, unsigned char priority);
		};

		class EventDispatcher {
		protected:
			EventPriorityMap* m_PriorityMap;
		public:
			EventDispatcher();

			~EventDispatcher();

			void Register(unsigned int event, const EventListener* listener);

			void Remove(unsigned int event, const EventListener* listener);

			bool Dispatch(Event* event) const;

		protected:
			bool Execute(std::vector<const EventListener*>* listeners, Event* event) const;
		};

	}
}