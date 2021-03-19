#pragma once

namespace platform {
	namespace windows {

		class Console {
			const wchar_t* mTitle;

		public:
			Console(const wchar_t* title = L"Console");
			
			~Console();

			//Returns false on no errors
			bool Initialize();

			bool SetTitle(const wchar_t* title);

			inline const wchar_t* GetTitle() const { return mTitle; }
		};

	}
}