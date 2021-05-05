#include "airpch.h"
#pragma once

namespace engine {
	namespace math {

		//TODO Check if inlining is allowed
		//TODO make < <= >= > operators use the member functions provided

		template<typename T>
		struct Vector2 {
			union {
				struct {
					T m_X, m_Y;
				};

				T m_Coords[2];
			};

			Vector2() : Vector2(0, 0) {

			}

			Vector2(const T& x, const T& y) : m_X(x), m_Y(y) {

			}

			Vector2(T&& x, T&& y) : m_X(x), m_Y(y) {
				x = 0;
				y = 0;
			}

			Vector2(const Vector2<T>& vector) : m_X(vector.m_X), m_Y(vector.m_Y) {

			}

			Vector2(Vector2<T>&& vector) noexcept : m_X(std::exchange(vector.m_X, 0)), m_Y(std::exchange(vector.m_Y, 0)) {

			}

			inline double Magnitude() const {
				return sqrt(std::move((double)MagnitudeSquared()));
			}

			inline T MagnitudeSquared() const {
				return (m_X * m_X) + (m_Y * m_Y);
			}

			Vector2<T>& Normalize() {
				float length = std::move(Magnitude());

				m_X = m_X / length;
				m_Y = m_Y / length;
				return *this;
			}

			Vector2<T>& Invert() {
				m_X = -m_X;
				m_Y = -m_Y;
				return *this;
			}

			Vector2<T>& Multiply(const T& scalar) {
				m_X = m_X * scalar;
				m_Y = m_Y * scalar;
				return *this;
			}

			T Dot(const Vector2<T>& other) const {
				return (m_X * other.m_X) + (m_Y * other.m_Y);
			}

			inline bool SmallerThan(const Vector2<T>& other) const {
				return std::move(MagnitudeSquared()) < std::move(other.MagnitudeSquared());
			}

			inline bool SmallerThanOrEqual(const Vector2<T>& other) const {
				return std::move(MagnitudeSquared()) <= std::move(other.MagnitudeSquared());
			}

			inline bool LargerThan(const Vector2<T>& other) const {
				return std::move(MagnitudeSquared()) > std::move(other.MagnitudeSquared());
			}

			inline bool LargerThanOrEqual(const Vector2<T>& other) const {
				return std::move(MagnitudeSquared()) >= std::move(other.MagnitudeSquared());
			}

			inline bool Equal(const Vector2<T>& other) const {
				return (m_X == other.m_X) && (m_Y == other.m_Y);
			}

			Vector2<T>& Set(const Vector2<T>& other) {
				if (this == &other) return *this;
				m_X = other.m_X;
				m_Y = other.m_Y;
				return *this;
			}

			Vector2<T>& Set(Vector2<T>&& other) noexcept {
				if (this == &other) return *this;
				m_X = std::exchange(other.m_X, 0);
				m_Y = std::exchange(other.m_Y, 0);
				return *this;
			}

			Vector2<T>& Add(const Vector2<T>& other) {
				m_X += other.m_X;
				m_Y += other.m_Y;
				return *this;
			}

			Vector2<T>& Subtract(const Vector2<T>& other) {
				m_X -= other.m_X;
				m_Y -= other.m_Y;
				return *this;
			}

			Vector2<T>& Clamp(const T& min, const T& max) {
				m_X = m_X < min ? : min : (m_X > max ? max : m_X);
				m_Y = m_Y < min ? : min : (m_Y > max ? max : m_Y);
				return *this;
			}

			//------	Member operators	------
			//--- operator[] ---
			T operator[](const std::size_t& idx) const {
				return m_Coords[idx];
			}

			T operator[](std::size_t&& idx) const {
				return m_Coords[std::move(idx)];
			}
			//--- operator[] ---

			//--- operator- ---
			Vector2<T> operator-() {
				return Vector2<T>(*this).Invert();
			}
			//--- operator- ---
			//------	Member operators	------

