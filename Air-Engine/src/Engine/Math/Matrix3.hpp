#include "airpch.h"
#pragma once

#include "Math.hpp"
#include "Vector3.hpp"

#define MAT3_SIZE AIR_MATH_MAT3_COLUMNS * AIR_MATH_MAT3_ROWS

namespace engine {
	namespace math {

		/// <summary>
		/// Row major AIR_MATH_MAT3_COLUMNS x AIR_MATH_MAT3_ROWS matrix (usually 3)
		/// </summary>
		/// <typeparam name="T"></typeparam>
		template<typename T>
		struct Matrix3 {
			union {
				struct {
					T m_a11, m_a12, m_a13;
					T m_a21, m_a22, m_a23;
					T m_a31, m_a32, m_a33;
				};

				Vector3<T> m_Rows[AIR_MATH_MAT3_ROWS];

				T m_Elements[MAT3_SIZE];
			};

			Matrix3() {
				Clear();
			}

			Matrix3(const T& diagonal) : Matrix3() {
				SetDiagonal(diagonal);
			}

			Matrix3(const Matrix3<T>& other) {
				memcpy_s(&m_Elements, sizeof(T) * MAT3_SIZE, &other.m_Elements, sizeof(T) * MAT3_SIZE);
			}

			Matrix3(Matrix3<T>&& other) noexcept {
				Set(std::move(other));
			}

			inline T& GetElement(uint8 row, uint8 column) {
				return m_Elements[column + row * AIR_MATH_MAT3_COLUMNS];
			}

			inline T GetElement(uint8 row, uint8 column) const {
				return m_Elements[column + row * AIR_MATH_MAT3_COLUMNS];
			}

			Matrix3<T>& Transpose() {
				for (int32 c = 0; c < AIR_MATH_MAT3_COLUMNS; c++) {
					for (int32 r = c + 1; r < AIR_MATH_MAT3_ROWS; r++) {
						std::swap(GetElement(r, c), GetElement(c, r));
					}
				}
				return *this;
			}

			inline T Determinant() const {
				return
					GetElement(0, 0) * GetElement(1, 1) * GetElement(2, 2) -
					GetElement(0, 0) * GetElement(1, 2) * GetElement(2, 1) -
					GetElement(0, 1) * GetElement(1, 0) * GetElement(2, 2) +
					GetElement(0, 1) * GetElement(1, 2) * GetElement(2, 0) +
					GetElement(0, 2) * GetElement(1, 0) * GetElement(2, 1) -
					GetElement(0, 2) * GetElement(1, 1) * GetElement(2, 0);
			}

			Matrix3<T> Inverse() const {
				Matrix3<T> out;
				T det = std::move(Determinant());

				if (det == 0)
					return Identity();

				T detInv = (T)1 / det;
				out.GetElement(0, 0) = GetElement(1, 1) * GetElement(2, 2) - GetElement(1, 2) * GetElement(2, 1);
				out.GetElement(0, 1) = -GetElement(0, 1) * GetElement(2, 2) + GetElement(0, 2) * GetElement(2, 1);
				out.GetElement(0, 2) = GetElement(0, 1) * GetElement(1, 2) - GetElement(0, 2) * GetElement(1, 1);

				out.GetElement(1, 0) = -GetElement(1, 0) * GetElement(2, 2) + GetElement(1, 2) * GetElement(2, 0);
				out.GetElement(1, 1) = GetElement(0, 0) * GetElement(2, 2) - GetElement(0, 2) * GetElement(2, 0);
				out.GetElement(1, 2) = -GetElement(0, 0) * GetElement(1, 2) + GetElement(0, 2) * GetElement(1, 0);

				out.GetElement(2, 0) = GetElement(1, 0) * GetElement(2, 1) - GetElement(1, 1) * GetElement(2, 0);
				out.GetElement(2, 1) = -GetElement(0, 0) * GetElement(2, 1) + GetElement(0, 1) * GetElement(2, 0);
				out.GetElement(2, 2) = GetElement(1, 1) * GetElement(0, 0) - GetElement(0, 1) * GetElement(1, 0);

				out.Multiply(detInv);
				return out;
			}

			Matrix3<T>& Clear() {
				memset(m_Elements, 0, sizeof(T) * MAT3_SIZE);
				return *this;
			}

			inline Matrix3<T> Copy() const {
				return Matrix3<T>(*this);
			}

			Matrix3<T>& SetDiagonal(const T& val) {
				for (int32 i = 0; i < AIR_MATH_MAT3_COLUMNS; i++)
					GetElement(i, i) = val;
				return *this;
			}

