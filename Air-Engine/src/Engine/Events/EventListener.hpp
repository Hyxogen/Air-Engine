#pragma once

namespace engine {
	namespace events {

		class Event;

		class EventListener {
		public:
			void OnEvent(const Event* event) const = 0;
		};

	}
}