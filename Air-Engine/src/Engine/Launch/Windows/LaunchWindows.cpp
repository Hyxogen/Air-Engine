#include <Windows.h>

#include "../../DataTypes.h"
#include "../Launch.h"

#include "../../PlatformCore/Windows/WindowsApplication.h"
#include "../../Util/Assert.h"

#include <iostream>

int32 WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, PWSTR cmdLine, int32 show) {
	std::cout << "LaunchWIndows" << std::endl;

	core::GenericApplication* app = new core::WindowsApplication(instance);
	app->Init();
	core::GenericWindow* window = app->MakeWindow();
	ASSERT(window->Init())
	window->ShowWindow();
	while (!window->ShouldClose()) {
		window->Update();
	}
	delete app;
	return 0;
}

int32 main(int argc, char** argv) {
	std::cout << "LaunchWIndows" << std::endl;
	return -1;
}