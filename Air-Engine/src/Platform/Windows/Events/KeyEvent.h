#pragma once

#include "../../../Engine/Events/Event.hpp"

namespace platform {
	namespace windows {

		class WindowsWindow;

		class KeyEvent : public engine::events::Event {
			WindowsWindow* mWindow;
			const unsigned int mEvent, mParam;
		public:
			//wParam could perhaps not work on 64bit platforms
			KeyEvent(WindowsWindow* window, unsigned int event, unsigned int wParam);

			unsigned int GetID() const;

			inline WindowsWindow* GetWindow() const { return mWindow; }

			inline unsigned int GetEvent() const { return mEvent; }

			inline unsigned int GetWParam() const { return mParam; }
		};

	}
}