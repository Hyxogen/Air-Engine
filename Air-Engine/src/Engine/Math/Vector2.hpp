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

			Vector2(Vector2<T>&& vector) : m_X(vector.m_X), m_Y(vector.m_Y) {
				vector.m_Y = (T)0;
				vector.m_Y = (T)0;
				vector.m_Coords == nullptr;
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
				return Multiply((T)-1);
			}
			
			Vector2<T>& Multiply(const T& scalar) {
				m_X = m_X * scalar;
				m_Y = m_Y * scalar;
				return *this;
			}

			Vector2<T>& Multiply(const T&& scalar) {
				m_X = m_X * scalar;
				m_Y = m_Y * scalar;
				return *this;
			}

			Vector2<T>& Dot(const Vector2<T>& other) {
				return (m_X * other.m_X) + (m_Y * other.m_Y);
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

			Vector2<T>& Clamp(const T&& min, const T&& max) {
				m_X = m_X < min ? : min : (m_X > max ? max : m_X);
				m_Y = m_Y < min ? : min : (m_Y > max ? max : m_Y);
				return *this;
			}

			Vector2<T>& operator-() {
				return Invert();
			}

			friend Vector2<T>& operator-(Vector2<T>& vector) {
				return vector.Invert();
			}

			friend Vector2<T>& operator+(Vector2<T>& a, const Vector2<T>& b) {
				return a.Add(b);
			}

			friend Vector2<T>& operator-(Vector2<T>& a, const Vector2<T>& b) {
				return a.Subtract(b);
			}

			friend Vector2<T>& operator*(Vector2<T>& vector, const T& scalar) {
				return vector.Multiply(scalar);
			}

			friend Vector2<T>& operator*(Vector2<T>& vector, const T&& scalar) {
				return vector.Multiply(scalar);
			}

			friend float operator*(const Vector2<T>& a, const Vector2<T>& b) {
				return a.Dot(b);
			}

			friend bool operator<(const Vector2<T>& a, const Vector2<T>& b) {
				return a.MagnitudeSquared() < b.MagnitudeSquared();
			}

			friend bool operator<=(const Vector2<T>& a, const Vector2<T>& b) {
				return a.MagnitudeSquared() <= b.MagnitudeSquared();
			}

			friend bool operator>=(const Vector2<T>& a, const Vector2<T>& b) {
				return a.MagnitudeSquared() >= b.MagnitudeSquared();
			}

			friend bool operator>(const Vector2<T>& a, const Vector2<T>& b) {
				return a.MagnitudeSquared() > b.MagnitudeSquared();
			}

			friend std::ostream& operator<<(std::ostream& stream, const Vector2<T>& vector) {
				stream << "[" << vector.m_X << "," << vector.m_Y << "]";
				return stream;
			}
		};

		typedef Vector2<float> Vector2f;
		typedef Vector2<double> Vector2d;
	}
}