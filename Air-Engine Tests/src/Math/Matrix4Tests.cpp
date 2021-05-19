#include "pch.h"
#include "Engine\Math\Matrix4.hpp"

namespace engine {
	namespace math {

		namespace Matrix4tests {

			TEST(Matrix4Tests, EmptyConstructor) {
				Matrix4f mat;

				for (int i = 0; i < 2 * 2; i++) {
					EXPECT_EQ(mat.m_Elements[i], 0);
				}
			}

			TEST(Matrix4Tests, DiagonalConstructor) {
				Matrix4f mat(1.0f);

				EXPECT_FLOAT_EQ(mat.m_a11, 1.0f);
				EXPECT_FLOAT_EQ(mat.m_a22, 1.0f);
			}

			TEST(Matrix4Tests, IdentityTranspose) {
				Matrix4f mat(1.0f);

				mat.Transpose();

				EXPECT_FLOAT_EQ(mat.m_a11, 1.0f);
				EXPECT_FLOAT_EQ(mat.m_a22, 1.0f);
				EXPECT_FLOAT_EQ(mat.m_a33, 1.0f);
				EXPECT_FLOAT_EQ(mat.m_a44, 1.0f);
			}

			TEST(Matrix4Tests, Transpose) {
				Matrix4f mat(2.0f);
				mat.m_a12 = 5.0f;
				mat.m_a21 = 9.0f;

				mat.Transpose();

				EXPECT_FLOAT_EQ(mat.m_a11, 2.0f);
				EXPECT_FLOAT_EQ(mat.m_a22, 2.0f);
				EXPECT_FLOAT_EQ(mat.m_a21, 5.0f);
				EXPECT_FLOAT_EQ(mat.m_a12, 9.0f);
			}

			/*
			[a][b][c]
			[d][e][f]
			[g][h][i]
			*/
			//i_{i}:=(a * ((a * e) - (b * d)) / ((((a * e) - (b * d)) * ((a * i) - (c * g))) - (((a * f) - (c * d)) * ((a * h) - (b * g)))))
			TEST(Matrix4Tests, Determinant) {
				Matrix4f mat(2.0f);
				mat.m_a12 = 5.0f;
				mat.m_a21 = 9.0f;

				float det = mat.Determinant();

				float testDet =
					mat[0][0] * mat[1][1] * mat[2][2] -
					mat[0][0] * mat[1][2] * mat[2][1] -
					mat[0][1] * mat[1][0] * mat[2][2] +
					mat[0][1] * mat[1][2] * mat[2][0] +
					mat[0][2] * mat[1][0] * mat[2][1] -
					mat[0][2] * mat[1][1] * mat[2][0];

				EXPECT_FLOAT_EQ(det, testDet);
			}

			TEST(Matrix4Tests, InverseAndMultiply) {
				Matrix4f mat(2.0f);
				mat.m_a11 = 5.0f;
				mat.m_a12 = 7.0f;
				mat.m_a13 = 8.0f;

				mat.m_a21 = 3.0f;
				mat.m_a22 = 5.0f;
				mat.m_a23 = 1.0f;

				mat.m_a31 = 10.0f;
				mat.m_a32 = 5.75f;
				mat.m_a33 = 4.9f;

				Matrix4f inv = mat.Copy().Inverse();

				inv.Multiply(mat);
				EXPECT_NEAR(inv[0][0], 1, 0.0000001);
				EXPECT_NEAR(inv[0][1], 0, 0.0000001);
				EXPECT_NEAR(inv[0][2], 0, 0.0000001);

				EXPECT_NEAR(inv[1][0], 0, 0.0000001);
				EXPECT_NEAR(inv[1][1], 1, 0.0000001);
				EXPECT_NEAR(inv[1][2], 0, 0.0000001);

				EXPECT_NEAR(inv[2][0], 0, 0.0000001);
				EXPECT_NEAR(inv[2][1], 0, 0.0000001);
				EXPECT_NEAR(inv[2][2], 1, 0.0000001);
			}

			TEST(Matrix4Tests, MultiplyScalar) {
				Matrix4f mat(2.0f);
				mat.m_a11 = 5.0f;
				mat.m_a12 = 7.0f;

				mat.m_a21 = 3.0f;
				mat.m_a22 = 8.0f;

				Matrix4f out = mat.Copy().Multiply(9.5f);

				for (int i = 0; i < MAT4_SIZE; i++) {
					//EXPECT_FLOAT_EQ(mat.m_Elements[i] * 9.5f, out.m_Elements[i]);
				}
			}

			TEST(Matrix4Tests, MultiplyVector) {
				Matrix4f mat(2.0f);
				Vector4f vec(9.0f, 13.5f);
				Vector4f vecCopy;
				mat.m_a11 = 5.0f;
				mat.m_a12 = 7.0f;

				mat.m_a21 = 3.0f;
				mat.m_a22 = 8.0f;

				Vector4f out = mat.Copy().Multiply(vec);

				for (int row = 0; row < 2; row++) {
					for (int column = 0; column < 2; column++) {
						vecCopy.m_Coords[row] += mat.GetElement(row, column) * vec.m_Coords[column];
						if (column == 1)
							EXPECT_FLOAT_EQ(out.m_Coords[row], vecCopy.m_Coords[row]);
					}
				}
			}

