#ifndef UNICODE
#define UNICODE
#endif 
#include <windows.h>
#include "Core/Window.hpp"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    using namespace engine;
    using namespace core;

    Window* window = new Window(500, 500, "New window");

    window->Initialize();

    while (!window->ShouldClose()) {
        window->Update();
    }

    delete window;

    return 0;
}