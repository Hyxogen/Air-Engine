#pragma once

namespace engine {
	namespace events {

		class EventListener;

		class EventDispatcher {

			template<class T>
			void RegisterListener(T type, void* function);
		};

} }