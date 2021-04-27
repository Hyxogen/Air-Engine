#pragma once

#include <map>
#include <unordered_map>
#include <vector>


namespace engine {
	namespace events {

		class Event;
		class EventListener;

		typedef std::vector<const EventListener*> EventList;
		//Probeer dit eens met een template te maken
		typedef std::map<long long, EventList*> PriorityMap;

		class EventPriorityMap {
		protected:
			PriorityMap* m_PrioMap;

		public:
			EventPriorityMap();

			~EventPriorityMap();

			void Add(unsigned int event, const EventListener* listener);

			void Remove(unsigned int event, const EventListener* listener);

			EventList* GetListeners(unsigned int event, unsigned char priority) const;

			EventList GetListenersOrdered(unsigned int event);

			/// <summary>
			/// Creates a long long of the event id together with a bitmask for the priority
			/// </summary>
			/// <param name="event">unsigned int representing the event</param>
			/// <param name="priority">a byte representing the priority, see Priority in EventListener.h</param>
			/// <returns>A long long with priority in the highest byte and event in the lowest 4 bytes</returns>
			static long long GetKeyMask(unsigned int event, unsigned char priority);

			static unsigned char GetPriority(long long key);

			static unsigned int GetEvent(long long key);
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
			bool Execute(EventList* listeners, Event* event) const;
		};

	}
}