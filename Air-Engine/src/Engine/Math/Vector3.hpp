#include "airpch.h"
#pragma once

namespace engine {
	namespace math {

		template<typename T>
		struct Vector3 {

			union {
				struct {
					T m_X, m_Y, m_Z;
				};

				T m_Coords[3];
			};

			Vector3(T x = (T)0, T y = (T)0, T z = (T)0) : m_X(x), m_Y(y), m_Z(z) {

			}

			Vector3(const Vector3<T>& vector) : Vector3(vector.m_X, vector.m_Y, vector.m_Z) {

			}

			Vector3(Vector3<T>&& vector) noexcept : m_X(std::exchange(vector.m_X, 0)), m_Y(std::exchange(vector.m_Y, 0)), m_Z(std::exchange(vector.m_Z, 0)) {

			}

			inline Vector3<T> Copy() const {
				return Vector3<T>(*this);
			}

			inline double Magnitude() const {
				return sqrt(std::move(MagnitudeSquared()));
			}

			inline double MagnitudeSquared() const {
				return (m_X * m_X) + (m_Y * m_Y) + (m_Z * m_Z);
			}

			Vector3<T>& Normalize() {
				double magnitude = std::move(Magnitude());
				if (magnitude == 0) return *this;
				m_X = m_X / magnitude;
				m_Y = m_Y / magnitude;
				m_Z = m_Z / magnitude;
				return *this;
			}

			Vector3<T>& Invert() {
				m_X = -m_X;
				m_Y = -m_Y;
				m_Z = -m_Z;
				return *this;
			}

			Vector3<T>& Multiply(const T& scalar) {
				m_X *= scalar;
				m_Y *= scalar;
				m_Z *= scalar;
				return *this;
			}

			inline double Dot(const Vector3<T>& other) const {
				return (m_X * other.m_X) + (m_Y * other.m_Y) + (m_Z * other.m_Z);
			}

			inline bool SmallerThan(const Vector3<T>& other) const {
				return std::move(MagnitudeSquared()) < std::move(other.MagnitudeSquared());
			}

			inline bool SmallerThanOrEqual(const Vector3<T>& other) const {
				return std::move(MagnitudeSquared()) <= std::move(other.MagnitudeSquared());
			}

			inline bool LargerThan(const Vector3<T>& other) const {
				return std::move(MagnitudeSquared()) > std::move(other.MagnitudeSquared());
			}

			inline bool LargerThanOrEqual(const Vector3<T>& other) const {
				return std::move(MagnitudeSquared()) >= std::move(other.MagnitudeSquared());
			}

			inline bool Equal(const Vector3<T>& other) const {
				return this == &other ? true : ((m_X == other.m_X) && (m_Y == other.m_Y) && (m_Z == other.m_Z));
			}

			Vector3<T>& Set(const Vector3<T>& other) {
				if (Equal(other)) return *this;
				m_X = other.m_X;
				m_Y = other.m_Y;
				m_Z = other.m_Z;
				return *this;
			}

			Vector3<T>& Set(Vector3<T>&& other) noexcept {
				if (Equal(other)) return *this;
				m_X = std::exchange(other.m_X, 0);
				m_Y = std::exchange(other.m_Y, 0);
				m_Z = std::exchange(other.m_Z, 0);
				return *this;
			}

			Vector3<T>& Add(const Vector3<T>& other) {
				m_X += other.m_X;
				m_Y += other.m_Y;
				m_Z += other.m_Z;
				return *this;
			}

			Vector3<T>& Subtract(const Vector3<T>& other) {
				m_X -= other.m_X;
				m_Y -= other.m_Y;
				m_Z -= other.m_Z;
				return *this;
			}

			Vector3<T> Cross(const Vector3<T>& other) const {
				Vector3<T> ret;
				ret.m_X = (m_Y * other.m_Z) - (m_Z * other.m_Y);
				ret.m_Y = (m_Z * other.m_X) - (m_X * other.m_Z);
				ret.m_Z = (m_X * other.m_Y) - (m_Y * other.m_X);
				return ret;
			}

