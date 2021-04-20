#pragma once

#include "../Events/Event.hpp"
#include "../Events/EventListener.hpp"

namespace engine {
	namespace io {

		class Window;

		class Keyboard : public events::EventListener {
		protected:
			Window* m_Window;
		public:
			Keyboard(Window* window);

			virtual bool GetKeyDown(int keyCode) const;

			virtual bool GetKeyToggled(int keyCode) const;

			inline Window* GetWindow() const { return m_Window; }

			virtual bool OnEvent(events::Event& event);
		};
	}
}