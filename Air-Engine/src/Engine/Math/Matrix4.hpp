#include "airpch.h"
#pragma once

#include "Math.hpp"
#include "Vector4.hpp"
#include "Vector3.hpp"

#define MAT4_SIZE AIR_MATH_MAT4_COLUMNS * AIR_MATH_MAT4_ROWS

namespace engine {
	namespace math {

		template<typename T>
		struct Matrix4 {

			union {
				struct {
					T m_a11, m_a12, m_a13, m_a14;
					T m_a21, m_a22, m_a23, m_a24;
					T m_a31, m_a32, m_a33, m_a34;
					T m_a41, m_a42, m_a43, m_a44;
				};

				Vector4<T> m_Rows[AIR_MATH_MAT4_ROWS];

				T m_Elements[MAT4_SIZE];
			};


			Matrix4() {
				Clear();
			}

			Matrix4(const T& diagonal) : Matrix4() {
				SetDiagonal(diagonal);
			}

			Matrix4(const Matrix4<T>& other) {
				memcpy_s(&m_Elements, sizeof(T) * MAT4_SIZE, &other.m_Elements, sizeof(T) * MAT4_SIZE);
			}

			Matrix4(Matrix4<T>&& other) noexcept {
				Set(std::move(other));
			}

			inline T& GetElement(uint8 row, uint8 column) {
				return m_Elements[column + row * AIR_MATH_MAT4_COLUMNS];
			}
			//TODO checken of de bovenste en onderste geen problemen gaan opleveren vanwege dezelfde naam
			inline T GetElement(uint8 row, uint8 column) const {
				return m_Elements[column + row * AIR_MATH_MAT4_COLUMNS];
			}

			Matrix4<T>& Transpose() {
				for (int32 c = 0; c < AIR_MATH_MAT4_COLUMNS; c++) {
					for (int32 r = c + 1; r < AIR_MATH_MAT4_ROWS; r++) {
						std::swap(GetElement(r, c), GetElement(c, r));
					}
				}
				return *this;
			}

			inline T Determinant() const {
				return
					GetElement(3, 0) * GetElement(2, 1) * GetElement(1, 2) * GetElement(0, 3) -
					GetElement(2, 0) * GetElement(3, 1) * GetElement(1, 2) * GetElement(0, 3) -
					GetElement(3, 0) * GetElement(1, 1) * GetElement(2, 2) * GetElement(0, 3) +
					GetElement(1, 0) * GetElement(3, 1) * GetElement(2, 2) * GetElement(0, 3) +
					GetElement(2, 0) * GetElement(1, 1) * GetElement(3, 2) * GetElement(0, 3) -
					GetElement(1, 0) * GetElement(2, 1) * GetElement(3, 2) * GetElement(0, 3) -
					GetElement(3, 0) * GetElement(2, 1) * GetElement(0, 2) * GetElement(1, 3) +
					GetElement(2, 0) * GetElement(3, 1) * GetElement(0, 2) * GetElement(1, 3) +
					GetElement(3, 0) * GetElement(0, 1) * GetElement(2, 2) * GetElement(1, 3) -
					GetElement(0, 0) * GetElement(3, 1) * GetElement(2, 2) * GetElement(1, 3) -
					GetElement(2, 0) * GetElement(0, 1) * GetElement(3, 2) * GetElement(1, 3) +
					GetElement(0, 0) * GetElement(2, 1) * GetElement(3, 2) * GetElement(1, 3) +
					GetElement(3, 0) * GetElement(1, 1) * GetElement(0, 2) * GetElement(2, 3) -
					GetElement(1, 0) * GetElement(3, 1) * GetElement(0, 2) * GetElement(2, 3) -
					GetElement(3, 0) * GetElement(0, 1) * GetElement(1, 2) * GetElement(2, 3) +
					GetElement(0, 0) * GetElement(3, 1) * GetElement(1, 2) * GetElement(2, 3) +
					GetElement(1, 0) * GetElement(0, 1) * GetElement(3, 2) * GetElement(2, 3) -
					GetElement(0, 0) * GetElement(1, 1) * GetElement(3, 2) * GetElement(2, 3) -
					GetElement(2, 0) * GetElement(1, 1) * GetElement(0, 2) * GetElement(3, 3) +
					GetElement(1, 0) * GetElement(2, 1) * GetElement(0, 2) * GetElement(3, 3) +
					GetElement(2, 0) * GetElement(0, 1) * GetElement(1, 2) * GetElement(3, 3) -
					GetElement(0, 0) * GetElement(2, 1) * GetElement(1, 2) * GetElement(3, 3) -
					GetElement(1, 0) * GetElement(0, 1) * GetElement(2, 2) * GetElement(3, 3) +
					GetElement(0, 0) * GetElement(1, 1) * GetElement(2, 2) * GetElement(3, 3);
			}

