#include "../../Air-Engine/src/Engine/Core/Application.hpp"
#include "../../Air-Engine/src/Engine/Core/Entrypoint.hpp"

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