#include "airpch.h"
#pragma once

#include "Math.hpp"
#include "Vector4.hpp"

namespace engine {
	namespace math {

		static constexpr unsigned char MAT4_SIZE = AIR_MATH_MAT4_COLUMNS * AIR_MATH_MAT4_ROWS;


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

			inline T& GetElement(unsigned char row, unsigned char column) {
				return m_Elements[column + row * AIR_MATH_MAT4_COLUMNS];
			}

			inline T GetElement(unsigned char row, unsigned char column) const {
				return m_Elements[column + row * AIR_MATH_MAT4_COLUMNS];
			}

			Matrix4<T>& Transpose() {
				for (int c = 0; c < AIR_MATH_MAT4_COLUMNS; c++) {
					for (int r = c + 1; r < AIR_MATH_MAT4_ROWS; r++) {
						std::swap(GetElement(r, c), GetElement(c, r));
					}
				}
				return *this;
			}

			inline T Determinant() const {
				//TODO implement
				return 0;
			}

			Matrix4<T>& Inverse() {
				//TODO implement
				return *this;
			}

			Matrix4<T>& MakeIdentity() {
				SetDiagonal((T)1);
				return *this;
			}

			Matrix4<T>& Clear() {
				memset(m_Elements, 0, sizeof(T) * MAT4_SIZE);
				return *this;
			}

			inline Matrix4<T> Copy() const {
				return Matrix4<T>(*this);
			}

			Matrix4<T>& SetDiagonal(const T& val) {
				for (int i = 0; i < AIR_MATH_MAT4_COLUMNS; i++)
					GetElement(i, i) = val;
				return *this;
			}

			bool Equal(const Matrix4<T>& other) const {
				if (this == &other) return true;
				for (int i = 0; i < MAT4_SIZE; i++)
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
				for (int i = 0; i < MAT4_SIZE; i++)
					m_Elements[i] *= scalar;
				return *this;
			}

			Matrix4<T>& Multiply(const Matrix4<T>& other) {
				Matrix4<T> copy = std::move(Copy());
				Clear();
				for (int row = 0; row < AIR_MATH_MAT4_ROWS; row++) {
					for (int column = 0; column < AIR_MATH_MAT4_COLUMNS; column++) {
						for (int c = 0; c < AIR_MATH_MAT4_COLUMNS; c++) {
							GetElement(row, column) += copy.GetElement(row, c) * other.GetElement(c, column);
						}
					}
				}
				return *this;
			}

			Matrix4<T>& Add(const Matrix4<T>& other) {
				for (int i = 0; i < MAT4_SIZE; i++)
					m_Elements[i] += other.m_Elements[i];
			}

			Matrix4<T>& Subtract(const Matrix4<T>& other) {
				for (int i = 0; i < MAT4_SIZE; i++)
					m_Elements[i] -= other.m_Elements[i];
			}

			Vector4<T> Multiply(const Vector4<T>& other) const {
				Vector4<T> ret;
				for (int row = 0; row < AIR_MATH_MAT4_ROWS; row++) {
					for (int column = 0; column < AIR_MATH_MAT4_COLUMNS; column++) {
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
				for (int i = 0; i < AIR_MATH_MAT4_ROWS; i++)
					stream << mat.m_Rows[i];
				return stream;
			}

			static constexpr Matrix4<T> Identity() {
				return Matrix4<T>((T)1);
			}

			static constexpr Matrix4<T> Zero() {
				return Matrix4<T>();
			}
		};

		typedef Matrix4<float> Matrix4f;
	}
}