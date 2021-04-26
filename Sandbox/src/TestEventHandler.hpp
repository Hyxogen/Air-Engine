#pragma once

#include "Engine\Events\EventListener.hpp"

class TestEventHandler : public engine::events::EventListener {

	bool OnEvent(engine::events::Event* event);

};

class SuperImportantHandler : public engine::events::EventListener {
	
	bool OnEvent(engine::events::Event* event);

	unsigned char GetPriority() const;
};