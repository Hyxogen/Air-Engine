#include <Air.h>
#include <Engine\Core\Entrypoint.hpp>

#include "TestEvent.hpp"
#include "TestEventHandler.hpp"

class Sandbox : public engine::core::Application {
public:

	Sandbox() {
		TestEventHandler handler;
		SuperImportantHandler impHandler;
		TestEvent event;

		this->GetDispatcher()->Register(event.GetID(), &handler);
		this->GetDispatcher()->Register(event.GetID(), &impHandler);
		this->GetDispatcher()->Dispatch(&event);
	}

	~Sandbox() {

	}
};

engine::core::Application* CreateApplication() {
	return new Sandbox();
}