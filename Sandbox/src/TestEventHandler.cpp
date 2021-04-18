#include "TestEventHandler.hpp"

#include "Engine\Events\Event.hpp"
#include "Engine\Util\Logger\Logger.hpp"

bool TestEventHandler::OnEvent(engine::events::Event& event) {
	AIR_CORE_LOG_INFO("On event");
	return false;
}