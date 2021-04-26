#include "TestEventHandler.hpp"

#include "Engine\Events\Event.hpp"
#include "Engine\Util\Logger\Logger.hpp"

bool TestEventHandler::OnEvent(engine::events::Event* event) {
	AIR_CORE_LOG_INFO("On event");
	return false;
}

bool SuperImportantHandler::OnEvent(engine::events::Event* event) {
	AIR_CORE_LOG_INFO("Superimportant event is handled");
	return false;
}

//Check if monitor priority works
unsigned char SuperImportantHandler::GetPriority() const {
	return engine::events::PRIORITY_MONITOR;
}
