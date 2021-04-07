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
				std::map<std::type_index, std::vector<LISTENER_FUNCTION>*>::iterator it = mFunctions->find(typeid(T));
				if (it == mFunctions->end())
					mFunctions->emplace(typeid(T), new std::vector<LISTENER_FUNCTION>);

				it = mFunctions->find(typeid(T));
				it->second->push_back(function);
			}

			void DispatchEvent(const Event* event) const;
		};

} }