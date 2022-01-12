#include "WindowsWindow.h"
#include "../../Util/Assert.h"

#include "WindowsApplication.h"

namespace core {

	WindowsWindow::WindowsWindow(WindowsApplication* owning, HINSTANCE instance, std::wstring name, GenericWindow* parent, int32 width, int32 height) : GenericWindow(owning, name, parent, width, height), m_HInstance(instance), m_Handle(0) {
	}

	WindowsWindow::WindowsWindow(WindowsApplication* owning, std::wstring name, GenericWindow* parent, int32 width, int32 height) : WindowsWindow(owning, owning->GetHInstance(), name, parent, width, height) {
	}

	WindowsWindow::~WindowsWindow() {
		Destroy();
	}

	bool WindowsWindow::Init() {
		if (m_Parent)
			m_Handle = CreateWindowExW(CS_OWNDC, L"DEFAULT", L"DEFAULT", WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, ((WindowsWindow*)m_Parent)->GetHandle(), 0, GetHInstance(), 0);
		else
			m_Handle = CreateWindowExW(CS_OWNDC, L"DEFAULT", L"DEFAULT", WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, GetHInstance(), 0);
		if (m_Handle == 0)
			return false;
		return true;
	}

	void WindowsWindow::Update() {
		MSG msg;
		while (PeekMessageW(&msg, m_Handle, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}

	//TODO Get status
	bool WindowsWindow::ShouldClose() const {
		return false;
	}

	void WindowsWindow::ShowWindow() {
		::ShowWindow(m_Handle, SW_SHOW);
	}

	void WindowsWindow::HideWindow() {
		::ShowWindow(m_Handle, SW_HIDE);
	}

	void WindowsWindow::SetTitle(std::wstring title) {
		m_Title = title;
		ASSERT(SetWindowTextW(m_Handle, title.c_str()))
	}

	void WindowsWindow::Destroy() {
		DestroyWindow(m_Handle);
	}

	
}