			//------	Non-Member operators	------
			//--- operator= ---
			Vector2<T>& operator=(const Vector2<T>& other) {
				return Set(other);
			}

			Vector2<T>& operator=(Vector2<T>&& other) noexcept {
				return Set(std::move(other));
			}
			//--- operator= ---

			//--- operator+= ---
			Vector2<T>& operator+=(const Vector2<T>& other) {
				return Add(other);
			}
			//---operator+= ---

			//--- operator-= ---
			Vector2<T>& operator-=(const Vector2<T>& other) {
				return Subtract(other);
			}
			//---operator-= ---

			//--- operator*= ---
			Vector2<T>& operator*=(const T& scalar) {
				return Multiply(scalar);
			}
			//--- operator*= ---

			//--- operator== ---
			friend bool operator==(const Vector2<T>& a, const Vector2<T>& b) {
				return a.Equal(b);
			}
			//--- operator== ---

			//--- operator!= ---
			friend bool operator!=(const Vector2<T>& a, const Vector2<T>& b) {
				return !a.Equal(b);
			}
			//--- operator!= ---

			///--- operator+ ---
			friend Vector2<T> operator+(const Vector2<T> a, const Vector2<T>& b) {
				return a.Add(b);
			}

			friend Vector2<T> operator+(const Vector2<T>& a, Vector2<T>&& b) {
				return b.Add(a);
			}

			friend Vector2<T> operator+(Vector2<T>&& a, const Vector2<T>& b) {
				return a.Add(b);
			}

			friend Vector2<T> operator+(Vector2<T>&& a, Vector2<T>&& b) {
				return a.Add(b);
			}
			//--- operator+ ---

			//--- operator- ---
			friend Vector2<T> operator-(const Vector2<T> a, const Vector2<T>& b) {
				return a.Subtract(b);
			}

			friend Vector2<T> operator-(const Vector2<T>& a, Vector2<T>&& b) {
				return b.Invert().Add(a);
			}

			friend Vector2<T> operator-(Vector2<T>&& a, const Vector2<T>& b) {
				return a.Subtract(b);
			}

			friend Vector2<T> operator-(Vector2<T>&& a, Vector2<T>&& b) {
				return a.Subtract(b);
			}
			//--- operator- ---

			//--- operator* ---
			friend Vector2<T> operator*(const Vector2<T> vector, const T& scalar) {
				return vector.Multiply(scalar);
			}

			friend T operator*(const Vector2<T>& a, const Vector2<T>& b) {
				return a.Dot(b);
			}
			//--- operator* ---

			//--- operator< ---
			friend bool operator<(const Vector2<T>& a, const Vector2<T>& b) {
				return a.SmallerThan(b);
			}
			//--- operator< ---

			//--- operator<= ---
			friend bool operator<=(const Vector2<T>& a, const Vector2<T>& b) {
				return a.SmallerThanOrEqual(b);
			}
			//--- operator<= ---

			//--- operator>= ---
			friend bool operator>=(const Vector2<T>& a, const Vector2<T>& b) {
				return a.LargerThanOrEqual(b);
			}
			//--- operator>= ---

			//--- operator> ---
			friend bool operator>(const Vector2<T>& a, const Vector2<T>& b) {
				return a.LargerThan(b);
			}
			//--- operator> ---

			//--- operator<< ---
			friend std::ostream& operator<<(std::ostream& stream, const Vector2<T>& vector) {
				stream << "[" << vector.m_X << "," << vector.m_Y << "]";
				return stream;
			}

			friend std::ostream& operator<<(std::ostream& stream, Vector2<T>&& vector) {
				stream << "[" << vector.m_X << "," << vector.m_Y << "]";
				return stream;
			}
			//--- operator<< ---
			//------	Non-Member operators	------

			static Vector2<T> Zero() {
				return Vector2();
			}
		};

		typedef Vector2<float> Vector2f;
		typedef Vector2<double> Vector2d;
	}
}