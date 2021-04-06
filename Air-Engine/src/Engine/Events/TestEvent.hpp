#pragma once
#include "Event.hpp"

namespace engine {
	namespace events {

		class TestEvent : public Event {
		protected:
			unsigned int mMessage;
		public:
			TestEvent(unsigned int message);

			unsigned int GetID() const;

			inline unsigned int GetMessage() const { return mMessage; }
		};
	}
}