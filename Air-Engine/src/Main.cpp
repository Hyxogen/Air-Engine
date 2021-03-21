#ifndef UNICODE
#define UNICODE
#endif 
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <iostream>
#include <GL/glew.h>
#include "Platform\Windows\WindowsWindow.hpp"
#include "Platform/Windows/GLContextAdapter.hpp"
#include "Platform/Windows/Console.hpp"
#include "Engine/Core/Util/Logger/Logger.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    using namespace engine;
    using namespace core;
    using namespace platform;
    using namespace windows;
    using namespace util;
    Console* console = new Console();
    if (console->Initialize()) {
        return -1;
    }

    WindowsWindow* window = new WindowsWindow(500, 500, L"Test");
    GLContextAdapter* contextAdapter = new GLContextAdapter(window, 3, 0);

    AIR_CORE_ERR_IF(window->Initialize(), "Failed to initialize window");
    AIR_CORE_ERR_IF(contextAdapter->Initialize(), "Failed to setup OpenGL context");

    window->SetVisibility(AIR_W_SHOW);

    GLenum err;

    AIR_CORE_LOG_INFO("Starting main loop...");
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
        if ((err = glGetError()) != GL_NO_ERROR) {
            break;
        }
        window->Update();
    }
    AIR_CORE_LOG_INFO("Shutting down engine...");

    delete console;
    delete contextAdapter;
    delete window;

    return 0;
}

/*
Ik denk toch niet dat de window class opengl functionaliteit moet regelen, gewoon een opengl helper class maken die dmv een WindowsWindow een opengl context kan maken

Ik denk dat de WindowsWindow class niet in charge moet zijn van OpenGL context creation, maar alleen het maken van een Window via de Win32API (Denk aan SOLID)

Kijken of Windows.hpp geen Windows.cpp nodig heeft omdat ik het puur virtueel wil maken
*/