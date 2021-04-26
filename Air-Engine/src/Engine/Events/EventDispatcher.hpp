#pragma once

#include <map>
#include <unordered_map>
#include <vector>


namespace engine {
	namespace events {

		class Event;
		class EventListener;

		typedef std::vector<const EventListener*> EventList;
		typedef std::unordered_map<long long, EventList*> PriorityMap;

		class EventPriorityMap {
		protected:
			PriorityMap* m_PrioMap;

		public:
			EventPriorityMap();

			~EventPriorityMap();

			void Add(unsigned int event, const EventListener* listener);

			void Remove(unsigned int event, const EventListener* listener);

			std::vector<const EventListener*>* GetListeners(unsigned int event, unsigned char priority) const;

			/// <summary>
			/// Creates a long long of the event id together with a bitmask for the priority
			/// </summary>
			/// <param name="event">unsigned int representing the event</param>
			/// <param name="priority">a byte representing the priority, see Priority in EventListener.h</param>
			/// <returns>A long long with priority in the highest byte and event in the lowest 4 bytes</returns>
			static long long GetKeyMask(unsigned int event, unsigned char priority);
		protected:
			EventList* CreateEntry(unsigned int event, unsigned char priority);
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