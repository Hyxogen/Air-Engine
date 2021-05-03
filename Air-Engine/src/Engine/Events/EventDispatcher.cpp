#include "airpch.h"
#include "EventDispatcher.hpp"

#include "Event.hpp"
#include "EventListener.hpp"

namespace engine {
	namespace events {

		EventPriorityMap::EventPriorityMap() : m_PrioMap(new PriorityMap()) {

		}

		EventPriorityMap::~EventPriorityMap() {
			PriorityMap::iterator it;

			for (it = m_PrioMap->begin(); it != m_PrioMap->end(); ++it)
				delete it->second;
			delete m_PrioMap;
		}

		void EventPriorityMap::Add(unsigned int event, const EventListener* listener) {
			EventList* listeners = GetListeners(event, listener->GetPriority());

			if (listeners == nullptr)
				listeners = CreateEntry(event, listener->GetPriority());

			listeners->push_back(listener);
			return;
		}

		void EventPriorityMap::Remove(unsigned int event, const EventListener* listener) {
			EventList* listeners = GetListeners(event, listener->GetPriority());
			if (listener == nullptr) return;

			for (int i = 0; i < listeners->size(); i++) {
				if (listeners->at(i) == listener) {
					listeners->erase(listeners->begin() + i);
					return;
				}
			}
		}

		EventList* EventPriorityMap::GetListeners(unsigned int event, unsigned char priority) const {
			PriorityMap::iterator it = m_PrioMap->find(GetKeyMask(event, priority));

			if (it == m_PrioMap->end())
				return nullptr;
			else
				return it->second;
		}

		EventList EventPriorityMap::GetListenersOrdered(unsigned int event) {
			EventList ret;
			PriorityMap::iterator it = m_PrioMap->lower_bound(GetKeyMask(event, PRIORITY_MONITOR));

			if (it == m_PrioMap->end())
				return ret;

			long long max = GetKeyMask(event, PRIORITY_LOWEST);
			long long key = 0;
			long long id, priority;
			int index = 0;
			for (it; it != m_PrioMap->end(); ++it) {
				key = it->first;
				if (key > max) break;

				id = GetEvent(key);
				priority = GetPriority(key);

				if (id != event) continue;

				ret.insert(ret.begin() + index, it->second->begin(), it->second->end());
				index = ret.size();
			}
			return ret;
		}

		long long EventPriorityMap::GetKeyMask(unsigned int event, unsigned char priority) {
			return (((long long)0 | priority) << ((sizeof(long long) - sizeof(priority)) << 3)) | event;
		}

		unsigned int EventPriorityMap::GetEvent(long long key) {
			return key & static_cast<long long>(UINT_MAX);
		}

		unsigned char EventPriorityMap::GetPriority(long long key) {
			return key & (static_cast<long long>(0xff)) << ((sizeof(long long) - sizeof(unsigned char)) << 3);
		}

		EventList* EventPriorityMap::CreateEntry(unsigned int event, unsigned char priority) {
			EventList* ret = new EventList();
			m_PrioMap->emplace(GetKeyMask(event, priority), ret);
			return ret;
		}

		EventDispatcher::EventDispatcher() : m_PriorityMap(new EventPriorityMap()) {

		}

		EventDispatcher::~EventDispatcher() {
			delete m_PriorityMap;
		}

		void EventDispatcher::Register(unsigned int event, const EventListener* listener) {
			m_PriorityMap->Add(event, listener);
		}

		void EventDispatcher::Remove(unsigned int event, const EventListener* listener) {
			m_PriorityMap->Remove(event, listener);
		}

		bool EventDispatcher::Dispatch(Event* event) const {
			EventList listeners = std::move(m_PriorityMap->GetListenersOrdered(event->GetID()));
			return Execute(&listeners, event);
		}

		bool EventDispatcher::Execute(EventList* listeners, Event* event) const {
			if (listeners == nullptr) return false;
			EventList::iterator it;

			for (it = listeners->begin(); it != listeners->end(); ++it) {
				if (((EventListener*)*it)->OnEvent(event))
					return true;
			}
			return false;
		}
	}
}