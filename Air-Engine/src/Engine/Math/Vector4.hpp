#include "airpch.h"
#pragma once

namespace engine {
	namespace math {

		template<typename T>
		struct Vector4 {

			union {
				struct {
					T m_X, m_Y, m_Z, m_W;
				};

				T m_Coords[4];
			};

			Vector4(T x = (T)0, T y = (T)0, T z = (T)0, T w = (T)0) : m_X(x), m_Y(y), m_Z(z), m_W(w) {

			}

			Vector4(const Vector4<T> other) : Vector4(other.m_X, other.m_Y, other.m_Z, other.m_W) {

			}

			Vector4(Vector4<T>&& other) noexcept : m_X(std::exchange(other.m_X, 0)), m_Y(std::exchange(other.m_Y, 0)), m_Z(std::exchange(other.m_Z, 0)), m_W(std::exchange(other.m_W, 0)) {

			}

			inline double MagnitudeSquared() const {
				return (m_X * m_X) + (m_Y * m_Y) + (m_Z * m_Z) + (m_W * m_W);
			}

			inline double Magnitude() const {
				return sqrt(std::move(MagnitudeSquared()));
			}

			Vector4<T>& Normalize() {
				double magnitude = std::move(Magnitude());

				if (magnitude == 0) return (*this);

				m_X = m_X / magnitude;
				m_Y = m_Y / magnitude;
				m_Z = m_Z / magnitude;
				m_W = m_W / magnitude;
				return *this;
			}

			Vector4<T>& Invert() {
				m_X = -m_X;
				m_Y = -m_Y;
				m_Z = -m_Z;
				m_W = -m_W;
				return *this;
			}

			Vector4<T>& Multiply(const T& scalar) {
				m_X *= scalar;
				m_Y *= scalar;
				m_Z *= scalar;
				m_W *= scalar;
				return *this;
			}

			inline double Dot(const Vector4<T>& other) const {
				return (m_X * other.m_X) + (m_Y * other.m_Y) + (m_Z * other.m_Z) + (m_W * other.m_W);
			}

			inline bool SmallerThan(const Vector4<T>& other) const {
				return std::move(MagnitudeSquared()) < std::move(other.MagnitudeSquared());
			}

			inline bool SmallerThanOrEqual(const Vector4<T>& other) const {
				return std::move(MagnitudeSquared()) <= std::move(other.MagnitudeSquared());
			}

			inline bool LargerThan(const Vector4<T>& other) const {
				return std::move(MagnitudeSquared()) > std::move(other.MagnitudeSquared());
			}

			inline bool LargerThanOrEqual(const Vector4<T>& other) const {
				return std::move(MagnitudeSquared()) >= std::move(other.MagnitudeSquared());
			}

			inline bool IsEqual(const Vector4<T>& other) const {
				return this == &other ? true : ((m_X == other.m_X) && (m_Y == other.m_Y) && (m_Z == other.m_Z) && (m_W == other.m_W));
			}

			Vector4<T>& Set(const Vector4<T>& other) {
				if (Equal(other)) return *this;
				m_X = other.m_X;
				m_Y = other.m_Y;
				m_Z = other.m_Z;
				m_W = other.m_W;
				return *this;
			}

			Vector4<T>& Set(Vector4<T>&& other) noexcept {
				if (Equal(other)) return;
				m_X = std::exchange(other.m_X);
				m_Y = std::exchange(other.m_Y);
				m_Z = std::exchange(other.m_Z);
				m_W = std::exchange(other.m_W);
				return *this;
			}

			Vector4<T>& Add(const Vector4<T>& other) {
				m_X += other.m_X;
				m_Y += other.m_Y;
				m_Z += other.m_Z;
				m_W += other.m_W;
				return *this;
			}

			Vector4<T>& Subtract(const Vector4<T>& other) {
				m_X -= other.m_X;
				m_Y -= other.m_Y;
				m_Z -= other.m_Z;
				m_W -= other.m_W;
				return *this;
			}

