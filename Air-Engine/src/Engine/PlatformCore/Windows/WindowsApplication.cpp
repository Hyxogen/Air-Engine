#include "WindowsApplication.h"

#include "WindowsWindow.h"

namespace core {

	LRESULT CALLBACK AppProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


	WindowsApplication::WindowsApplication() : WindowsApplication(NULL) {

	}

	WindowsApplication::WindowsApplication(HINSTANCE instance) : m_HInstance(instance) {
		if (m_HInstance == NULL)
			m_HInstance = GetModuleHandleA(0);
	}

	WindowsApplication::~WindowsApplication() {

	}

	bool WindowsApplication::Init() {
		if (RegisterWindowClass() == false)
			return false;
		return true;
	}

	GenericWindow* WindowsApplication::MakeWindow() {
		return new WindowsWindow(this, L"Test", nullptr);
	}

	bool WindowsApplication::RegisterWindowClass() {
		WNDCLASSEXW wndClass = { };

		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.lpfnWndProc = (WNDPROC)AppProc;
		wndClass.lpszClassName = L"DEFAULT";
		wndClass.hInstance = m_HInstance;

		if (::RegisterClassExW(&wndClass) == 0)
			return false;
		return true;
	}

	LRESULT CALLBACK AppProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}