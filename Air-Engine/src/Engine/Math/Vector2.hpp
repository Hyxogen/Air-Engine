#include "airpch.h"
#pragma once

namespace engine {
	namespace math {

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

			Vector2(Vector2<T>&& vector) noexcept : m_X(vector.m_X), m_Y(vector.m_Y) {
				vector.m_Y = (T)0;
				vector.m_Y = (T)0;
			}

			T Magnitude() const {
				sqrt((double)MagnitudeSquared());
			}

			T MagnitudeSquared() const {
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

			Vector2<T>& Multiply(T&& scalar) {
				m_X = m_X * scalar;
				m_Y = m_Y * scalar;
				return *this;
			}

			T Dot(const Vector2<T>& other) const {
				return (m_X * other.m_X) + (m_Y * other.m_Y);
			}

			T Dot(Vector2<T>&& other) const {
				return (m_X * other.m_X) + (m_Y * other.m_Y);
			}

			Vector2<T>& Add(const Vector2<T>& other) {
				m_X += other.m_X;
				m_Y += other.m_Y;
				return *this;
			}

			Vector2<T>& Add(Vector2<T>&& other) {
				m_X += other.m_X;
				m_Y += other.m_Y;
				return *this;
			}

			Vector2<T>& Subtract(const Vector2<T>& other) {
				m_X -= other.m_X;
				m_Y -= other.m_Y;
				return *this;
			}

			Vector2<T>& Subtract(Vector2<T>&& other) {
				m_X -= other.m_X;
				m_Y -= other.m_Y;
				return *this;
			}

			Vector2<T>& Clamp(const T& min, const T& max) {
				m_X = m_X < min ? : min : (m_X > max ? max : m_X);
				m_Y = m_Y < min ? : min : (m_Y > max ? max : m_Y);
				return *this;
			}

			Vector2<T>& Clamp(T&& min, T&& max) {
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
				return m_Coords[idx];
			}
			//--- operator[] ---

			//--- operator- ---
			Vector2<T> operator-() {
				Vector2<T> ret(*this);
				return ret.Invert();
			}
			//--- operator- ---
			//------	Member operators	------

			//------	Non-Member operators	------
			//--- operator= ---
			Vector2<T> operator=(const Vector2<T>& other) {
				return Vector2<T>(other);
			}

			Vector2<T> operator=(Vector2<T>&& other) {
				return Vector2<T>(other);
			}
			//--- operator= ---

			//--- operator+= ---
			Vector2<T>& operator+=(const Vector2<T>& other) {
				return Add(other);
			}

			Vector2<T>& operator+=(Vector2<T>&& other) {
				return Add(other);
			}
			//---operator+= ---

			//--- operator-= ---
			Vector2<T>& operator-=(const Vector2<T>& other) {
				return Subtract(other);
			}

			Vector2<T>& operator-=(Vector2<T>&& other) {
				return Subtract(other);
			}
			//---operator-= ---

			//--- operator*= ---
			Vector2<T>& operator*=(const T& scalar) {
				return Multiply(scalar);
			}

			Vector2<T>& operator*=(T&& scalar) {
				return Multiply(scalar);
			}
			//--- operator*= ---

			///--- operator+ ---
			Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b) {
				Vector2<T> ret(a);
				return ret.Add(b);
			}

			Vector2<T> operator+(const Vector2<T>& a, Vector2<T>&& b) {
				return b.Add(a);
			}

			Vector2<T> operator+(Vector2<T>&& a, const Vector2<T>& b) {
				return a.Add(b);
			}

			Vector2<T> operator+(Vector2<T>&& a, Vector2<T>&& b) {
				return a.Add(b);
			}
			//--- operator+ ---

			//--- operator- ---
			Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b) {
				Vector2<T> ret(a);
				return ret.Subtract(b);
			}

			Vector2<T> operator-(const Vector2<T>& a, Vector2<T>&& b) {
				return b.Invert().Add(a);
			}

			Vector2<T> operator-(Vector2<T>&& a, const Vector2<T>& b) {
				return a.Subtract(b);
			}

