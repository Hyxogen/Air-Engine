#pragma once
#include "Event.hpp"

namespace engine {
	namespace events {

		class FooEvent : public Event {
		protected:
			unsigned int mMessage;
		public:
			FooEvent(unsigned int message);

			unsigned int GetID() const;

			inline unsigned int GetMessage() const { return mMessage; }
		};
	}
}