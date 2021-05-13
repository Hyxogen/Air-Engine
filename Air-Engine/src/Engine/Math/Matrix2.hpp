#include "airpch.h"
#pragma once

#include "Math.hpp"
#include "Vector2.hpp"

namespace engine {
	namespace math {

		static constexpr unsigned char MAT2_SIZE = AIR_MATH_MAT2_COLUMNS * AIR_MATH_MAT2_ROWS;
		template<typename T>
		struct Matrix2 {
			union {
				#ifdef AIR_MATH_ROWMAJOR
				struct {
					Vector2<T> m_Rows[AIR_MATH_MAT2_ROWS];
				};

				struct {
					T m_a11, m_a12;
					T m_a21, m_a22;
				};

				#else

				struct {
					T m_a11, m_a21;
					T m_a12, m_a22;
				};

				struct {
					Vector2<T> m_Columns[AIR_MATH_MAT2_COLUMNS];
				};
				#endif

				T m_Elements[MAT2_SIZE];
			};

			Matrix2() {
				Clear();
			}

			Matrix2(const T& diagonal) : Matrix2() {
				SetDiagonal(diagonal);
			}

			Matrix2(const Matrix2<T>& other) {
				memcpy_s(&m_Elements, sizeof(T) * MAT2_SIZE, &other.m_Elements, sizeof(T) * MAT2_SIZE);
			}

			inline T& GetElement(unsigned char row, unsigned char column) {
				#ifdef AIR_MATH_ROWMAJOR
				return m_Elements[column + row * AIR_MATH_MAT2_COLUMNS];
				#else
				return m_Elements[row + column * AIR_MATH_MAT2_COLUMNS];
				#endif
			}

			inline T GetElementCopy(unsigned char row, unsigned char column) const {
				#ifdef AIR_MATH_ROWMAJOR
				return m_Elements[column + row * AIR_MATH_MAT2_COLUMNS];
				#else
				return m_Elements[row + column * AIR_MATH_MAT2_COLUMNS];
				#endif
			}

			/*
			[x][o][o][o]
			[o][x][o][o]
			[o][o][x][o]
			[o][o][o][x]
			*/
			Matrix2<T>& Transpose() {
				for (int c = 0; c < AIR_MATH_MAT2_COLUMNS; c++) {
					for (int r = c + 1; r < AIR_MATH_MAT2_ROWS; r++) {
						std::swap(GetElement(r, c), GetElement(c, r));
					}
				}
				return *this;
			}

			/*
			m11 * m22 - m12 * m21
			*/
			inline T Determinant() const {
				return ((GetElementCopy(0, 0) * GetElementCopy(1, 1)) - (GetElementCopy(0, 1) * GetElementCopy(1, 0)));
			}

			Matrix2<T>& Inverse() {
				T det = std::move(Determinant());

				if (det == 0)
					return MakeIdentity();

				T temp = GetElement(1, 1) / det;

				GetElement(1, 1) = GetElement(0, 0) / det;
				GetElement(0, 0) = temp;

				GetElement(0, 1) = -GetElement(0, 1) / det;
				GetElement(1, 0) = -GetElement(1, 0) / det;
				return *this;
			}

			Matrix2<T>& MakeIdentity() {
				SetDiagonal((T)1);
				return *this;
			}

			Matrix2<T>& Clear() {
				memset(m_Elements, 0, sizeof(T) * MAT2_SIZE);
				return *this;
			}

			inline Matrix2<T> Copy() const {
				return Matrix2<T>(*this);
			}

			Matrix2<T>& SetDiagonal(const T& val) {
				for (int i = 0; i < AIR_MATH_MAT2_COLUMNS; i++)
					GetElement(i, i) = val;
				return *this;
			}

			bool Equal(const Matrix2<T>& other) const {
				if (this == &other) return true;
				for (int i = 0; i < MAT2_SIZE; i++)
					if (m_Elements[i] != other.m_Elements[i]) return false;
				return true;
			}

			Matrix2<T>& Multiply(const T& scalar) {
				for (int i = 0; i < MAT2_SIZE; i++)
					m_Elements[i] *= scalar;
				return *this;
			}

			Matrix2<T>& Multiply(const Matrix2<T>& other) {
				Matrix2<T> copy = std::move(Copy());
				Clear();
				for (int row = 0; row < AIR_MATH_MAT2_ROWS; row++) {
					for (int column = 0; column < AIR_MATH_MAT2_COLUMNS; column++) {
						for (int c = 0; c < AIR_MATH_MAT2_COLUMNS; c++) {
							GetElement(row, column) += copy.GetElement(row, c) * other.GetElementCopy(c, column);
						}
					}
				}
				return *this;
			}

			Matrix2<T>& Add(const Matrix2<T>& other) {
				for (int i = 0; i < MAT2_SIZE; i++)
					m_Elements[i] += other.m_Elements[i];
			}

			Matrix2<T>& Subtract(const Matrix2<T>& other) {
				for (int i = 0; i < MAT2_SIZE; i++)
					m_Elements[i] -= other.m_Elements[i];
			}

			#ifdef AIR_MATH_ROWMAJOR
			Vector2<T> Multiply(const Vector2<T>& other) {
				Vector2<T> ret = other.Copy();
				for (int row = 0; row < AIR_MATH_MAT2_ROWS; row++) {
					for (int column = 0; column < AIR_MATH_MAT2_COLUMNS; column++) {
						ret.m_Coords[row] = other.Dot(m_Rows[row]);
					}
				}
			}
			#endif

			static constexpr Matrix2<T> Identity() {
				return Matrix2<T>((T)1);
			}

			static constexpr Matrix2<T> Zero() {
				return Matrix2<T>();
			}
		};

		typedef Matrix2<float> Matrix2f;
	}
}