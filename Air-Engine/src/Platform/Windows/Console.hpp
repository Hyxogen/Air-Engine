#pragma once

namespace platform {
	namespace windows {

		class Console {
			const wchar_t* m_Title;

		public:
			Console(const wchar_t* title = L"Console");
			
			~Console();

			//Returns false on no errors
			bool Initialize();

			//Return false on no errors
			bool SetTitle(const wchar_t* title);

			inline const wchar_t* GetTitle() const { return m_Title; }
		};

	}
}