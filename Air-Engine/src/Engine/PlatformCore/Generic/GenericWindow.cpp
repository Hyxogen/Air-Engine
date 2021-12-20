#include "GenericWindow.h"

namespace core {

	GenericWindow::GenericWindow(std::wstring name, GenericWindow* parent, int32 width, int32 height) : m_Title(name), m_Parent(parent), m_Width(width), m_Height(height) {

	}

	GenericWindow::~GenericWindow() {
	
	}
	
	void GenericWindow::ShowWindow() {
	
	}
	
	void GenericWindow::HideWindow() {
	
	}
	
	void GenericWindow::SetTitle(std::wstring title) {
	
	}
}