#pragma once

#include "../Generic/GenericWindow.h"
#include "../../DataTypes.h"

#include <Windows.h>

namespace core {

	class WindowsApplication;

	class WindowsWindow : public GenericWindow {

		HINSTANCE m_HInstance;
		HWND m_Handle;

	public:
		WindowsWindow(WindowsApplication* owning, HINSTANCE instance, std::wstring name, GenericWindow* parent, int32 width, int32 height);

		WindowsWindow(WindowsApplication* owning, std::wstring name, GenericWindow* parent = 0, int32 width = AIR_WINDOW_DEFAULT_WIDTH, int32 height = AIR_WINDOW_DEFAULT_HEIGHT);

		virtual ~WindowsWindow();

		virtual bool Init() override;

		virtual void Update() override;

		virtual bool ShouldClose() const override;

		virtual void ShowWindow() override;

		virtual void HideWindow() override;

		virtual void SetTitle(std::wstring title) override;

		inline HWND GetHandle() const { return m_Handle; }

		inline HINSTANCE GetHInstance() const { return m_HInstance; }

	private:
		virtual void Destroy();
	};

}