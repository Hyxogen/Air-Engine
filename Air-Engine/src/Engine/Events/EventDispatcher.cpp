#include "EventDispatcher.hpp"

namespace engine {
	namespace events {

		EventDispatcher::EventDispatcher() {
			mFunctions = new std::map<std::type_index, std::vector<LISTENER_FUNCTION>*>();
		}

		EventDispatcher::~EventDispatcher() {
			std::map<std::type_index, std::vector<LISTENER_FUNCTION>*>::iterator it = mFunctions->begin();

			for (it = mFunctions->begin(); it != mFunctions->end(); ++it)
				delete it->second;

			delete mFunctions;
		}

		void EventDispatcher::DispatchEvent(const Event* event) const {
			std::map<std::type_index, std::vector<LISTENER_FUNCTION>*>::iterator it = mFunctions->find(typeid((*event)));
			if (it == mFunctions->end()) return;

			std::vector<LISTENER_FUNCTION>::iterator func_it;
			for (func_it = it->second->begin(); func_it != it->second->end(); ++func_it)
				(*func_it)(event);
		}
	}
}