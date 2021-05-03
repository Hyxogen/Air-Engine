#include "airpch.h"
#pragma once

#ifdef AIR_PLATFORM_WINDOWS

engine::core::Application* CreateApplication();

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int nCmdShow) {
	auto application = CreateApplication();
	application->Run();
	delete application;
	return 0;
}
#endif