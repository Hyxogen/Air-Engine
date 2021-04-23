#include <Air.h>
#include <Engine\Core\Entrypoint.hpp>

#include "TestEvent.hpp"
#include "TestEventHandler.hpp"

class Sandbox : public engine::core::Application {
public:

	Sandbox() {
		TestEventHandler handler;
		TestEvent event;
	}

	~Sandbox() {

	}
};

engine::core::Application* CreateApplication() {
	return new Sandbox();
}