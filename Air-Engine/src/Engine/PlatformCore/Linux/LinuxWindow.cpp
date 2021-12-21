#include "LinuxWindow.h"

namespace core {

	LinuxWindow::LinuxWindow(std::wstring name, LinuxWindow* parent, int32 width = AIR_WINDOW_DEFAULT_WIDTH, int32 height = AIR_WINDOW_DEFAULT_HEIGHT)
		: GenericWindow(name, parent, widht, height) {
		
	}

	LinuxWindow::~LinuxWindow() {
		Destroy();
	}

	bool LinuxWindow::Init() override {
		root = DefaultRootWindow()
	}

	void LinuxWindow::Update() override {

	}

	bool LinuxWindow::ShouldClose() const override {

	}

	void LinuxWindow::ShowWindow() override {

	}

	void LinuxWindow::HideWindow() override {

	}

	void LinuxWindow::SetTitle(std::wstring title) override {

	}

	void LinuxWindow::Destroy() {

	}

}