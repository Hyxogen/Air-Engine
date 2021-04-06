#include "EventDispatcher.hpp"

namespace engine {
	namespace events {

		EventDispatcher::EventDispatcher() {
			mFunctions = new std::map<std::type_info, std::vector<LISTENER_FUNCTION>*>();
		}

		EventDispatcher::~EventDispatcher() {
			std::map<std::type_info, std::vector<LISTENER_FUNCTION>*>::iterator it = mFunctions->begin();

			for (it = mFunctions->begin(); it != mFunctions->end(); ++it)
				delete it->second;

			delete mFunctions;
		}
	}
}