			//Would const T& min = 0 work?
			Vector3<T>& Clamp(const T& min, const T& max) {
				m_X = m_X < min ? min : (m_X > max ? max : m_X);
				m_Y = m_Y < min ? min : (m_Y > max ? max : m_Y);
				m_Z = m_Z < min ? min : (m_Z > max ? max : m_Z);
				return *this;
			}

			//------	Member operators	------
			//--- operator[] ---
			T operator[](const std::size_t& idx) const {
				return m_Coords[idx];
			}
			//--- operator[] ---

			//--- operator- ---
			Vector3<T> operator-() {
				return std::move(Vector3<T>(*this).Invert());
			}
			//--- operator- ---

			// //--- operator= ---
			Vector3<T>& operator=(const Vector3<T>& other) {
				return Set(other);
			}

			Vector3<T>& operator=(Vector3<T>&& other) noexcept {
				return Set(std::move(other));
			}
			//--- operator= ---

			//--- operator+= ---
			Vector3<T>& operator+=(const Vector3<T>& other) {
				return Add(other);
			}
			//---operator+= ---

			//--- operator-= ---
			Vector3<T>& operator-=(const Vector3<T>& other) {
				return Subtract(other);
			}
			//---operator-= ---

			//--- operator*= ---
			Vector3<T>& operator*=(const T& scalar) {
				return Multiply(scalar);
			}
			//--- operator*= ---
			//------	Member operators	------

			//------	Non-Member operators	------

			//--- operator== ---
			friend bool operator==(const Vector3<T>& a, const Vector3<T>& b) {
				return a.Equal(b);
			}
			//--- operator== ---

			//--- operator!= ---
			friend bool operator!=(const Vector3<T>& a, const Vector3<T>& b) {
				return !a.Equal(b);
			}
			//--- operator!= ---

			///--- operator+ ---
			friend Vector3<T> operator+(Vector3<T> a, const Vector3<T>& b) {
				return std::move(a.Add(b));
			}
			//--- operator+ ---

			//--- operator- ---
			friend Vector3<T> operator-(Vector3<T> a, const Vector3<T>& b) {
				return std::move(a.Subtract(b));
			}
			//--- operator- ---

			//--- operator* ---
			friend Vector3<T> operator*(const Vector3<T>& vector, const T& scalar) {
				return std::move(vector.Copy().Multiply(scalar));
			}

			friend Vector3<T> operator*(Vector3<T>&& vector, const T& scalar) noexcept {
				return std::move(vector.Multiply(scalar));
			}

			friend Vector3<T> operator*(const T& scalar, const Vector3<T>& vector) {
				return std::move(vector.Copy().Multiply(scalar));
			}

			friend Vector3<T> operator*(const T& scalar, Vector3<T>&& vector) noexcept {
				return std::move(vector.Multiply(scalar));
			}

			friend T operator*(const Vector3<T>& a, const Vector3<T>& b) {
				return a.Dot(b);
			}
			//--- operator* ---

			//--- operator< ---
			friend bool operator<(const Vector3<T>& a, const Vector3<T>& b) {
				return a.SmallerThan(b);
			}
			//--- operator< ---

			//--- operator<= ---
			friend bool operator<=(const Vector3<T>& a, const Vector3<T>& b) {
				return a.SmallerThanOrEqual(b);
			}
			//--- operator<= ---

			//--- operator>= ---
			friend bool operator>=(const Vector3<T>& a, const Vector3<T>& b) {
				return a.LargerThanOrEqual(b);
			}
			//--- operator>= ---

			//--- operator> ---
			friend bool operator>(const Vector3<T>& a, const Vector3<T>& b) {
				return a.LargerThan(b);
			}
			//--- operator> ---

			//--- operator<< ---
			friend std::ostream& operator<<(std::ostream& stream, const Vector3<T>& vector) {
				stream << "[" << vector.m_X << "," << vector.m_Y << "," << vector.m_Z << "]";
				return stream;
			}

			static Vector3<T> Zero() {
				return Vector3<T>();
			}

			static Vector3<T> Lerp(const Vector3<T>& a, const Vector3<T> b, float c) {
				return (((1.0f - c) * a) + (c * b));

			}
		};

		typedef Vector3<float> Vector3f;
		typedef Vector3<double> Vector3d;
	}
}