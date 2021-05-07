#include "pch.h"
#include "Engine\Math\Vector3.hpp"

#define AIR_TESTS_COORDS 5

namespace engine {
	namespace math {

		struct Coord {
			float m_X, m_Y, m_Z;
		};

		Coord coords[] = {
			{0.0f, 0.0f, 0.0f},
			{5.0f, 6.0f, 7.0f},
			{5.542f, 6.3413f, 6321.5f},
			{-5.542f, 6.3413f, -6321.5f},
			{500000.0f, 600000.0f, 70000.0f}
		};

		float extra[] = {
			8.4f,
			-54.341f,
			5.0f,
			0.0f,
			9413.545f
		};

		TEST(Vector3Test, EmptyConstructor) {
			Vector3f vector;
			EXPECT_EQ(vector.m_X, 0.0f);
			EXPECT_EQ(vector.m_Y, 0.0f);
			EXPECT_EQ(vector.m_Z, 0.0f);
		}

		TEST(Vector3Test, FilledConstructor) {
			for (int i = 0; i < AIR_TESTS_COORDS; i++) {
				Coord coord = coords[i];
				Vector3f vector(coord.m_X, coord.m_Y, coord.m_Z);
				EXPECT_EQ(vector.m_X, coord.m_X);
				EXPECT_EQ(vector.m_Y, coord.m_Y);
				EXPECT_EQ(vector.m_Z, coord.m_Z);
			}
		}

		TEST(Vector3Test, MoveConstructorEmpty) {
			Vector3f vector(Vector3f::Zero());
			EXPECT_EQ(vector.m_X, 0.0f);
			EXPECT_EQ(vector.m_Y, 0.0f);
			EXPECT_EQ(vector.m_Z, 0.0f);
		}

		TEST(Vector3Test, MoveConstructorFilled) {
			for (int i = 0; i < AIR_TESTS_COORDS; i++) {
				Coord coord = coords[i];
				Vector3f vector(Vector3f(coord.m_X, coord.m_Y, coord.m_Z) * 1);
				EXPECT_EQ(vector.m_X, coord.m_X);
				EXPECT_EQ(vector.m_Y, coord.m_Y);
				EXPECT_EQ(vector.m_Z, coord.m_Z);
			}
		}

		TEST(Vector3Test, CopyConstructor) {
			for (int i = 0; i < AIR_TESTS_COORDS; i++) {
				Coord coord = coords[i];
				Vector3f other(coord.m_X, coord.m_Y, coord.m_Z);
				Vector3f vector(other);

				EXPECT_EQ(vector.m_X, coord.m_X);
				EXPECT_EQ(vector.m_Y, coord.m_Y);
				EXPECT_EQ(vector.m_Z, coord.m_Z);
			}
		}

		TEST(Vector3Test, Magnitude) {
			for (int i = 0; i < AIR_TESTS_COORDS; i++) {
				Coord coord = coords[i];
				Vector3f vector(coord.m_X, coord.m_Y, coord.m_Z);
				double mag = vector.Magnitude();
				double exp = sqrt((double)((coord.m_X * coord.m_X) + (coord.m_Y * coord.m_Y) + (coord.m_Z * coord.m_Z)));
				EXPECT_NEAR(mag, exp, 0.000001);
			}
		}

		TEST(Vector3Test, MagnitudeSq) {
			for (int i = 0; i < AIR_TESTS_COORDS; i++) {
				Coord coord = coords[i];
				Vector3f vector(coord.m_X, coord.m_Y, coord.m_Z);
				double mag = vector.MagnitudeSquared();
				double exp = (coord.m_X * coord.m_X) + (coord.m_Y * coord.m_Y) + (coord.m_Z * coord.m_Z);
				EXPECT_EQ(mag, exp);
			}
		}

		TEST(Vector3Test, Normalize) {
			for (int i = 0; i < AIR_TESTS_COORDS; i++) {
				Coord coord = coords[i];
				Vector3f vector(coord.m_X, coord.m_Y, coord.m_Z);
				double mag = vector.Magnitude();
				vector.Normalize();

				if (mag == 0) {
					EXPECT_EQ(vector.m_X, 0);
					EXPECT_EQ(vector.m_Y, 0);
					EXPECT_EQ(vector.m_Z, 0);
				}
				else {
					EXPECT_EQ(vector.m_X, (float)(coord.m_X / mag));
					EXPECT_EQ(vector.m_Y, (float)(coord.m_Y / mag));
					EXPECT_EQ(vector.m_Z, (float)(coord.m_Z / mag));
				}
			}
		}

		TEST(Vector3Test, Invert) {
			for (int i = 0; i < AIR_TESTS_COORDS; i++) {
				Coord coord = coords[i];
				Vector3f vector(coord.m_X, coord.m_Y, coord.m_Z);
				vector.Invert();
				EXPECT_EQ(vector.m_X, -coord.m_X);
				EXPECT_EQ(vector.m_Y, -coord.m_Y);
				EXPECT_EQ(vector.m_Z, -coord.m_Z);
			}
		}

		TEST(Vector3Test, MultiplyScalar) {
			for (int i = 0; i < AIR_TESTS_COORDS; i++) {
				Coord coord = coords[i];
				Vector3f vector(coord.m_X, coord.m_Y, coord.m_Z);
				vector.Multiply(extra[i]);
				EXPECT_EQ(vector.m_X, coord.m_X * extra[i]);
				EXPECT_EQ(vector.m_Y, coord.m_Y * extra[i]);
				EXPECT_EQ(vector.m_Z, coord.m_Z * extra[i]);
			}
		}
	}
}