			bool Equal(const Matrix3<T>& other) const {
				if (this == &other) return true;
				for (int32 i = 0; i < MAT3_SIZE; i++)
					if (m_Elements[i] != other.m_Elements[i]) return false;
				return true;
			}

			Matrix3<T>& Set(Matrix3<T>&& other) {
				if (this == &other) return *this;
				memcpy_s(&m_Elements, sizeof(T) * MAT3_SIZE, &other.m_Elements, sizeof(T) * MAT3_SIZE);
				memset(&other.m_Elements, 0, sizeof(T) * MAT3_SIZE);
				return *this;
			}

			Matrix3<T>& Set(const Matrix3<T>& other) {
				if (this == &other) return *this;
				memcpy_s(&m_Elements, sizeof(T) * MAT3_SIZE, &other.m_Elements, sizeof(T) * MAT3_SIZE);
				return *this;
			}

			Matrix3<T>& Multiply(const T& scalar) {
				for (int32 i = 0; i < MAT3_SIZE; i++)
					m_Elements[i] *= scalar;
				return *this;
			}

			Matrix3<T>& Multiply(const Matrix3<T>& other) {
				Matrix3<T> copy = std::move(Copy());
				Clear();
				for (int32 row = 0; row < AIR_MATH_MAT3_ROWS; row++) {
					for (int32 column = 0; column < AIR_MATH_MAT3_COLUMNS; column++) {
						for (int32 c = 0; c < AIR_MATH_MAT3_COLUMNS; c++) {
							GetElement(row, column) += copy.GetElement(row, c) * other.GetElement(c, column);
						}
					}
				}
				return *this;
			}

			Matrix3<T>& Add(const Matrix3<T>& other) {
				for (int32 i = 0; i < MAT3_SIZE; i++)
					m_Elements[i] += other.m_Elements[i];
			}

			Matrix3<T>& Subtract(const Matrix3<T>& other) {
				for (int32 i = 0; i < MAT3_SIZE; i++)
					m_Elements[i] -= other.m_Elements[i];
			}

			Vector3<T> Multiply(const Vector3<T>& other) const {
				Vector3<T> ret;
				for (int32 row = 0; row < AIR_MATH_MAT3_ROWS; row++) {
					for (int32 column = 0; column < AIR_MATH_MAT3_COLUMNS; column++) {
						ret.m_Coords[row] += GetElement(row, column) * other.m_Coords[column];
					}
				}
				return ret;
			}

			Vector3<T>& operator[](const std::size_t& idx) {
				return m_Rows[idx];
			}

			Vector3<T> operator[](const std::size_t& idx) const {
				return m_Rows[idx];
			}

			Matrix3<T>& operator=(const Matrix3<T>& other) {
				return Set(other);
			}

			Matrix3<T>& operator=(Matrix3<T>&& other) noexcept {
				return Set(std::move(other));
			}

			Matrix3<T>& operator+=(const Matrix3<T>& other) {
				return Add(other);
			}

			Matrix3<T>& operator-=(const Matrix3<T>& other) {
				return Subtract(other);
			}

			Matrix3<T>& operator*=(const Matrix3<T>& other) {
				return Multiply(other);
			}

			friend bool operator==(const Matrix3<T>& a, const Matrix3<T>& b) {
				return a.Equal(a);
			}

			friend bool operator!=(const Matrix3<T>& a, const Matrix3<T>& b) {
				return !a.Equal(b);
			}

			friend Matrix3<T> operator+(const Matrix3<T>& a, const Matrix3<T>& b) {
				return std::move(a.Copy().Add(b));
			}

			friend Matrix3<T> operator-(const Matrix3<T>& a, const Matrix3<T>& b) {
				return std::move(a.Copy().Subtract(b));
			}

			friend Matrix3<T> operator*(const Matrix3<T>& a, const Matrix3<T>& b) {
				return std::move(a.Copy().Multiply(b));
			}

			friend Vector3<T> operator*(const Matrix3<T>& mat, const Vector3<T>& vec) {
				return std::move(mat.Multiply(vec));
			}

			friend std::ostream& operator<<(std::ostream& stream, const Matrix3<T>& mat) {
				for (int32 i = 0; i < AIR_MATH_MAT3_ROWS; i++)
					stream << mat.m_Rows[i];
				return stream;
			}

			static constexpr Matrix3<T> Identity() {
				return Matrix3<T>((T)1);
			}

			static constexpr Matrix3<T> Zero() {
				return Matrix3<T>();
			}
		};

		typedef Matrix3<float> Matrix3f;
	}
}