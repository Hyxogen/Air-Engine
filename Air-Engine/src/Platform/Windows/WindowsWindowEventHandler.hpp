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
			void HandleKeyEvent(WindowsWindowEvent& event);

			void HandleMouseEvent(WindowsWindowEvent& event);

			void HandleOtherEvent(WindowsWindowEvent& event);
		};

	}
}