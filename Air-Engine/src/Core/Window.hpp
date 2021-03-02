#pragma once

namespace engine {
	namespace core {

		class Window {

			int mWidth, mHeight;
			const char* mName;
			void* mWindow;
			bool mShouldClose;

		public:

			Window(int width, int height, const char* name);

			~Window();

			bool Initialize();

			void Update();

			inline bool ShouldClose() const { return mShouldClose; }

			/*
			Window object z'n eigen loop geven
			 + Interface regelt alles
			 - Betekent dat de rest afhangt van de window op dit moment

			Functie geven voor het updaten van de window (zoals GLFW)
			 + Implementatie bepaalt waar en wanneer de window update
			 - Wordt niet 'automatisch' geregeld
			*/
		};

	}
}