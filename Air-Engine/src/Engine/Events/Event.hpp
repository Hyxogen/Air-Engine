#pragma once

namespace engine {
	namespace events {

		class Event {
		protected:
			Event();
		public:
			const unsigned int mID;
		};

} }