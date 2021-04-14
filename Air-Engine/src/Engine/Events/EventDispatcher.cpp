#include "EventDispatcher.hpp"

#include "Event.hpp"
#include "EventListener.hpp"

namespace engine {
	namespace events {

		EventDispatcher::EventDispatcher() : m_Listeners(*(new std::unordered_map<unsigned int, std::vector<const EventListener*>&>())){
			
		}

		EventDispatcher::~EventDispatcher() {
			std::unordered_map<unsigned int, std::vector<const EventListener*>&>::iterator it;

			//Checken of dit door alle elementen heen gaat
			for (it = m_Listeners.begin(); it != m_Listeners.end(); ++it) {
				delete& it->second;
			}

			delete &m_Listeners;
		}

		void EventDispatcher::Register(unsigned int event, const EventListener* listener) {
			std::unordered_map<unsigned int, std::vector<const EventListener*>&>::iterator key = m_Listeners.find(event);

			if (key == m_Listeners.end())
				key = m_Listeners.emplace(event, *(new std::vector<const EventListener*>())).first;

			key->second.push_back(listener);
		}

		void EventDispatcher::Remove(unsigned int event, const EventListener* listener) {
			std::unordered_map<unsigned int, std::vector<const EventListener*>&>::iterator key = m_Listeners.find(event);

			if (key == m_Listeners.end())
				return;

			for (unsigned int i = 0; i < key->second.size(); i++) {
				if (key->second[i] == listener) {
					key->second.erase(key->second.begin() + i);
					return;
				}
			}
		}

		void EventDispatcher::Dispatch(Event& event) const {
			std::unordered_map<unsigned int, std::vector<const EventListener*>&>::iterator key = m_Listeners.find(event.GetID());

			if (key == m_Listeners.end()) return;

			std::vector<const EventListener*>::iterator it = key->second.begin();

			//Checken of dit door alles loopt
			while ((it++) != key->second.end()) {
				if (((EventListener*)*it)->OnEvent(event))
					break;
			}
		}
	}
}