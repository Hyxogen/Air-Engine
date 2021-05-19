#include "pch.h"
#include "Engine\Math\Matrix3.hpp"

namespace engine {
	namespace math {

		namespace Matrix3tests {

			TEST(Matrix3Tests, EmptyConstructor) {
				Matrix3f mat;

				for (int i = 0; i < 2 * 2; i++) {
					EXPECT_EQ(mat.m_Elements[i], 0);
				}
			}

			TEST(Matrix3Tests, DiagonalConstructor) {
				Matrix3f mat(1.0f);

				EXPECT_FLOAT_EQ(mat.m_a11, 1.0f);
				EXPECT_FLOAT_EQ(mat.m_a22, 1.0f);
			}

			TEST(Matrix3Tests, IdentityTranspose) {
				Matrix3f mat(1.0f);

				mat.Transpose();

				EXPECT_FLOAT_EQ(mat.m_a11, 1.0f);
				EXPECT_FLOAT_EQ(mat.m_a22, 1.0f);
				EXPECT_FLOAT_EQ(mat.m_a33, 1.0f);
			}

			TEST(Matrix3Tests, Transpose) {
				Matrix3f mat(2.0f);
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
			TEST(Matrix3Tests, Determinant) {
				Matrix3f mat(2.0f);
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

			TEST(Matrix3Tests, InverseAndMultiply) {
				Matrix3f mat(2.0f);
				mat.m_a11 = 5.0f;
				mat.m_a12 = 7.0f;
				mat.m_a13 = 8.0f;

				mat.m_a21 = 3.0f;
				mat.m_a22 = 5.0f;
				mat.m_a23 = 1.0f;

				mat.m_a31 = 10.0f;
				mat.m_a32 = 5.75f;
				mat.m_a33 = 4.9f;

				Matrix3f inv = mat.Copy().Inverse();

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

			TEST(Matrix3Tests, MultiplyScalar) {
				Matrix3f mat(2.0f);
				mat.m_a11 = 5.0f;
				mat.m_a12 = 7.0f;

				mat.m_a21 = 3.0f;
				mat.m_a22 = 8.0f;

				Matrix3f out = mat.Copy().Multiply(9.5f);

				for (int i = 0; i < MAT3_SIZE; i++) {
					EXPECT_FLOAT_EQ(mat.m_Elements[i] * 9.5f, out.m_Elements[i]);
				}
			}

			TEST(Matrix3Tests, MultiplyVector) {
				Matrix3f mat(2.0f);
				Vector3f vec(9.0f, 13.5f);
				Vector3f vecCopy;
				mat.m_a11 = 5.0f;
				mat.m_a12 = 7.0f;

				mat.m_a21 = 3.0f;
				mat.m_a22 = 8.0f;

				Vector3f out = mat.Copy().Multiply(vec);

				for (int row = 0; row < 2; row++) {
					for (int column = 0; column < 2; column++) {
						vecCopy.m_Coords[row] += mat.GetElement(row, column) * vec.m_Coords[column];
						if (column == 1)
							EXPECT_FLOAT_EQ(out.m_Coords[row], vecCopy.m_Coords[row]);
					}
				}
			}

			TEST(Matrix3Tests, MoveConstructor) {
				Matrix3f mat(2.0f);
				mat.m_a12 = 5.0f;
				mat.m_a21 = 9.0f;
				mat.Transpose();

				Matrix3f copy(std::move(mat));

				EXPECT_FLOAT_EQ(copy.m_a11, 2.0f);
				EXPECT_FLOAT_EQ(copy.m_a22, 2.0f);
				EXPECT_FLOAT_EQ(copy.m_a21, 5.0f);
				EXPECT_FLOAT_EQ(copy.m_a12, 9.0f);

				EXPECT_FLOAT_EQ(mat.m_a11, 0.0f);
				EXPECT_FLOAT_EQ(mat.m_a22, 0.0f);
				EXPECT_FLOAT_EQ(mat.m_a21, 0.0f);
				EXPECT_FLOAT_EQ(mat.m_a12, 0.0f);
			}

			TEST(Matrix3Tests, MoveSet) {
				Matrix3f mat(2.0f);
				mat.m_a12 = 5.0f;
				mat.m_a21 = 9.0f;
				mat.Transpose();

				Matrix3f copy;
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

			TEST(Matrix3Tests, Set) {
				Matrix3f mat(2.0f);
				mat.m_a12 = 5.0f;
				mat.m_a21 = 9.0f;
				mat.Transpose();

				Matrix3f copy;
				copy.Set(mat);

				EXPECT_FLOAT_EQ(copy.m_a11, 2.0f);
				EXPECT_FLOAT_EQ(copy.m_a22, 2.0f);
				EXPECT_FLOAT_EQ(copy.m_a21, 5.0f);
				EXPECT_FLOAT_EQ(copy.m_a12, 9.0f);
			}

			TEST(Matrix3Tests, ArrayOperator) {
				Matrix3f mat(2.0f);
				mat.m_a12 = 5.0f;
				mat.m_a21 = 9.0f;

				mat.Transpose();

				EXPECT_FLOAT_EQ(mat[0][0], 2.0f);
				EXPECT_FLOAT_EQ(mat[1][1], 2.0f);
				EXPECT_FLOAT_EQ(mat[1][0], 5.0f);
				EXPECT_FLOAT_EQ(mat[0][1], 9.0f);
			}

			TEST(Matrix3Tests, OperatorTimesVector) {
				Matrix3f mat(2.0f);
				Vector3f vec(9.0f, 13.5f);
				Vector3f vecCopy;
				mat.m_a11 = 5.0f;
				mat.m_a12 = 7.0f;

				mat.m_a21 = 3.0f;
				mat.m_a22 = 8.0f;

				Vector3f out = mat * vec;

				for (int row = 0; row < 2; row++) {
					for (int column = 0; column < 2; column++) {
						vecCopy.m_Coords[row] += mat.GetElement(row, column) * vec.m_Coords[column];
						if (column == 1)
							EXPECT_FLOAT_EQ(out.m_Coords[row], vecCopy.m_Coords[row]);
					}
				}
			}

			TEST(Matrix3Tests, OperatorTimesMatrix) {
				Matrix3f mat(2.0f);
				mat.m_a11 = 5.0f;
				mat.m_a12 = 7.0f;

				mat.m_a21 = 3.0f;
				mat.m_a22 = 5.0f;

				Matrix3f inv = mat.Copy().Inverse();

				EXPECT_EQ(inv * mat, Matrix3f::Identity());
			}

			TEST(Matrix3Tests, Equal) {
				Matrix3f mat(2.0f);
				mat.m_a11 = 5.0f;
				mat.m_a12 = 7.0f;

				mat.m_a21 = 3.0f;
				mat.m_a22 = 5.0f;

				EXPECT_TRUE(mat.Equal(mat));
				EXPECT_TRUE(mat == mat);
				EXPECT_FALSE(mat != mat);

				Matrix3f test(2.0f);
				test.m_a11 = 5.0f;
				test.m_a12 = 7.0f;

				test.m_a21 = 3.0f;
				test.m_a22 = 5.0f;

				EXPECT_TRUE(mat.Equal(test));
				EXPECT_FALSE(mat.Equal(Matrix3f()));
			}
		}

	}
}