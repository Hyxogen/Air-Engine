#pragma once

namespace engine {
	namespace events {

		class Event {
		public:
			virtual unsigned int GetID() const = 0;
		};

} }