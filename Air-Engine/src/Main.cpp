#ifndef UNICODE
#define UNICODE
#endif 
#include <windows.h>
#include "Core/WindowsWindow.hpp"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    using namespace engine;
    using namespace core;

    WindowsWindow* window = new WindowsWindow(500, 500, L"Test");

    if (!window->Initialize()) {
        return -1;
    }
    window->SetVisibility(AIR_W_SHOW);

    while (!window->ShouldClose()) {
        window->Update();
    }

    delete window;

    return 0;
}

/*
Window class een soort OpenGL context geven
+ Makkelijk weggestopt
- Is niet window's verantwoordlijkheid

Basic window interface maken maar ook OpenGLWindow classes
+ Verantwoordlijkheid verbeterd
- Te ingewikkeld?
*/