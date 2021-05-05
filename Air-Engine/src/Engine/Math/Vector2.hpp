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

			Vector2(Vector2<T>&& vector) : m_X(vector.m_X), m_Y(vector.m_Y) {
				
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

			Vector2<T>& Multiply(T&& scalar) {
				return Multiply(scalar);
			}

			T Dot(const Vector2<T>& other) const {
				return (m_X * other.m_X) + (m_Y * other.m_Y);
			}

			T Dot(Vector2<T>&& other) const {
				return std::move(Dot(other));
			}

			inline bool SmallerThan(const Vector2<T>& other) const {
				return std::move(MagnitudeSquared()) < std::move(other.MagnitudeSquared());
			}

			inline bool SmallerThan(Vector2<T>&& other) const {
				return std::move(SmallerThan(other));
			}

			inline bool SmallerThanOrEqual(const Vector2<T>& other) const {
				return std::move(MagnitudeSquared()) <= std::move(other.MagnitudeSquared());
			}

			inline bool SmallerThanOrEqual(Vector2<T>&& other) const {
				return std::move(SmallerThanOrEqual(other));
			}

			inline bool LargerThan(const Vector2<T>& other) const {
				return std::move(MagnitudeSquared()) > std::move(other.MagnitudeSquared());
			}

			inline bool LargerThan(Vector2<T>&& other) const {
				return std::move(LargerThan(other));
			}

			inline bool LargerThanOrEqual(const Vector2<T>& other) const {
				return std::move(MagnitudeSquared()) >= std::move(other.MagnitudeSquared());
			}

			inline bool LargerThanOrEqual(Vector2<T>&& other) const {
				return std::move(LargerThanOrEqual(other));
			}

			inline bool Equal(const Vector2<T>& other) const {
				return (m_X == other.m_X) && (m_Y == other.m_Y);
			}

			inline bool Equal(Vector2<T>&& other) const {
				return Equal(other);
			}

			Vector2<T>& Set(const Vector2<T>& other) {
				m_X = other.m_X;
				m_Y = other.m_Y;
				return *this;
			}

			Vector2<T>& Set(Vector2<T>&& other) {
				return Set(other);
			}

			Vector2<T>& Add(const Vector2<T>& other) {
				m_X += other.m_X;
				m_Y += other.m_Y;
				return *this;
			}

			Vector2<T>& Add(Vector2<T>&& other) {
				return Add(other);
			}

			Vector2<T>& Subtract(const Vector2<T>& other) {
				m_X -= other.m_X;
				m_Y -= other.m_Y;
				return *this;
			}

			Vector2<T>& Subtract(Vector2<T>&& other) {
				return Subtract(other);
			}

			Vector2<T>& Clamp(const T& min, const T& max) {
				m_X = m_X < min ? : min : (m_X > max ? max : m_X);
				m_Y = m_Y < min ? : min : (m_Y > max ? max : m_Y);
				return *this;
			}

			Vector2<T>& Clamp(T&& min, T&& max) {
				return Clamp(min, max);
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
				return Vector2<T>(*this).Invert();
			}
			//--- operator- ---
			//------	Member operators	------

			//------	Non-Member operators	------
			//--- operator= ---
			Vector2<T>& operator=(const Vector2<T>& other) {
				return Set(other);
			}

			Vector2<T>& operator=(Vector2<T>&& other) {
				return Set(other);
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

			//--- operator== ---
			friend bool operator==(const Vector2<T>& a, const Vector2<T>& b) {
				return a.Equal(b);
			}

			friend bool operator==(const Vector2<T>& a, Vector2<T>&& b) {
				return a.Equal(b);
			}

			friend bool operator==(Vector2<T>&& a, const Vector2<T>* b) {
				return a.Equal(b);
			}

			friend bool operator==(Vector2<T>&& a, const Vector2<T>&& b) {
				return a.Equal(b);
			}
			//--- operator== ---

			//--- operator!= ---
			friend bool operator!=(const Vector2<T>& a, const Vector2<T>& b) {
				return !a.Equal(b);
			}

			friend bool operator!=(const Vector2<T>& a, Vector2<T>&& b) {
				return !a.Equal(b);
			}

			friend bool operator!=(Vector2<T>&& a, const Vector2<T>* b) {
				return !a.Equal(b);
			}

			friend bool operator!=(Vector2<T>&& a, const Vector2<T>&& b) {
				return !a.Equal(b);
			}
			//--- operator!= ---

			///--- operator+ ---
			friend Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b) {
				return Vector2<T>(a).Add(b);
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
			friend Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b) {
				return Vector2<T>(a).Subtract(b);
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
			friend Vector2<T> operator*(const Vector2<T>& vector, const T& scalar) {
				return Vector2<T>(vector).Multiply(scalar);
			}

			friend Vector2<T> operator*(const Vector2<T>& vector, T&& scalar) {
				return Vector2<T>(vector).Multiply(scalar);
			}

			friend T operator*(const Vector2<T>& a, const Vector2<T>& b) {
				return a.Dot(b);
			}

			friend T operator*(const Vector2<T>& a, Vector2<T>&& b) {
				return a.Dot(b);
			}

			friend T operator*(Vector2<T>&& a, const Vector2<T>& b) {
				return a.Dot(b);
			}

			friend T operator*(Vector2<T>&& a, Vector2<T>&& b) {
				return a.Dot(b);
			}
			//--- operator* ---

			//--- operator< ---
			friend bool operator<(const Vector2<T>& a, const Vector2<T>& b) {
				return a.SmallerThan(b);
			}

			friend bool operator<(const Vector2<T>& a, Vector2<T>&& b) {
				return a.SmallerThan(b);
			}

			friend bool operator<(Vector2<T>&& a, const Vector2<T>& b) {
				return a.SmallerThan(b);
			}

			friend bool operator<(Vector2<T>&& a, Vector2<T>&& b) {
				return a.SmallerThan(b);
			}
			//--- operator< ---

			//--- operator<= ---
			friend bool operator<=(const Vector2<T>& a, const Vector2<T>& b) {
				return a.SmallerThanOrEqual(b);
			}
			
			friend bool operator<=(const Vector2<T>& a, Vector2<T>&& b) {
				return a.SmallerThanOrEqual(b);
			}
			
			friend bool operator<=(Vector2<T>&& a, const Vector2<T>& b) {
				return a.SmallerThanOrEqual(b);
			}

			friend bool operator<=(Vector2<T>&& a, Vector2<T>&& b) {
				return a.SmallerThanOrEqual(b);
			}
			//--- operator<= ---

			//--- operator>= ---
			friend bool operator>=(const Vector2<T>& a, const Vector2<T>& b) {
				return a.LargerThanOrEqual(b);
			}

			friend bool operator>=(const Vector2<T>& a, Vector2<T>&& b) {
				return a.LargerThanOrEqual(b);
			}

			friend bool operator>=(Vector2<T>&& a, const Vector2<T>& b) {
				return a.LargerThanOrEqual(b);
			}

			friend bool operator>=(Vector2<T>&& a, Vector2<T>&& b) {
				return a.LargerThanOrEqual(b);
			}
			//--- operator>= ---

			//--- operator> ---
			friend bool operator>(const Vector2<T>& a, const Vector2<T>& b) {
				return a.LargerThan(b);
			}
			
			friend bool operator>(const Vector2<T>& a, Vector2<T>&& b) {
				return a.LargerThan(b);
			}
			
			friend bool operator>(Vector2<T>&& a, const Vector2<T>& b) {
				return a.LargerThan(b);
			}
			
			friend bool operator>(Vector2<T>&& a, Vector2<T>&& b) {
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