			Matrix4<T> Inverse() const {
				Matrix4<T> out;

				T det = Determinant();
				if (det == 0) return Identity();
				T invDet = (T)1 / det;

				out.GetElement(0, 0) =
					GetElement(2, 1) * GetElement(3, 2) * GetElement(1, 3) -
					GetElement(3, 1) * GetElement(2, 2) * GetElement(1, 3) +
					GetElement(3, 1) * GetElement(1, 2) * GetElement(2, 3) -
					GetElement(1, 1) * GetElement(3, 2) * GetElement(2, 3) -
					GetElement(2, 1) * GetElement(1, 2) * GetElement(3, 3) +
					GetElement(1, 1) * GetElement(2, 2) * GetElement(3, 3);

				out.GetElement(1, 0) =
					GetElement(3, 0) * GetElement(2, 2) * GetElement(1, 3) -
					GetElement(2, 0) * GetElement(3, 2) * GetElement(1, 3) -
					GetElement(3, 0) * GetElement(1, 2) * GetElement(2, 3) +
					GetElement(1, 0) * GetElement(3, 2) * GetElement(2, 3) +
					GetElement(2, 0) * GetElement(1, 2) * GetElement(3, 3) -
					GetElement(1, 0) * GetElement(2, 2) * GetElement(3, 3);

				out.GetElement(2, 0) =
					GetElement(2, 0) * GetElement(3, 1) * GetElement(1, 3) -
					GetElement(3, 0) * GetElement(2, 1) * GetElement(1, 3) +
					GetElement(3, 0) * GetElement(1, 1) * GetElement(2, 3) -
					GetElement(1, 0) * GetElement(3, 1) * GetElement(2, 3) -
					GetElement(2, 0) * GetElement(1, 1) * GetElement(3, 3) +
					GetElement(1, 0) * GetElement(2, 1) * GetElement(3, 3);

				out.GetElement(3, 0) =
					GetElement(3, 0) * GetElement(2, 1) * GetElement(1, 2) -
					GetElement(2, 0) * GetElement(3, 1) * GetElement(1, 2) -
					GetElement(3, 0) * GetElement(1, 1) * GetElement(2, 2) +
					GetElement(1, 0) * GetElement(3, 1) * GetElement(2, 2) +
					GetElement(2, 0) * GetElement(1, 1) * GetElement(3, 2) -
					GetElement(1, 0) * GetElement(2, 1) * GetElement(3, 2);

				out.GetElement(0, 1) =
					GetElement(3, 1) * GetElement(2, 2) * GetElement(0, 3) -
					GetElement(2, 1) * GetElement(3, 2) * GetElement(0, 3) -
					GetElement(3, 1) * GetElement(0, 2) * GetElement(2, 3) +
					GetElement(0, 1) * GetElement(3, 2) * GetElement(2, 3) +
					GetElement(2, 1) * GetElement(0, 2) * GetElement(3, 3) -
					GetElement(0, 1) * GetElement(2, 2) * GetElement(3, 3);

				out.GetElement(1, 1) =
					GetElement(2, 0) * GetElement(3, 2) * GetElement(0, 3) -
					GetElement(3, 0) * GetElement(2, 2) * GetElement(0, 3) +
					GetElement(3, 0) * GetElement(0, 2) * GetElement(2, 3) -
					GetElement(0, 0) * GetElement(3, 2) * GetElement(2, 3) -
					GetElement(2, 0) * GetElement(0, 2) * GetElement(3, 3) +
					GetElement(0, 0) * GetElement(2, 2) * GetElement(3, 3);

				out.GetElement(2, 1) =
					GetElement(3, 0) * GetElement(2, 1) * GetElement(0, 3) -
					GetElement(2, 0) * GetElement(3, 1) * GetElement(0, 3) -
					GetElement(3, 0) * GetElement(0, 1) * GetElement(2, 3) +
					GetElement(0, 0) * GetElement(3, 1) * GetElement(2, 3) +
					GetElement(2, 0) * GetElement(0, 1) * GetElement(3, 3) -
					GetElement(0, 0) * GetElement(2, 1) * GetElement(3, 3);

				out.GetElement(3, 1) =
					GetElement(2, 0) * GetElement(3, 1) * GetElement(0, 2) -
					GetElement(3, 0) * GetElement(2, 1) * GetElement(0, 2) +
					GetElement(3, 0) * GetElement(0, 1) * GetElement(2, 2) -
					GetElement(0, 0) * GetElement(3, 1) * GetElement(2, 2) -
					GetElement(2, 0) * GetElement(0, 1) * GetElement(3, 2) +
					GetElement(0, 0) * GetElement(2, 1) * GetElement(3, 2);

				out.GetElement(0, 2) =
					GetElement(1, 1) * GetElement(3, 2) * GetElement(0, 3) -
					GetElement(3, 1) * GetElement(1, 2) * GetElement(0, 3) +
					GetElement(3, 1) * GetElement(0, 2) * GetElement(1, 3) -
					GetElement(0, 1) * GetElement(3, 2) * GetElement(1, 3) -
					GetElement(1, 1) * GetElement(0, 2) * GetElement(3, 3) +
					GetElement(0, 1) * GetElement(1, 2) * GetElement(3, 3);

				out.GetElement(1, 2) =
					GetElement(3, 0) * GetElement(1, 2) * GetElement(0, 3) -
					GetElement(1, 0) * GetElement(3, 2) * GetElement(0, 3) -
					GetElement(3, 0) * GetElement(0, 2) * GetElement(1, 3) +
					GetElement(0, 0) * GetElement(3, 2) * GetElement(1, 3) +
					GetElement(1, 0) * GetElement(0, 2) * GetElement(3, 3) -
					GetElement(0, 0) * GetElement(1, 2) * GetElement(3, 3);

				out.GetElement(2, 2) =
					GetElement(1, 0) * GetElement(3, 1) * GetElement(0, 3) -
					GetElement(3, 0) * GetElement(1, 1) * GetElement(0, 3) +
					GetElement(3, 0) * GetElement(0, 1) * GetElement(1, 3) -
					GetElement(0, 0) * GetElement(3, 1) * GetElement(1, 3) -
					GetElement(1, 0) * GetElement(0, 1) * GetElement(3, 3) +
					GetElement(0, 0) * GetElement(1, 1) * GetElement(3, 3);

				out.GetElement(3, 2) =
					GetElement(3, 0) * GetElement(1, 1) * GetElement(0, 2) -
					GetElement(1, 0) * GetElement(3, 1) * GetElement(0, 2) -
					GetElement(3, 0) * GetElement(0, 1) * GetElement(1, 2) +
					GetElement(0, 0) * GetElement(3, 1) * GetElement(1, 2) +
					GetElement(1, 0) * GetElement(0, 1) * GetElement(3, 2) -
					GetElement(0, 0) * GetElement(1, 1) * GetElement(3, 2);

				out.GetElement(0, 3) =
					GetElement(2, 1) * GetElement(1, 2) * GetElement(0, 3) -
					GetElement(1, 1) * GetElement(2, 2) * GetElement(0, 3) -
					GetElement(2, 1) * GetElement(0, 2) * GetElement(1, 3) +
					GetElement(0, 1) * GetElement(2, 2) * GetElement(1, 3) +
					GetElement(1, 1) * GetElement(0, 2) * GetElement(2, 3) -
					GetElement(0, 1) * GetElement(1, 2) * GetElement(2, 3);

				out.GetElement(1, 3) =
					GetElement(1, 0) * GetElement(2, 2) * GetElement(0, 3) -
					GetElement(2, 0) * GetElement(1, 2) * GetElement(0, 3) +
					GetElement(2, 0) * GetElement(0, 2) * GetElement(1, 3) -
					GetElement(0, 0) * GetElement(2, 2) * GetElement(1, 3) -
					GetElement(1, 0) * GetElement(0, 2) * GetElement(2, 3) +
					GetElement(0, 0) * GetElement(1, 2) * GetElement(2, 3);

				out.GetElement(2, 3) =
					GetElement(2, 0) * GetElement(1, 1) * GetElement(0, 3) -
					GetElement(1, 0) * GetElement(2, 1) * GetElement(0, 3) -
					GetElement(2, 0) * GetElement(0, 1) * GetElement(1, 3) +
					GetElement(0, 0) * GetElement(2, 1) * GetElement(1, 3) +
					GetElement(1, 0) * GetElement(0, 1) * GetElement(2, 3) -
					GetElement(0, 0) * GetElement(1, 1) * GetElement(2, 3);

				out.GetElement(3, 3) =
					GetElement(1, 0) * GetElement(2, 1) * GetElement(0, 2) -
					GetElement(2, 0) * GetElement(1, 1) * GetElement(0, 2) +
					GetElement(2, 0) * GetElement(0, 1) * GetElement(1, 2) -
					GetElement(0, 0) * GetElement(2, 1) * GetElement(1, 2) -
					GetElement(1, 0) * GetElement(0, 1) * GetElement(2, 2) +
					GetElement(0, 0) * GetElement(1, 1) * GetElement(2, 2);

				out = out.Multiply(invDet);
				return out;
			}