			Vector4<T>& Clamp(const T& min, const T& max) {
				m_X = m_X < min ? min : (m_X > max ? max : m_X);
				m_Y = m_Y < min ? min : (m_Y > max ? max : m_Y);
				m_Z = m_Z < min ? min : (m_Z > max ? max : m_Z);
				m_W = m_W < min ? min : (m_W > max ? max : m_W);
				return *this;
			}


			//------	Member operators	------
			//--- operator[] ---
			T operator[](const std::size_t& idx) const {
				return m_Coords[idx];
			}
			//--- operator[] ---

			//--- operator- ---
			Vector4<T> operator-() {
				return std::move(Vector4<T>(*this).Invert());
			}
			//--- operator- ---

			// //--- operator= ---
			Vector4<T>& operator=(const Vector4<T>& other) {
				return Set(other);
			}

			Vector4<T>& operator=(Vector4<T>&& other) noexcept {
				return Set(std::move(other));
			}
			//--- operator= ---

			//--- operator+= ---
			Vector4<T>& operator+=(const Vector4<T>& other) {
				return Add(other);
			}
			//---operator+= ---

			//--- operator-= ---
			Vector4<T>& operator-=(const Vector4<T>& other) {
				return Subtract(other);
			}
			//---operator-= ---

			//--- operator*= ---
			Vector4<T>& operator*=(const T& scalar) {
				return Multiply(scalar);
			}
			//--- operator*= ---
			//------	Member operators	------

			//------	Non-Member operators	------

			//--- operator== ---
			friend bool operator==(const Vector4<T>& a, const Vector4<T>& b) {
				return a.Equal(b);
			}
			//--- operator== ---

			//--- operator!= ---
			friend bool operator!=(const Vector4<T>& a, const Vector4<T>& b) {
				return !a.Equal(b);
			}
			//--- operator!= ---

			///--- operator+ ---
			friend Vector4<T> operator+(Vector4<T> a, const Vector4<T>& b) {
				return std::move(a.Add(b));
			}
			//--- operator+ ---

			//--- operator- ---
			friend Vector4<T> operator-(Vector4<T> a, const Vector4<T>& b) {
				return std::move(a.Subtract(b));
			}
			//--- operator- ---

			//--- operator* ---
			friend Vector4<T> operator*(const Vector4<T>& vector, const T& scalar) {
				return std::move(Vector4<T>(vector).Multiply(scalar));
			}

			friend Vector4<T> operator*(Vector4<T>&& vector, const T& scalar) noexcept {
				return std::move(vector.Multiply(scalar));
			}

			friend Vector4<T> operator*(const T& scalar, const Vector4<T>& vector) {
				return std::move(Vector4<T>(vector).Multiply(scalar));
			}

			friend Vector4<T> operator*(const T& scalar, Vector4<T>&& vector) noexcept {
				return std::move(vector.Multiply(scalar));
			}

			friend T operator*(const Vector4<T>& a, const Vector4<T>& b) {
				return a.Dot(b);
			}
			//--- operator* ---

			//--- operator< ---
			friend bool operator<(const Vector4<T>& a, const Vector4<T>& b) {
				return a.SmallerThan(b);
			}
			//--- operator< ---

			//--- operator<= ---
			friend bool operator<=(const Vector4<T>& a, const Vector4<T>& b) {
				return a.SmallerThanOrEqual(b);
			}
			//--- operator<= ---

			//--- operator>= ---
			friend bool operator>=(const Vector4<T>& a, const Vector4<T>& b) {
				return a.LargerThanOrEqual(b);
			}
			//--- operator>= ---

			//--- operator> ---
			friend bool operator>(const Vector4<T>& a, const Vector4<T>& b) {
				return a.LargerThan(b);
			}
			//--- operator> ---

			//--- operator<< ---
			friend std::ostream& operator<<(std::ostream& stream, const Vector4<T>& vector) {
				stream << "[" << vector.m_X << "," << vector.m_Y << "," << vector.m_Z << "]";
				return stream;
			}

			static Vector4<T> Zero() {
				return Vector4<T>();
			}

			static Vector4<T> Lerp(const Vector4<T>& a, const Vector4<T> b, float c) {
				return (((1.0f - c) * a) + (c * b));

			}
		};

		typedef Vector4<float> Vector4f;
		typedef Vector4<double> Vector4d;
	}
}