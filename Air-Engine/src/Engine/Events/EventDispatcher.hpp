#pragma once

#include <map>
#include <vector>
#include <typeindex>
#include "Event.hpp"
#include "../Core/Assert.hpp"

typedef void (*LISTENER_FUNCTION)(const engine::events::Event*);

namespace engine {
	namespace events {

		class EventDispatcher {
			std::map<std::type_index, std::vector<LISTENER_FUNCTION>*>* mFunctions;

		public:
			EventDispatcher();

			~EventDispatcher();

			template<class T>
			void RegisterListener(LISTENER_FUNCTION function) {
				///ASSERT(std::is_same<typeid(T), typeid(Event)>());

				//const std::type_info& info(typeid(T));

				std::map<std::type_index, std::vector<LISTENER_FUNCTION>*>::iterator it = mFunctions->find(typeid(T));
				if (it == mFunctions->end())
					mFunctions->emplace(typeid(T), new std::vector<LISTENER_FUNCTION>);

				it = mFunctions->find(typeid(T));
				it->second->push_back(function);
			}

			void DispatchEvent(const Event* event) const {
				std::map<std::type_index, std::vector<LISTENER_FUNCTION>*>::iterator it = mFunctions->find(typeid((*event)));
				if (it == mFunctions->end()) return;

				std::vector<LISTENER_FUNCTION>::iterator func_it;
				for (func_it = it->second->begin(); func_it != it->second->end(); ++func_it)
					(*func_it)(event);
			}
		};

} }