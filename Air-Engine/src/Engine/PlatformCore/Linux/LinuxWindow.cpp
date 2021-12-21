#include "LinuxWindow.h"

namespace core {

	LinuxWindow::LinuxWindow(GenericApplication* owning, std::wstring name, LinuxWindow* parent, int32 width, int32 height)
		: GenericWindow(owning, name, parent, width, height) {
		
	}

	LinuxWindow::~LinuxWindow() {
		Destroy();
	}

	bool LinuxWindow::Init() {
		return true;
	}

	void LinuxWindow::Update() {

	}

	bool LinuxWindow::ShouldClose() const {
		return false;
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