#ifndef UNICODE
#define UNICODE
#endif 
#include <windows.h>
#include "Core/Window.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    using namespace engine;
    using namespace core;

    Window* window = new Window(500, 500, "New window");

    window->Initialize();
    window->SetVisibility(AIR_W_SHOW);

    while (!window->ShouldClose()) {
        window->Update();
    }

    delete window;

    return 0;
}