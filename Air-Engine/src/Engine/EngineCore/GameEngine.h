#pragma once

#include "Engine.h"

namespace core {

	class GenericPlatform;

	class GameEngine : public Engine {

	protected:
		const GenericPlatform* m_Platform;

	public:
		GameEngine(GenericPlatform *platform);

		virtual ~GameEngine() override;

		virtual bool PreInit() override;

		virtual bool Init() override;

		virtual void Start() override;

		virtual void Tick() override;

		virtual bool PreDeinit() override;

		virtual bool DeInit() override;

		inline const GenericPlatform* GetPlatform() const { return m_Platform; }
	};

}