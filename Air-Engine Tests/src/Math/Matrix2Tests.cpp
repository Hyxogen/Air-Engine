#include "pch.h"
#include "Engine\Math\Matrix2.hpp"

namespace engine {
	namespace math {

		namespace matrix2tests {

			TEST(Matrix2Tests, EmptyConstructor) {
				Matrix2f mat;

				for (int i = 0; i < 2 * 2; i++) {
					EXPECT_EQ(mat.m_Elements[i], 0);
				}
			}

			TEST(Matrix2Tests, DiagonalConstructor) {
				Matrix2f mat(1.0f);

				EXPECT_FLOAT_EQ(mat.m_a11, 1.0f);
				EXPECT_FLOAT_EQ(mat.m_a22, 1.0f);
			}

			TEST(Matrix2Tests, IdentityTranspose) {
				Matrix2f mat(1.0f);

				mat.Transpose();

				EXPECT_FLOAT_EQ(mat.m_a11, 1.0f);
				EXPECT_FLOAT_EQ(mat.m_a22, 1.0f);
			}

			TEST(Matrix2Tests, Transpose) {
				Matrix2f mat(2.0f);
				mat.m_a12 = 5.0f;
				mat.m_a21 = 9.0f;

				mat.Transpose();

				EXPECT_FLOAT_EQ(mat.m_a11, 2.0f);
				EXPECT_FLOAT_EQ(mat.m_a22, 2.0f);
				EXPECT_FLOAT_EQ(mat.m_a21, 5.0f);
				EXPECT_FLOAT_EQ(mat.m_a12, 9.0f);
			}

			TEST(Matrix2Tests, Determinant) {
				Matrix2f mat(2.0f);
				mat.m_a12 = 5.0f;
				mat.m_a21 = 9.0f;

				float det = mat.Determinant();

				EXPECT_FLOAT_EQ(det, (mat.m_a11 * mat.m_a22) - (mat.m_a12 * mat.m_a21));
			}

			TEST(Matrix2Tests, InverseAndMultiply) {
				Matrix2f mat(2.0f);
				mat.m_a11 = 5.0f;
				mat.m_a12 = 7.0f;

				mat.m_a21 = 3.0f;
				mat.m_a22 = 5.0f;

				Matrix2f inv = mat.Copy().Inverse();

				EXPECT_TRUE(inv.Multiply(mat).Equal(Matrix2f::Identity()));
			}

			TEST(Matrix2Tests, MultiplyScalar) {
				Matrix2f mat(2.0f);
				mat.m_a11 = 5.0f;
				mat.m_a12 = 7.0f;

				mat.m_a21 = 3.0f;
				mat.m_a22 = 8.0f;

				Matrix2f out = mat.Copy().Multiply(9.5f);

				for (int i = 0; i < MAT2_SIZE; i++) {
					//EXPECT_FLOAT_EQ(mat.m_Elements[i] * 9.5f, out.m_Elements[i]);
				}
			}

			TEST(Matrix2Tests, MultiplyVector) {
				Matrix2f mat(2.0f);
				Vector2f vec(9.0f, 13.5f);
				Vector2f vecCopy;
				mat.m_a11 = 5.0f;
				mat.m_a12 = 7.0f;

				mat.m_a21 = 3.0f;
				mat.m_a22 = 8.0f;

				Vector2f out = mat.Copy().Multiply(vec);

				for (int row = 0; row < 2; row++) {
					for (int column = 0; column < 2; column++) {
						vecCopy.m_Coords[row] += mat.GetElement(row, column) * vec.m_Coords[column];
						if (column == 1)
							EXPECT_FLOAT_EQ(out.m_Coords[row], vecCopy.m_Coords[row]);
					}
				}
			}

