#include "GameEngine.h"
#include "GameInstance.h"

extern core::GameInstance* CreateGameInstance();

namespace core {
	
	GameEngine::GameEngine(GenericPlatform* platform) : m_Platform(platform) {
	
	}
	
	GameEngine::~GameEngine() {
	
	}
	
	bool GameEngine::PreInit() {
		GameInstance* instance = CreateGameInstance();
		if (instance == nullptr)
			return false;
		SetGameInstance(instance);
		return true;
	
	}
	
	bool GameEngine::Init() {
		m_GameInstance->Init();
		return true;
	}

	
	void GameEngine::Start() {
	
	}
	
	void GameEngine::Tick() {
		m_GameInstance->Tick();
	}
	
	bool GameEngine::PreDeinit() {
		return true;
	}

	bool GameEngine::DeInit() {
		if (!m_GameInstance->DeInit())
			return false;
		return true;
	}
}