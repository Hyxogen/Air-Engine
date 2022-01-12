#pragma once

namespace air {

	class GameInstance {

	protected:
		GameInstance();

	public:
		virtual ~GameInstance();

		virtual bool Init();

		virtual void Tick();

		virtual bool DeInit();
	};

}