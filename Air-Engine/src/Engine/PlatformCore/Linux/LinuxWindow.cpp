#include "LinuxWindow.h"

namespace core {

	LinuxWindow::LinuxWindow(GenericApplication owning, std::wstring name, LinuxWindow* parent, int32 width = AIR_WINDOW_DEFAULT_WIDTH, int32 height = AIR_WINDOW_DEFAULT_HEIGHT)
		: GenericWindow(owning, name, parent, width, height) {
		
	}

	LinuxWindow::~LinuxWindow() {
		Destroy();
	}

	bool LinuxWindow::Init() {
		root = DefaultRootWindow()
	}

	void LinuxWindow::Update() {

	}

	bool LinuxWindow::ShouldClose() const {

	}

	void LinuxWindow::ShowWindow() {

	}

	void LinuxWindow::HideWindow() {

	}

	void LinuxWindow::SetTitle(std::wstring title) {

	}

	void LinuxWindow::Destroy() {

	}

}