			Matrix4<T>& Clear() {
				memset(m_Elements, 0, sizeof(T) * MAT4_SIZE);
				return *this;
			}

			inline Matrix4<T> Copy() const {
				return Matrix4<T>(*this);
			}

			Matrix4<T>& SetDiagonal(const T& val) {
				for (int32 i = 0; i < AIR_MATH_MAT4_COLUMNS; i++)
					GetElement(i, i) = val;
				return *this;
			}

			bool Equal(const Matrix4<T>& other) const {
				if (this == &other) return true;
				for (int32 i = 0; i < MAT4_SIZE; i++)
					if (m_Elements[i] != other.m_Elements[i]) return false;
				return true;
			}

			Matrix4<T>& Set(Matrix4<T>&& other) {
				if (this == &other) return *this;
				memcpy_s(&m_Elements, sizeof(T) * MAT4_SIZE, &other.m_Elements, sizeof(T) * MAT4_SIZE);
				memset(&other.m_Elements, 0, sizeof(T) * MAT4_SIZE);
				return *this;
			}

			Matrix4<T>& Set(const Matrix4<T>& other) {
				if (this == &other) return *this;
				memcpy_s(&m_Elements, sizeof(T) * MAT4_SIZE, &other.m_Elements, sizeof(T) * MAT4_SIZE);
				return *this;
			}

