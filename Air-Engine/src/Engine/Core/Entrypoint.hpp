#pragma once

#ifdef AIR_PLATFORM_WINDOWS
#include <windows.h>

engine::core::Application* CreateApplication();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	auto application = CreateApplication();
	application->Run();
	delete application;
	return 0;
}
#endif