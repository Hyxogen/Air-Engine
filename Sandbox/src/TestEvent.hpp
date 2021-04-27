#pragma once

#include "Engine\Events\Event.hpp"

class TestEvent : public engine::events::Event {
public:
	unsigned int GetID() const;
};

class NearEvent : public engine::events::Event {
public:
	unsigned int GetID() const;
};