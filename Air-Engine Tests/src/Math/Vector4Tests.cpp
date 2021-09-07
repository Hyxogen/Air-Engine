#include "pch.h"
#include "Engine\Math\Vector4.hpp"

#define AIR_TESTS_COORDS 5

namespace engine {
	namespace math {
		namespace vector4tests {

			struct Coord {
				float m_X, m_Y, m_Z, m_W;
			};

			Coord coords[] = {
				{0.0f, 0.0f, 0.0f, 0.0f},
				{5.0f, 6.0f, 7.0f, 1.0f},
				{5.542f, 6.3413f, 6321.5f, 542.412f},
				{-5.542f, 6.3413f, -6321.5f, -41.3432f},
				{500000.0f, 600000.0f, 70000.0f, 800000.0f}
			};

			Coord extraCoords[] = {
				{-5.542f, 6.3413f, -6321.5f, -41.3432f},
				{500000.0f, 600000.0f, 70000.0f, 800000.0f},
				{5.0f, 6.0f, 7.0f, 1.0f},
				{5.542f, 6.3413f, 6321.5f, 542.412f},
				{0.0f, 0.0f, 0.0f, 0.0f}
			};

			float extraFloats[] = {
				8.4f,
				-54.341f,
				5.0f,
				0.0f,
				9413.545f
			};

			TEST(Vector4Test, EmptyConstructor) {
				Vector4f vector;
				EXPECT_EQ(vector.m_X, 0.0f);
				EXPECT_EQ(vector.m_Y, 0.0f);
				EXPECT_EQ(vector.m_Z, 0.0f);
				EXPECT_EQ(vector.m_W, 0.0f);
			}

			TEST(Vector4Test, FilledConstructor) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					Vector4f vector(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W);
					EXPECT_EQ(vector.m_X, coord.m_X);
					EXPECT_EQ(vector.m_Y, coord.m_Y);
					EXPECT_EQ(vector.m_Z, coord.m_Z);
					EXPECT_EQ(vector.m_W, coord.m_W);
				}
			}

			TEST(Vector4Test, MoveConstructorEmpty) {
				Vector4f vector(Vector4f::Zero());
				EXPECT_EQ(vector.m_X, 0.0f);
				EXPECT_EQ(vector.m_Y, 0.0f);
				EXPECT_EQ(vector.m_Z, 0.0f);
				EXPECT_EQ(vector.m_W, 0.0f);
			}

