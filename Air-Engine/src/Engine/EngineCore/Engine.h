#pragma once

namespace core {

	class GameInstance;

	class Engine {

	protected:
		GameInstance* m_GameInstance;

		virtual ~Engine();

	public:
		//Returns true when no errors or the like ocurred otherwise false
		virtual bool PreInit();

		//Returns true when no errors or the like ocurred otherwise false
		virtual bool Init();

		virtual void Start();

		virtual void Tick();

		//Returns true when no errors or the like ocurred otherwise false
		virtual bool PreDeinit();

		//Returns true when no errors or the like ocurred otherwise false
		virtual bool DeInit();

		inline void SetGameInstance(GameInstance* instance) { m_GameInstance = instance; }
	};

}