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
		NearEvent nearEvent;

		this->GetDispatcher()->Register(event.GetID(), &handler);
		this->GetDispatcher()->Register(event.GetID(), &impHandler);
		this->GetDispatcher()->Register(nearEvent.GetID(), &handler);
		this->GetDispatcher()->Register(nearEvent.GetID(), &impHandler);
		//this->GetDispatcher()->Remove(event.GetID(), &impHandler);
		this->GetDispatcher()->Dispatch(&nearEvent);
	}

	~Sandbox() {

	}
};

engine::core::Application* CreateApplication() {
	return new Sandbox();
}