			TEST(Vector4Test, MoveConstructorFilled) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					Vector4f vector(Vector4f(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W) * 1);
					EXPECT_EQ(vector.m_X, coord.m_X);
					EXPECT_EQ(vector.m_Y, coord.m_Y);
					EXPECT_EQ(vector.m_Z, coord.m_Z);
					EXPECT_EQ(vector.m_W, coord.m_W);
				}
			}

			TEST(Vector4Test, CopyConstructor) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					Vector4f other(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W);
					Vector4f vector(other);

					EXPECT_EQ(vector.m_X, coord.m_X);
					EXPECT_EQ(vector.m_Y, coord.m_Y);
					EXPECT_EQ(vector.m_Z, coord.m_Z);
					EXPECT_EQ(vector.m_W, coord.m_W);
				}
			}

			TEST(Vector4Test, Magnitude) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					Vector4f vector(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W);
					double mag = vector.Magnitude();
					double exp = sqrt((double)((coord.m_X * coord.m_X) + (coord.m_Y * coord.m_Y) + (coord.m_Z * coord.m_Z) + (coord.m_W * coord.m_W)));
					EXPECT_NEAR(mag, exp, 0.000001);
				}
			}

			TEST(Vector4Test, MagnitudeSq) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					Vector4f vector(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W);
					double mag = vector.MagnitudeSquared();
					double exp = (coord.m_X * coord.m_X) + (coord.m_Y * coord.m_Y) + (coord.m_Z * coord.m_Z) + (coord.m_W * coord.m_W);
					EXPECT_EQ(mag, exp);
				}
			}

			TEST(Vector4Test, Normalize) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					Vector4f vector(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W);
					double mag = vector.Magnitude();
					vector.Normalize();

					if (mag == 0) {
						EXPECT_EQ(vector.m_X, 0);
						EXPECT_EQ(vector.m_Y, 0);
						EXPECT_EQ(vector.m_Z, 0);
						EXPECT_EQ(vector.m_W, 0);
					}
					else {
						EXPECT_EQ(vector.m_X, (float)(coord.m_X / mag));
						EXPECT_EQ(vector.m_Y, (float)(coord.m_Y / mag));
						EXPECT_EQ(vector.m_Z, (float)(coord.m_Z / mag));
						EXPECT_EQ(vector.m_W, (float)(coord.m_W / mag));
					}
				}
			}

			TEST(Vector4Test, Invert) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					Vector4f vector(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W);
					vector.Invert();
					EXPECT_EQ(vector.m_X, -coord.m_X);
					EXPECT_EQ(vector.m_Y, -coord.m_Y);
					EXPECT_EQ(vector.m_Z, -coord.m_Z);
					EXPECT_EQ(vector.m_W, -coord.m_W);
				}
			}

			TEST(Vector4Test, MultiplyScalar) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					Vector4f vector(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W);
					vector.Multiply(extraFloats[i]);
					EXPECT_EQ(vector.m_X, coord.m_X * extraFloats[i]);
					EXPECT_EQ(vector.m_Y, coord.m_Y * extraFloats[i]);
					EXPECT_EQ(vector.m_Z, coord.m_Z * extraFloats[i]);
					EXPECT_EQ(vector.m_W, coord.m_W * extraFloats[i]);
				}
			}

			TEST(Vector4Test, Dot) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					Coord extra = extraCoords[i];
					Vector4f vector(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W);
					Vector4f other(extra.m_X, extra.m_Y, extra.m_Z, extra.m_W);

					EXPECT_EQ(vector.Dot(other), (coord.m_X * extra.m_X) + (coord.m_Y * extra.m_Y) + (coord.m_Z * extra.m_Z) + (coord.m_W * extra.m_W));
				}
			}

			TEST(Vector4Test, SmallerThan) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					Coord extra = extraCoords[i];
					Vector4f vector(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W);
					Vector4f other(extra.m_X, extra.m_Y, extra.m_Z, extra.m_W);

					EXPECT_EQ(vector.MagnitudeSquared() < other.MagnitudeSquared(), vector.SmallerThan(other));
				}
			}

			TEST(Vector4Test, SmallerThanOrEqual) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					Coord extra = extraCoords[i];
					Vector4f vector(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W);
					Vector4f other(extra.m_X, extra.m_Y, extra.m_Z, extra.m_W);

					EXPECT_EQ(vector.MagnitudeSquared() <= other.MagnitudeSquared(), vector.SmallerThanOrEqual(other));
				}
			}

			TEST(Vector4Test, LargerThanOrEqual) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					Coord extra = extraCoords[i];
					Vector4f vector(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W);
					Vector4f other(extra.m_X, extra.m_Y, extra.m_Z, extra.m_W);

					EXPECT_EQ(vector.MagnitudeSquared() >= other.MagnitudeSquared(), vector.LargerThanOrEqual(other));
				}
			}

			TEST(Vector4Test, LargerThan) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					Coord extra = extraCoords[i];
					Vector4f vector(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W);
					Vector4f other(extra.m_X, extra.m_Y, extra.m_Z, extra.m_W);

					EXPECT_EQ(vector.MagnitudeSquared() > other.MagnitudeSquared(), vector.LargerThan(other));
				}
			}

			TEST(Vector4Test, Set) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					Coord extra = extraCoords[i];
					Vector4f vector(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W);
					Vector4f other(extra.m_X, extra.m_Y, extra.m_Z, extra.m_W);
					vector.Set(other);

					EXPECT_EQ(vector.m_X, extra.m_X);
					EXPECT_EQ(vector.m_Y, extra.m_Y);
					EXPECT_EQ(vector.m_Z, extra.m_Z);
					EXPECT_EQ(vector.m_W, extra.m_W);
				}
			}

			TEST(Vector4Test, Equal) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					Coord extra = extraCoords[i];
					Vector4f vector(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W);
					Vector4f other(extra.m_X, extra.m_Y, extra.m_Z, extra.m_W);

					bool equalFunc = vector.Equal(other);
					bool trueEqual = (vector.m_X == extra.m_X) && (vector.m_Y == extra.m_Y) && (vector.m_Z == extra.m_Z) && (vector.m_W == extra.m_W);

					EXPECT_EQ(trueEqual, equalFunc);
					
					EXPECT_TRUE(vector.Equal(vector));
					EXPECT_TRUE(vector.Equal(Vector4f(vector)));
					EXPECT_FALSE(vector.Equal(other));
				}
			}

			TEST(Vector4Test, SetMove) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					Coord extra = extraCoords[i];
					Vector4f vector(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W);
					Vector4f other(extra.m_X, extra.m_Y, extra.m_Z, extra.m_W);
					vector.Set((other * 1.0f));

					EXPECT_EQ(vector.m_X, extra.m_X);
					EXPECT_EQ(vector.m_Y, extra.m_Y);
					EXPECT_EQ(vector.m_Z, extra.m_Z);
					EXPECT_EQ(vector.m_W, extra.m_W);
				}
			}

			TEST(Vector4Test, Add) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					Coord extra = extraCoords[i];
					Vector4f vector(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W);
					Vector4f other(extra.m_X, extra.m_Y, extra.m_Z, extra.m_W);
					vector.Add(other);

					EXPECT_EQ(vector.m_X, coord.m_X + extra.m_X);
					EXPECT_EQ(vector.m_Y, coord.m_Y + extra.m_Y);
					EXPECT_EQ(vector.m_Z, coord.m_Z + extra.m_Z);
					EXPECT_EQ(vector.m_W, coord.m_W + extra.m_W);
				}
			}

			TEST(Vector4Test, Subtract) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					Coord extra = extraCoords[i];
					Vector4f vector(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W);
					Vector4f other(extra.m_X, extra.m_Y, extra.m_Z, extra.m_W);
					vector.Subtract(other);

					EXPECT_EQ(vector.m_X, coord.m_X - extra.m_X);
					EXPECT_EQ(vector.m_Y, coord.m_Y - extra.m_Y);
					EXPECT_EQ(vector.m_Z, coord.m_Z - extra.m_Z);
					EXPECT_EQ(vector.m_W, coord.m_W - extra.m_W);
				}
			}

			TEST(Vector4Test, Clamp) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					float extra = extraFloats[i];
					if (extra < 0)
						extra *= -1;
					Vector4f vector(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W);
					vector.Clamp(-extra, extra);

					EXPECT_LE(vector.m_X, extra);
					EXPECT_LE(vector.m_Y, extra);
					EXPECT_LE(vector.m_Z, extra);
					EXPECT_LE(vector.m_W, extra);

					EXPECT_GE(vector.m_X, -extra);
					EXPECT_GE(vector.m_Y, -extra);
					EXPECT_GE(vector.m_Z, -extra);
					EXPECT_GE(vector.m_W, -extra);
				}
			}

			TEST(Vector4Test, ArrayOperator) {
				for (int i = 0; i < AIR_TESTS_COORDS; i++) {
					Coord coord = coords[i];
					Vector4f vector(coord.m_X, coord.m_Y, coord.m_Z, coord.m_W);
					EXPECT_EQ(vector[0], coord.m_X);
					EXPECT_EQ(vector[1], coord.m_Y);
					EXPECT_EQ(vector[2], coord.m_Z);
					EXPECT_EQ(vector[3], coord.m_W);
				}
			}
		}
	}
}