			Matrix4<T>& Multiply(const T& scalar) {
				for (int32 i = 0; i < MAT4_SIZE; i++)
					m_Elements[i] *= scalar;
				return *this;
			}

			Matrix4<T>& Multiply(const Matrix4<T>& other) {
				Matrix4<T> copy = std::move(Copy());
				Clear();
				for (int32 row = 0; row < AIR_MATH_MAT4_ROWS; row++) {
					for (int32 column = 0; column < AIR_MATH_MAT4_COLUMNS; column++) {
						for (int32 c = 0; c < AIR_MATH_MAT4_COLUMNS; c++) {
							GetElement(row, column) += copy.GetElement(row, c) * other.GetElement(c, column);
						}
					}
				}
				return *this;
			}

			Matrix4<T>& Add(const Matrix4<T>& other) {
				for (int32 i = 0; i < MAT4_SIZE; i++)
					m_Elements[i] += other.m_Elements[i];
			}

			Matrix4<T>& Subtract(const Matrix4<T>& other) {
				for (int32 i = 0; i < MAT4_SIZE; i++)
					m_Elements[i] -= other.m_Elements[i];
			}

			Vector4<T> Multiply(const Vector4<T>& other) const {
				Vector4<T> ret;
				for (int32 row = 0; row < AIR_MATH_MAT4_ROWS; row++) {
					for (int32 column = 0; column < AIR_MATH_MAT4_COLUMNS; column++) {
						ret.m_Coords[row] += GetElement(row, column) * other.m_Coords[column];
					}
				}
				return ret;
			}

