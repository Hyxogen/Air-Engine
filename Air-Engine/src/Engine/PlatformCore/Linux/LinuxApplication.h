#pragma once

#include "../Generic/GenericApplication.h"

#include <X11/X.h>
#include <X11/Xlib.h>

namespace core {

	class LinuxApplication : public GenericApplication {

	protected:
		Display* m_Display;

	public:
		LinuxApplication();

		virtual ~LinuxApplication() override;

		virtual bool Init() override;

		virtual GenericWindow* MakeWindow() override;

	};

}