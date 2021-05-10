#include "airpch.h"
#pragma once

#include "Math.hpp"
#include "Vector2.hpp"

namespace engine {
	namespace math {

		template<typename T>
		struct Matrix2 {
			union {
				#ifdef AIR_MATH_ROWMAJOR
				struct {
					Vector2<T> m_Rows[2];
				};

				struct {
					T m_a11, m_a12;
					T m_a21, m_a22;
				};

				#else
				struct {
					Vector2<T> m_Columns[2];
				};

				struct {
					T m_a11, m_a21;
					T m_a12, m_a22;
				};

				#endif

				T m_Elements[4];
			};

			Matrix2() {
				memset(m_Elements, 0, sizeof(T) * 4);
			}

		};

	}
}