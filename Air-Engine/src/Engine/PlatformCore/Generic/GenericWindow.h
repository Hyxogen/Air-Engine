#pragma once

#include <string>
#include "../../DataTypes.h"

#define AIR_WINDOW_DEFAULT_WIDTH 650
#define AIR_WINDOW_DEFAULT_HEIGHT 1020

namespace core {

	class GenericWindow {

	protected:
		std::wstring m_Title;
		int32 m_Width, m_Height;

		GenericWindow* m_Parent;

	public:
		GenericWindow(std::wstring name, GenericWindow* parent, int32 width = AIR_WINDOW_DEFAULT_WIDTH, int32 height = AIR_WINDOW_DEFAULT_HEIGHT);

		virtual ~GenericWindow();

		virtual bool Init() = 0;

		virtual void Update() = 0;

		virtual bool ShouldClose() const = 0;

		virtual void ShowWindow();

		virtual void HideWindow();

		virtual void SetTitle(std::wstring title);

		inline std::wstring GetTitle() const { return m_Title; }

		inline const GenericWindow* GetParent() const { return m_Parent; }

		inline int32 GetWidth() const { return m_Width; }

		inline int32 GetHeight() const { return m_Height; }
	};

}