			TEST(Matrix4Tests, MoveConstructor) {
				Matrix4f mat(2.0f);
				mat.m_a12 = 5.0f;
				mat.m_a21 = 9.0f;
				mat.Transpose();

				Matrix4f copy(std::move(mat));

				EXPECT_FLOAT_EQ(copy.m_a11, 2.0f);
				EXPECT_FLOAT_EQ(copy.m_a22, 2.0f);
				EXPECT_FLOAT_EQ(copy.m_a21, 5.0f);
				EXPECT_FLOAT_EQ(copy.m_a12, 9.0f);

				EXPECT_FLOAT_EQ(mat.m_a11, 0.0f);
				EXPECT_FLOAT_EQ(mat.m_a22, 0.0f);
				EXPECT_FLOAT_EQ(mat.m_a21, 0.0f);
				EXPECT_FLOAT_EQ(mat.m_a12, 0.0f);
			}

			TEST(Matrix4Tests, MoveSet) {
				Matrix4f mat(2.0f);
				mat.m_a12 = 5.0f;
				mat.m_a21 = 9.0f;
				mat.Transpose();

				Matrix4f copy;
				copy.Set(std::move(mat));

				EXPECT_FLOAT_EQ(copy.m_a11, 2.0f);
				EXPECT_FLOAT_EQ(copy.m_a22, 2.0f);
				EXPECT_FLOAT_EQ(copy.m_a21, 5.0f);
				EXPECT_FLOAT_EQ(copy.m_a12, 9.0f);

				EXPECT_FLOAT_EQ(mat.m_a11, 0.0f);
				EXPECT_FLOAT_EQ(mat.m_a22, 0.0f);
				EXPECT_FLOAT_EQ(mat.m_a21, 0.0f);
				EXPECT_FLOAT_EQ(mat.m_a12, 0.0f);
			}

			TEST(Matrix4Tests, Set) {
				Matrix4f mat(2.0f);
				mat.m_a12 = 5.0f;
				mat.m_a21 = 9.0f;
				mat.Transpose();

				Matrix4f copy;
				copy.Set(mat);

				EXPECT_FLOAT_EQ(copy.m_a11, 2.0f);
				EXPECT_FLOAT_EQ(copy.m_a22, 2.0f);
				EXPECT_FLOAT_EQ(copy.m_a21, 5.0f);
				EXPECT_FLOAT_EQ(copy.m_a12, 9.0f);
			}

			TEST(Matrix4Tests, ArrayOperator) {
				Matrix4f mat(2.0f);
				mat.m_a12 = 5.0f;
				mat.m_a21 = 9.0f;

				mat.Transpose();

				EXPECT_FLOAT_EQ(mat[0][0], 2.0f);
				EXPECT_FLOAT_EQ(mat[1][1], 2.0f);
				EXPECT_FLOAT_EQ(mat[1][0], 5.0f);
				EXPECT_FLOAT_EQ(mat[0][1], 9.0f);
			}

			TEST(Matrix4Tests, OperatorTimesVector) {
				Matrix4f mat(2.0f);
				Vector4f vec(9.0f, 13.5f);
				Vector4f vecCopy;
				mat.m_a11 = 5.0f;
				mat.m_a12 = 7.0f;

				mat.m_a21 = 3.0f;
				mat.m_a22 = 8.0f;

				Vector4f out = mat * vec;

				for (int row = 0; row < 2; row++) {
					for (int column = 0; column < 2; column++) {
						vecCopy.m_Coords[row] += mat.GetElement(row, column) * vec.m_Coords[column];
						if (column == 1)
							EXPECT_FLOAT_EQ(out.m_Coords[row], vecCopy.m_Coords[row]);
					}
				}
			}

			TEST(Matrix4Tests, OperatorTimesMatrix) {
				Matrix4f mat(2.0f);
				mat.m_a11 = 5.0f;
				mat.m_a12 = 7.0f;

				mat.m_a21 = 3.0f;
				mat.m_a22 = 5.0f;

				Matrix4f inv = mat.Copy().Inverse();

				EXPECT_EQ(inv * mat, Matrix4f::Identity());
			}

			TEST(Matrix4Tests, Equal) {
				Matrix4f mat(2.0f);
				mat.m_a11 = 5.0f;
				mat.m_a12 = 7.0f;

				mat.m_a21 = 3.0f;
				mat.m_a22 = 5.0f;

				EXPECT_TRUE(mat.Equal(mat));
				EXPECT_TRUE(mat == mat);
				EXPECT_FALSE(mat != mat);

				Matrix4f test(2.0f);
				test.m_a11 = 5.0f;
				test.m_a12 = 7.0f;

				test.m_a21 = 3.0f;
				test.m_a22 = 5.0f;

				EXPECT_TRUE(mat.Equal(test));
				EXPECT_FALSE(mat.Equal(Matrix4f()));
			}
		}

	}
}