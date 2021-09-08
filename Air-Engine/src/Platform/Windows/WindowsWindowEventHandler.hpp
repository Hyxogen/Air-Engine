#include "airpch.h"
#pragma once

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

			static int32 GetXCoord(LPARAM lParam);

			static int32 GetYCoord(LPARAM lParam);

			static bool IsRepeat(LPARAM lParam);

			static int32 GetScrollDelta(WPARAM wParam);

			static uint32 GetButtonMask(WPARAM wParam);

			static uint32 GetKeyCode(WPARAM wParam);

		protected:
			bool HandleEvent(WindowsWindowEvent* event);

			bool HandleKeyEvent(WindowsWindowEvent* event);

			bool HandleMouseEvent(WindowsWindowEvent* event);

			bool HandleOtherEvent(WindowsWindowEvent* event);
		};

	}
}