			Vector2<T> operator-(Vector2<T>&& a, Vector2<T>&& b) {
				return a.Subtract(b);
			}
			//--- operator- ---

			//--- operator* ---
			Vector2<T> operator*(const Vector2<T>& vector, const T& scalar) {
				Vector2<T> ret(vector);
				return ret.Multiply(scalar);
			}

			Vector2<T> operator*(const Vector2<T>& vector, T&& scalar) {
				Vector2<T> ret(vector);
				return ret.Multiply(scalar);
			}

			T operator*(const Vector2<T>& a, const Vector2<T>& b) {
				return a.Dot(b);
			}

			T operator*(const Vector2<T>& a, Vector2<T>&& b) {
				return a.Dot(b);
			}

			T operator*(Vector2<T>&& a, const Vector2<T>& b) {
				return a.Dot(b);
			}

			T operator*(Vector2<T>&& a, Vector2<T>&& b) {
				return a.Dot(b);
			}
			//--- operator* ---

			//--- operator< ---
			bool operator<(const Vector2<T>& a, const Vector2<T>& b) {
				return a.MagnitudeSquared() < b.MagnitudeSquared();
			}

			bool operator<(const Vector2<T>& a, Vector2<T>&& b) {
				return a.MagnitudeSquared() < b.MagnitudeSquared();
			}

			bool operator<(Vector2<T>&& a, const Vector2<T>& b) {
				return a.MagnitudeSquared() < b.MagnitudeSquared();
			}

			bool operator<(Vector2<T>&& a, Vector2<T>&& b) {
				return a.MagnitudeSquared() < b.MagnitudeSquared();
			}
			//--- operator< ---

			//--- operator<= ---
			bool operator<=(const Vector2<T>& a, const Vector2<T>& b) {
				return a.MagnitudeSquared() <= b.MagnitudeSquared();
			}

			bool operator<=(const Vector2<T>& a, Vector2<T>&& b) {
				return a.MagnitudeSquared() <= b.MagnitudeSquared();
			}

			bool operator<=(Vector2<T>&& a, const Vector2<T>& b) {
				return a.MagnitudeSquared() <= b.MagnitudeSquared();
			}

			bool operator<=(Vector2<T>&& a, Vector2<T>&& b) {
				return a.MagnitudeSquared() <= b.MagnitudeSquared();
			}
			//--- operator<= ---

			//--- operator>= ---
			bool operator>=(const Vector2<T>& a, const Vector2<T>& b) {
				return a.MagnitudeSquared() >= b.MagnitudeSquared();
			}

			bool operator>=(const Vector2<T>& a, Vector2<T>&& b) {
				return a.MagnitudeSquared() >= b.MagnitudeSquared();
			}

			bool operator>=(Vector2<T>&& a, const Vector2<T>& b) {
				return a.MagnitudeSquared() >= b.MagnitudeSquared();
			}

			bool operator>=(Vector2<T>&& a, Vector2<T>&& b) {
				return a.MagnitudeSquared() >= b.MagnitudeSquared();
			}
			//--- operator>= ---

			//--- operator> ---
			bool operator>(const Vector2<T>& a, const Vector2<T>& b) {
				return a.MagnitudeSquared() > b.MagnitudeSquared();
			}

			bool operator>(const Vector2<T>& a, Vector2<T>&& b) {
				return a.MagnitudeSquared() > b.MagnitudeSquared();
			}

			bool operator>(Vector2<T>&& a, const Vector2<T>& b) {
				return a.MagnitudeSquared() > b.MagnitudeSquared();
			}

			bool operator>(Vector2<T>&& a, Vector2<T>&& b) {
				return a.MagnitudeSquared() > b.MagnitudeSquared();
			}
			//--- operator> ---

			//--- operator<< ---
			std::ostream& operator<<(std::ostream& stream, const Vector2<T>& vector) {
				stream << "[" << vector.m_X << "," << vector.m_Y << "]";
				return stream;
			}

			std::ostream& operator<<(std::ostream& stream, Vector2<T>&& vector) {
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