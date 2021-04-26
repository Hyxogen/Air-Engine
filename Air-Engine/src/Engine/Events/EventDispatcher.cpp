#include "EventDispatcher.hpp"

#include "Event.hpp"
#include "EventListener.hpp"

namespace engine {
	namespace events {

		EventPriorityMap::EventPriorityMap() : m_PrioMap(new std::unordered_map<long long, std::vector<const EventListener*>*>()) {

		}

		EventPriorityMap::~EventPriorityMap() {
			std::unordered_map<long long, std::vector<const EventListener*>*>::iterator it;

			for (it = m_PrioMap->begin(); it != m_PrioMap->end(); ++it)
				delete it->second;
			delete m_PrioMap;
		}

		void EventPriorityMap::Add(unsigned int event, const EventListener* listener) {
			std::vector<const EventListener*>* listeners = GetListeners(event, listener->GetPriority());

			if (listeners == nullptr)
				listeners = CreateEntry(event, listener->GetPriority());

			listeners->push_back(listener);
			return;
		}

		std::vector<const EventListener*>* EventPriorityMap::GetListeners(unsigned int event, unsigned char priority) const {
			std::unordered_map<long long, std::vector<const EventListener*>*>::iterator it = m_PrioMap->find(GetKeyMask(event, priority));

			if (it == m_PrioMap->end())
				return nullptr;
			else
				return it->second;
		}

		long long EventPriorityMap::GetKeyMask(unsigned int event, unsigned char priority) {
			long long ret = priority;
			ret = ret << ((sizeof(long long) - sizeof(priority)) * 8);
			ret = ret | event;
			return ret;
		}

		std::vector<const EventListener*>* EventPriorityMap::CreateEntry(unsigned int event, unsigned char priority) {
			std::vector<const EventListener*>* ret = new std::vector<const EventListener*>;
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
			std::vector<const EventListener*>* listeners = m_PriorityMap->GetListeners(event, listener->GetPriority());
			if (listener == nullptr) return;

			for (int i = 0; i < listeners->size(); i++) {
				if (listeners->at(i) == listener) {
					listeners->erase(listeners->begin() + i);
					return;
				}
			}
		}

		bool EventDispatcher::Dispatch(Event* event) const {
			for (unsigned char i = PRIORITY_MONITOR; i != PRIORITY_LOWEST + 1; i++) {
				if (Execute(m_PriorityMap->GetListeners(event->GetID(), i), event))
					return true;
			}
			return false;
		}

		bool EventDispatcher::Execute(std::vector<const EventListener*>* listeners, Event* event) const {
			if (listeners == nullptr) return false;
			std::vector<const EventListener*>::iterator it;

			for (it = listeners->begin(); it != listeners->end(); ++it) {
				if (((EventListener*)*it)->OnEvent(event))
					return true;
			}
			return false;
		}
	}
}