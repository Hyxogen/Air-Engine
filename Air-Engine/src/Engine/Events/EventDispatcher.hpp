#include "airpch.h"
#pragma once

namespace engine {
	namespace events {

		class Event;
		class EventListener;

		typedef std::vector<const EventListener*> EventList;
		//Probeer dit eens met een template te maken
		typedef std::map<int64, EventList*> PriorityMap;

		class EventPriorityMap {
		protected:
			PriorityMap* m_PrioMap;

		public:
			EventPriorityMap();

			~EventPriorityMap();

			void Add(uint32 event, const EventListener* listener);

			void Remove(uint32 event, const EventListener* listener);

			EventList* GetListeners(uint32 event, uint8 priority) const;

			EventList GetListenersOrdered(uint32 event);

			/// <summary>
			/// Creates a int64 of the event id together with a bitmask for the priority
			/// </summary>
			/// <param name="event">uint32 representing the event</param>
			/// <param name="priority">a byte representing the priority, see Priority in EventListener.h</param>
			/// <returns>A int64 with priority in the highest byte and event in the lowest 4 bytes</returns>
			static int64 GetKeyMask(uint32 event, uint8 priority);

			static uint8 GetPriority(int64 key);

			static uint32 GetEvent(int64 key);
		protected:
			EventList* CreateEntry(uint32 event, uint8 priority);
		};

		class EventDispatcher {
		protected:
			EventPriorityMap* m_PriorityMap;
		public:
			EventDispatcher();

			~EventDispatcher();

			void Register(uint32 event, const EventListener* listener);

			void Remove(uint32 event, const EventListener* listener);

			bool Dispatch(Event* event) const;

		protected:
			bool Execute(EventList* listeners, Event* event) const;
		};

	}
}