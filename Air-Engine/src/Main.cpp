#ifndef UNICODE
#define UNICODE
#endif 
#include <GL/glew.h>
#include "Platform\Windows\WindowsWindow.hpp"
#include "Platform/Windows/GLContextAdapter.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    using namespace engine;
    using namespace core;
    using namespace platform;
    using namespace windows;

    WindowsWindow* window = new WindowsWindow(500, 500, L"Test");
    GLContextAdapter* contextAdapter = new GLContextAdapter(window);

    if (!window->Initialize()) {
        return -1;
    }

    if (contextAdapter->Initialize()) {
        return -1;
    }

    window->SetVisibility(AIR_W_SHOW);

    while (!window->ShouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2i(0, 1);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2i(-1, -1);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2i(1, -1);
        glEnd();
        glFlush();
        window->Update();
    }

    delete contextAdapter;
    delete window;

    return 0;
}

/*
Ik denk toch niet dat de window class opengl functionaliteit moet regelen, gewoon een opengl helper class maken die dmv een WindowsWindow een opengl context kan maken

Ik denk dat de WindowsWindow class niet in charge moet zijn van OpenGL context creation, maar alleen het maken van een Window via de Win32API (Denk aan SOLID)

Kijken of Windows.hpp geen Windows.cpp nodig heeft omdat ik het puur virtueel wil maken
*/