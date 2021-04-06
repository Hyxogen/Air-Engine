#pragma once

#include <map>
#include <vector>
#include <typeindex>
#include "Event.hpp"
#include "../Core/Assert.hpp"

typedef void (*LISTENER_FUNCTION) (engine::events::Event*);

namespace engine {
	namespace events {

		class EventDispatcher {
			std::map<std::type_info, std::vector<LISTENER_FUNCTION>*>* mFunctions;

		public:
			EventDispatcher();

			~EventDispatcher();

			template<class T>
			void RegisterListener(LISTENER_FUNCTION function) {
				if (mFunctions->at(typeid(T)) == 0)
					mFunctions->emplace(new std::vector<LISTENER_FUNCTION>);
				mFunctions->at(typeid(T))->push_back(function);
			}

			template<class T>
			void DispatchEvent(const T* event) const {
				ASSERT(typeid(T) == typeid(event));
				
				std::map<std::type_info, std::vector<LISTENER_FUNCTION>*>::iterator it = mFunctions->find(typeid(T));
				if (it == mFunctions->end()) return;

				std::vector<LISTENER_FUNCTION>::iterator func_it;
				for (func_it = it->second->begin(); func_it != it->second->end; ++func_it)
					*func_it();
			}
		};

} }