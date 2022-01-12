#include <Engine\EngineCore\GameInstance.h>

class Sandbox : public air::GameInstance {
public:

	Sandbox() {

	}

	~Sandbox() {

	}

	void Update() {
		Application::Update();
	}
};

core::GameInstance* CreateGameInstance() {
	return new Sandbox();
}