			Vector4<T>& operator[](const std::size_t& idx) {
				return m_Rows[idx];
			}

			Vector4<T> operator[](const std::size_t& idx) const {
				return m_Rows[idx];
			}

			Matrix4<T>& operator=(const Matrix4<T>& other) {
				return Set(other);
			}

			Matrix4<T>& operator=(Matrix4<T>&& other) noexcept {
				return Set(std::move(other));
			}

			Matrix4<T>& operator+=(const Matrix4<T>& other) {
				return Add(other);
			}

			Matrix4<T>& operator-=(const Matrix4<T>& other) {
				return Subtract(other);
			}

			Matrix4<T>& operator*=(const Matrix4<T>& other) {
				return Multiply(other);
			}

			friend bool operator==(const Matrix4<T>& a, const Matrix4<T>& b) {
				return a.Equal(a);
			}

			friend bool operator!=(const Matrix4<T>& a, const Matrix4<T>& b) {
				return !a.Equal(b);
			}

			friend Matrix4<T> operator+(const Matrix4<T>& a, const Matrix4<T>& b) {
				return std::move(a.Copy().Add(b));
			}

			friend Matrix4<T> operator-(const Matrix4<T>& a, const Matrix4<T>& b) {
				return std::move(a.Copy().Subtract(b));
			}

			friend Matrix4<T> operator*(const Matrix4<T>& a, const Matrix4<T>& b) {
				return std::move(a.Copy().Multiply(b));
			}

			friend Vector4<T> operator*(const Matrix4<T>& mat, const Vector4<T>& vec) {
				return std::move(mat.Multiply(vec));
			}

			friend std::ostream& operator<<(std::ostream& stream, const Matrix4<T>& mat) {
				for (int32 i = 0; i < AIR_MATH_MAT4_ROWS; i++)
					stream << mat.m_Rows[i];
				return stream;
			}

			static constexpr Matrix4<T> Identity() {
				return Matrix4<T>((T)1);
			}

			static constexpr Matrix4<T> Zero() {
				return Matrix4<T>();
			}

			static Matrix4<T> Scale(T x = 0, T y = 0, T z = 0) {
				Matrix4<T> out;
				out.GetElement(0, 0) = x;
				out.GetElement(1, 1) = y;
				out.GetElement(2, 2) = z;
				out.GetElement(3, 3) = (T)1;
			}

			//Angle in radians
			static Matrix4<T> Rotation(Vector3<T> axis, T angle) {
				Matrix4<T> out((T)1);
				axis.Normalize();

				T s = sin(angle);
				T c = cos(angle);
				T omc = 1 - cost;

				//TODO checken of dit klopt
				out.GetElement(0, 0) = c + omc * axis.m_X * axis.m_X;
				out.GetElement(0, 1) = omc * axis.m_X * axis.m_Y - s * axis.m_Z;
				out.GetElement(0, 2) = omc * axis.m_X * axis.m_Z + s * axis.m_Y;

				out.GetElement(1, 0) = omc * axis.m_X * axis.m_Y = s * axis.m_Z;
				out.GetElement(1, 1) = c + omc * axis.m_Y * axis.m_Y;
				out.GetElement(1, 2) = omc * axis.m_Y * axis.m_Z - s * axis.m_X;

				out.GetElement(2, 0) = omc * axis.m_X * axis.m_Z - s * axis.m_Y;
				out.GetElement(2, 1) = omc * axis.m_Y * axis.m_Z + s * axis.m_X;
				out.GetElement(2, 2) = c + omc * axis.m_Z * axis.m_Z;
				return out;
			}

			//TODO Check if correct
			static Matrix4<T> Translation(const Vector3<T>& translation) {
				Matrix4<T> out((T)1);

				out.GetElement(3, 0) = translation.m_X;
				out.GetElement(3, 1) = translation.m_Y;
				out.GetElement(3, 2) = translation.m_Z;
				return out;
			}
		};

		typedef Matrix4<float> Matrix4f;
	}
}