#pragma once

namespace engine {
	namespace io {

		class Window {

		protected:
			int32 m_Width, m_Height;
			const wchar_t* m_Title;

			Window(const wchar_t* title, int32 width, int32 height) : m_Title(title), m_Width(width), m_Height(height) {}

		public:
			virtual ~Window() {};

			virtual bool Initialize() = 0;

			virtual void Update() = 0;

			virtual void Draw() = 0;

			virtual bool ShouldClose() const = 0;

			virtual void SetVisibility(int16 visibility) = 0;

			inline int32 GetWidth() const { return m_Width; }

			inline int32 GetHeight() const { return m_Height; }
		};

	}
}