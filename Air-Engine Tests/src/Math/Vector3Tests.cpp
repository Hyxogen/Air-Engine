#include "pch.h"
#include "Engine\Math\Vector3.hpp"

namespace engine {
	namespace math {
		TEST(Vector3Test, EmptyConstructor) {
			Vector3f vector;
			EXPECT_EQ(vector.m_X, 0.0f);
			EXPECT_EQ(vector.m_Y, 0.0f);
			EXPECT_EQ(vector.m_Z, 0.0f);
		}

		TEST(Vector3Test, FilledConstructor) {
			Vector3f vector(1.8f, -6.35423f, 5.0f);
			EXPECT_EQ(vector.m_X, 1.8f);
			EXPECT_EQ(vector.m_Y, -6.35423f);
			EXPECT_EQ(vector.m_Z, 5.0f);
		}

		TEST(Vector3Test, MoveConstructorEmpty) {
			Vector3f vector(Vector3f::Zero());
			EXPECT_EQ(vector.m_X, 0.0f);
			EXPECT_EQ(vector.m_Y, 0.0f);
			EXPECT_EQ(vector.m_Z, 0.0f);
		}

		TEST(Vector3Test, MoveConstructorFilled) {
			Vector3f vector(Vector3f(1.8f, -6.35423f, 5.0f) * 1);
			EXPECT_EQ(vector.m_X, 1.8f);
			EXPECT_EQ(vector.m_Y, -6.35423f);
			EXPECT_EQ(vector.m_Z, 5.0f);
		}

		TEST(Vector3Test, CopyConstructor) {
			Vector3f other = Vector3f(1.8f, -6.35423f, 5.0f);
			Vector3f vector(other);
			EXPECT_EQ(vector.m_X, 1.8f);
			EXPECT_EQ(vector.m_Y, -6.35423f);
			EXPECT_EQ(vector.m_Z, 5.0f);
		}

		TEST(Vector3Test, Magnitude) {
			Vector3f other = Vector3f(1.5f, -6.5f, 5.0f);
			EXPECT_NEAR(other.Magnitude(), 8.33666, 0.00001);
		}

		TEST(Vector3Test, MagnitudeSq) {
			Vector3f other = Vector3f(1.5f, -6.5f, 5.3f);
			EXPECT_NEAR(other.MagnitudeSquared(), 72.59, 0.001);
		}

		TEST(Vector3Test, Normalize) {
			Vector3f vector(53.5f, -623.0f, 993.55f);
			vector.Normalize();
			EXPECT_LE(vector.m_X, 1.0f);
			EXPECT_LE(vector.m_Y, 1.0f);
			EXPECT_LE(vector.m_Y, 1.0f);
			EXPECT_LE(vector.Magnitude(), 1.0f);
		}
	}
}