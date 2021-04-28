#include <Air.h>
#include <Engine\Core\Entrypoint.hpp>

class Sandbox : public engine::core::Application {
public:

	Sandbox() {

	}

	~Sandbox() {

	}
};

engine::core::Application* CreateApplication() {
	return new Sandbox();
}