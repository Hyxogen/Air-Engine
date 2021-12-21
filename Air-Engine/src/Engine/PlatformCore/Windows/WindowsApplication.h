#pragma once

#include "../Generic/GenericApplication.h"

#include <Windows.h>

namespace core {

	class WindowsApplication : public GenericApplication {

		HINSTANCE m_HInstance;

		WindowsApplication();
	public:
		WindowsApplication(HINSTANCE m_HInstance);

		virtual ~WindowsApplication() override;

		virtual bool Init() override;

		virtual GenericWindow* MakeWindow() override;

	protected:
		bool RegisterWindowClass();
	};

}