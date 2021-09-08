#pragma once
#include "Engine\Core\DataTypes.hpp"

namespace engine {
	namespace events {

		class Event {
		public:
			virtual uint32 GetID() const = 0;
		};

	}
}