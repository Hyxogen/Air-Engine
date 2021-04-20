#pragma once

namespace engine {
	namespace io {

		class Window;

		class Keyboard {
			Window* mWindow;
		public:
			Keyboard(Window* window);

			virtual bool GetKeyDown(int keyCode) const = 0;

			virtual bool GetKeyToggled(int keyCode) const = 0;

			inline Window* GetWindow() const { return mWindow; }
		};
} }