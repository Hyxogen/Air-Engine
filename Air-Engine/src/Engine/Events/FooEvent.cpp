#include "FooEvent.hpp"

namespace engine {
	namespace events {

		FooEvent::FooEvent(unsigned int message) : mMessage(message) {

		}

		unsigned int FooEvent::GetID() const {
			return 1;
		}

	}
}