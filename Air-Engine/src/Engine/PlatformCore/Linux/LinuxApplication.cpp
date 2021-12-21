#include "LinuxApplication.h"

#include "../../Util/Assert.h"

namespace core {

	LinuxApplication::LinuxApplication() {

	}

	LinuxApplication::~LinuxApplication() {

	}

	bool LinuxApplication::Init() {
		m_Display = XOpenDisplay(0);

		ASSERT(m_Display);
	}

	LinuxApplication::MakeWindow() {

	}

}