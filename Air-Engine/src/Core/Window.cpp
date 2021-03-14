#include "Window.hpp"

namespace engine {
	namespace core {

		Window::Window(const wchar_t* title, int width, int height) : mTitle(title), mWidth(width), mHeight(height) {

		}

		Window::~Window() {

		}
	}
}