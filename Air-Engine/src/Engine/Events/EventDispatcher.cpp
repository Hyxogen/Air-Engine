#include "EventDispatcher.hpp"

namespace engine {
	namespace events {

		EventDispatcher::EventDispatcher() {
			m_Listeners = new std::unordered_map<unsigned int, std::vector<const EventListener&>&>&();
		}

		EventDispatcher::~EventDispatcher() {
			std::unordered_map<unsigned int, std::vector<const EventListener&>&>::iterator it = m_Listeners.begin();

			//Checken of dit door alle elementen heen gaat
			while ((it++) != m_Listeners.end()) {
				delete it->second;
			}

			delete m_Listeners;
		}

		void EventDispatcher::Register(unsigned int event, const EventListener& listener) {
			std::unordered_map<unsigned int, std::vector<const EventListener&>&>::iterator key = m_Listeners.find(event);

			if (key == m_Listeners.end())
				key = m_Listeners.emplace(event, new std::vector<const EventListener&>()).first;

			key->second.push_back(listener);
		}

	}
}