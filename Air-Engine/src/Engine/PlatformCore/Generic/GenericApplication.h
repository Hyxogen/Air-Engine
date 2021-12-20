#pragma once

#include "GenericWindow.h"

namespace core {

	class GenericApplication {

	protected:
		GenericApplication();

	public:

		virtual void Init();

		virtual ~GenericApplication() = 0;

		virtual GenericWindow* MakeWindow() = 0;

	};

}