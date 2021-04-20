#pragma once

#include "../Events/Event.hpp"
#include "../Events/EventListener.hpp"

namespace engine {
	namespace io {

		class Window;

		class Keyboard : public events::EventListener {
			Window* m_Window;
		public:
			Keyboard(Window* window);

			virtual bool GetKeyDown(int keyCode) const = 0;

			virtual bool GetKeyToggled(int keyCode) const = 0;

			inline Window* GetWindow() const { return mWindow; }

			virtual bool OnEvent(events::Event& event);
		};
} }