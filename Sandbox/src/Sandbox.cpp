#include <Air.h>
#include <Engine\Core\Entrypoint.hpp>
#include <glad\wgl.h>
#include <glad\gl.h>

class Sandbox : public engine::core::Application {
public:

	Sandbox() {

	}

	~Sandbox() {

	}

	void Update() {
		Application::Update();
	}
};

engine::core::Application* CreateApplication() {
	return new Sandbox();
}