			TEST(Matrix2Tests, MoveConstructor) {
				Matrix2f mat(2.0f);
				mat.m_a12 = 5.0f;
				mat.m_a21 = 9.0f;
				mat.Transpose();

				Matrix2f copy(std::move(mat));

				EXPECT_FLOAT_EQ(copy.m_a11, 2.0f);
				EXPECT_FLOAT_EQ(copy.m_a22, 2.0f);
				EXPECT_FLOAT_EQ(copy.m_a21, 5.0f);
				EXPECT_FLOAT_EQ(copy.m_a12, 9.0f);

				EXPECT_FLOAT_EQ(mat.m_a11, 0.0f);
				EXPECT_FLOAT_EQ(mat.m_a22, 0.0f);
				EXPECT_FLOAT_EQ(mat.m_a21, 0.0f);
				EXPECT_FLOAT_EQ(mat.m_a12, 0.0f);
			}

			TEST(Matrix2Tests, MoveSet) {
				Matrix2f mat(2.0f);
				mat.m_a12 = 5.0f;
				mat.m_a21 = 9.0f;
				mat.Transpose();

				Matrix2f copy;
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

			TEST(Matrix2Tests, Set) {
				Matrix2f mat(2.0f);
				mat.m_a12 = 5.0f;
				mat.m_a21 = 9.0f;
				mat.Transpose();

				Matrix2f copy;
				copy.Set(mat);

				EXPECT_FLOAT_EQ(copy.m_a11, 2.0f);
				EXPECT_FLOAT_EQ(copy.m_a22, 2.0f);
				EXPECT_FLOAT_EQ(copy.m_a21, 5.0f);
				EXPECT_FLOAT_EQ(copy.m_a12, 9.0f);
			}

			TEST(Matrix2Tests, ArrayOperator) {
				Matrix2f mat(2.0f);
				mat.m_a12 = 5.0f;
				mat.m_a21 = 9.0f;

				mat.Transpose();

				EXPECT_FLOAT_EQ(mat[0][0], 2.0f);
				EXPECT_FLOAT_EQ(mat[1][1], 2.0f);
				EXPECT_FLOAT_EQ(mat[1][0], 5.0f);
				EXPECT_FLOAT_EQ(mat[0][1], 9.0f);
			}

			TEST(Matrix2Tests, OperatorTimesVector) {
				Matrix2f mat(2.0f);
				Vector2f vec(9.0f, 13.5f);
				Vector2f vecCopy;
				mat.m_a11 = 5.0f;
				mat.m_a12 = 7.0f;

				mat.m_a21 = 3.0f;
				mat.m_a22 = 8.0f;

				Vector2f out = mat * vec;
				
				for (int row = 0; row < 2; row++) {
					for (int column = 0; column < 2; column++) {
						vecCopy.m_Coords[row] += mat.GetElement(row, column) * vec.m_Coords[column];
						if (column == 1)
							EXPECT_FLOAT_EQ(out.m_Coords[row], vecCopy.m_Coords[row]);
					}
				}
			}

			TEST(Matrix2Tests, OperatorTimesMatrix) {
				Matrix2f mat(2.0f);
				mat.m_a11 = 5.0f;
				mat.m_a12 = 7.0f;

				mat.m_a21 = 3.0f;
				mat.m_a22 = 5.0f;

				Matrix2f inv = mat.Copy().Inverse();

				EXPECT_EQ(inv * mat, Matrix2f::Identity());
			}

			TEST(Matrix2Tests, Equal) {
				Matrix2f mat(2.0f);
				mat.m_a11 = 5.0f;
				mat.m_a12 = 7.0f;

				mat.m_a21 = 3.0f;
				mat.m_a22 = 5.0f;

				EXPECT_TRUE(mat.Equal(mat));
				EXPECT_TRUE(mat == mat);
				EXPECT_FALSE(mat != mat);

				Matrix2f test(2.0f);
				test.m_a11 = 5.0f;
				test.m_a12 = 7.0f;

				test.m_a21 = 3.0f;
				test.m_a22 = 5.0f;

				EXPECT_TRUE(mat.Equal(test));
				EXPECT_FALSE(mat.Equal(Matrix2f()));
			}
		}

	}
}