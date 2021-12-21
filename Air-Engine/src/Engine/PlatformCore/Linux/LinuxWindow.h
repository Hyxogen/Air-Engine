#pragma once

#include "../Generic/GenericWindow.h"

#include <X11/X.h>
#include <X11/Xlib.h>

namespace core {

	class LinuxWindow : GenericWindow {

	protected:
		Window root;

	public:
		LinuxWindow(std::wstring name, LinuxWindow* parent, int32 width = AIR_WINDOW_DEFAULT_WIDTH, int32 height = AIR_WINDOW_DEFAULT_HEIGHT);

		virtual bool Init() override;

		virtual void Update() override;

		virtual bool ShouldClose() const override;

		virtual void ShowWindow() override;

		virtual void HideWindow() override;

		virtual void SetTitle(std::wstring title) override;
	private:
		virtual void Destroy();
	};

}