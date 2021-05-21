#include "airpch.h"
#pragma once

#include "Math.hpp"
#include "Vector2.hpp"

namespace engine {
	namespace math {

		static constexpr unsigned char MAT2_SIZE = AIR_MATH_MAT2_COLUMNS * AIR_MATH_MAT2_ROWS;

		/// <summary>
		/// Row major AIR_MATH_MAT2_COLUMNS x AIR_MATH_MAT2_ROWS matrix (usually 2)
		/// </summary>
		/// <typeparam name="T"></typeparam>
		template<typename T>
		struct Matrix2 {
			union {
				struct {
					T m_a11, m_a12;
					T m_a21, m_a22;
				};

				Vector2<T> m_Rows[AIR_MATH_MAT2_ROWS];

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

			Matrix2(Matrix2<T>&& other) noexcept {
				Set(std::move(other));
			}

			inline T& GetElement(unsigned char row, unsigned char column) {
				return m_Elements[column + row * AIR_MATH_MAT2_COLUMNS];
			}

			inline T GetElement(unsigned char row, unsigned char column) const {
				return m_Elements[column + row * AIR_MATH_MAT2_COLUMNS];
			}

			Matrix2<T>& Transpose() {
				for (int c = 0; c < AIR_MATH_MAT2_COLUMNS; c++) {
					for (int r = c + 1; r < AIR_MATH_MAT2_ROWS; r++) {
						std::swap(GetElement(r, c), GetElement(c, r));
					}
				}
				return *this;
			}

			inline T Determinant() const {
				return ((GetElement(0, 0) * GetElement(1, 1)) - (GetElement(0, 1) * GetElement(1, 0)));
			}

			Matrix2<T> Inverse() const {
				Matrix2<T> out;
				T det = std::move(Determinant());

				if (det == 0)
					return Identity();

				out.GetElement(1, 1) = GetElement(0, 0) / det;
				out.GetElement(0, 0) = GetElement(1, 1) / det;

				out.GetElement(0, 1) = -GetElement(0, 1) / det;
				out.GetElement(1, 0) = -GetElement(1, 0) / det;
				return out;
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

			Matrix2<T>& Set(Matrix2<T>&& other) {
				if (this == &other) return *this;
				memcpy_s(&m_Elements, sizeof(T) * MAT2_SIZE, &other.m_Elements, sizeof(T) * MAT2_SIZE);
				memset(&other.m_Elements, 0, sizeof(T) * MAT2_SIZE);
				return *this;
			}

			Matrix2<T>& Set(const Matrix2<T>& other) {
				if (this == &other) return *this;
				memcpy_s(&m_Elements, sizeof(T) * MAT2_SIZE, &other.m_Elements, sizeof(T) * MAT2_SIZE);
				return *this;
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
							GetElement(row, column) += copy.GetElement(row, c) * other.GetElement(c, column);
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

			Vector2<T> Multiply(const Vector2<T>& other) const {
				Vector2<T> ret;
				for (int row = 0; row < AIR_MATH_MAT2_ROWS; row++) {
					for (int column = 0; column < AIR_MATH_MAT2_COLUMNS; column++) {
						ret.m_Coords[row] += GetElement(row, column) * other.m_Coords[column];
					}
				}
				return ret;
			}

			Vector2<T>& operator[](const std::size_t& idx) {
				return m_Rows[idx];
			}

			Vector2<T>& operator[](const std::size_t& idx) const {
				return m_Rows[idx];
			}

			Matrix2<T>& operator=(const Matrix2<T>& other) {
				return Set(other);
			}

			Matrix2<T>& operator=(Matrix2<T>&& other) noexcept {
				return Set(std::move(other));
			}

			Matrix2<T>& operator+=(const Matrix2<T>& other) {
				return Add(other);
			}

			Matrix2<T>& operator-=(const Matrix2<T>& other) {
				return Subtract(other);
			}

			Matrix2<T>& operator*=(const Matrix2<T>& other) {
				return Multiply(other);
			}

			friend bool operator==(const Matrix2<T>& a, const Matrix2<T>& b) {
				return a.Equal(a);
			}

			friend bool operator!=(const Matrix2<T>& a, const Matrix2<T>& b) {
				return !a.Equal(b);
			}

			friend Matrix2<T> operator+(const Matrix2<T>& a, const Matrix2<T>& b) {
				return std::move(a.Copy().Add(b));
			}

			friend Matrix2<T> operator-(const Matrix2<T>& a, const Matrix2<T>& b) {
				return std::move(a.Copy().Subtract(b));
			}

			friend Matrix2<T> operator*(const Matrix2<T>& a, const Matrix2<T>& b) {
				return std::move(a.Copy().Multiply(b));
			}

			friend Vector2<T> operator*(const Matrix2<T>& mat, const Vector2<T>& vec) {
				return std::move(mat.Multiply(vec));
			}

			friend std::ostream& operator<<(std::ostream& stream, const Matrix2<T>& mat) {
				for (int i = 0; i < AIR_MATH_MAT2_ROWS; i++)
					stream << mat.m_Rows[i];
				return stream;
			}

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