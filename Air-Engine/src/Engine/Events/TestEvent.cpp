#include "TestEvent.hpp"

namespace engine {
	namespace events {

		TestEvent::TestEvent(unsigned int message) : mMessage(message) {

		}

		unsigned int TestEvent::GetID() const {
			return 1;
		}

	}
}