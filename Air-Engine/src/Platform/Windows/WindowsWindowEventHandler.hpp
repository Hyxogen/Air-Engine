#pragma once

#include <windows.h>

#include "../../Engine/Events/EventListener.hpp"

namespace platform {
	namespace windows {
		
		class WindowsWindow;
		class WindowsWindowEvent;
		
		class WindowsWindowEventHandler : public engine::events::EventListener {
		protected:
			WindowsWindow* m_Window;

		public:
			WindowsWindowEventHandler(WindowsWindow* window);

			virtual bool OnEvent(engine::events::Event* event);

			static int GetXCoord(LPARAM lParam);

			static int GetYCoord(LPARAM lParam);

			static bool IsRepeat(LPARAM lParam);

			static int GetScrollDelta(WPARAM wParam);

			static unsigned int GetButtonMask(WPARAM wParam);

			static unsigned int GetKeyCode(WPARAM wParam);

		protected:
			bool HandleEvent(WindowsWindowEvent* event);

			bool HandleKeyEvent(WindowsWindowEvent* event);

			bool HandleMouseEvent(WindowsWindowEvent* event);

			bool HandleOtherEvent(WindowsWindowEvent* event);
		};

	}
}