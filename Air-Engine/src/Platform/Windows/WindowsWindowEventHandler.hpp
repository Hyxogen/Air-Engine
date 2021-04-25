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

			virtual bool OnEvent(engine::events::Event& event);

		protected:
			bool HandleEvent(WindowsWindowEvent& event);

			bool HandleKeyEvent(WindowsWindowEvent& event);

			bool HandleMouseEvent(WindowsWindowEvent& event);

			bool HandleOtherEvent(WindowsWindowEvent& event);
		};

	}
}