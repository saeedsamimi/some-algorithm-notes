#include <gtest/gtest.h>

#include <Matrix.hpp>
#include <MatrixExcepts.hpp>

TEST(MatrixAlloc, giveZeroSizes) {
  ASSERT_THROW(Matrix(0, 12), MatrixBadAlloc);
  ASSERT_THROW(Matrix(0, 0), MatrixBadAlloc);
  ASSERT_THROW(Matrix(1200, 0), MatrixBadAlloc);
  ASSERT_NO_THROW(Matrix(100, 100));
  ASSERT_NO_THROW(Matrix(1, 1));
  ASSERT_NO_THROW(Matrix(20, 12));
}

TEST(MatrixArithmeticCall, getBadCall) {
  Matrix mat1(2, 3, {12, 23, 45, 12, 34, -12});
  Matrix mat2(3, 3, {129, 0, 56, 23, -1, -6});
  ASSERT_THROW(mat2 * mat1, MatrixBadArithmeticCall);
  ASSERT_THROW(mat1 + mat2, MatrixBadArithmeticCall);
  ASSERT_THROW(mat1 - mat2, MatrixBadArithmeticCall);
  ASSERT_THROW((void)mat1.determinant(), MatrixBadArithmeticCall);
}

TEST(MatrixArithmeticCall, getCorrectCall) {
  Matrix mat1(2, 3, {1, 2, 3, 4, 5, 6});
  Matrix mat2(3, 2, {1, 2, 3, 4, 5, 6});
  Matrix mat3(2, 3, {-1, 9, -2, 3, 10, 3});
  EXPECT_EQ(mat1 + mat3, Matrix(2, 3, {0, 11, 1, 7, 15, 9}));
  EXPECT_EQ(mat1 - mat3, Matrix(2, 3, {2, -7, 5, 1, -5, 3}));
  EXPECT_EQ(mat1 * mat2, Matrix(2, 2, {22, 28, 49, 64}));
  EXPECT_EQ(mat2 * mat1, Matrix(3, 3, {9, 12, 15, 19, 26, 33, 29, 40, 51}));
  EXPECT_EQ(-mat2, Matrix(3, 2, {-1, -2, -3, -4, -5, -6}));
  EXPECT_EQ(-(-mat3 * mat2), Matrix(2, 2, {16, 22, 48, 64}));
  EXPECT_EQ(mat1 * 2, Matrix(2, 3, {2, 4, 6, 8, 10, 12}));
  EXPECT_EQ(mat3 * -100, Matrix(2, 3, {100, -900, 200, -300, -1000, -300}));
}

TEST(MatrixStaticMembersCall, getEyes) {
  Matrix eye1 = Matrix::eyes(10);
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++) EXPECT_EQ(eye1(i, j), i == j ? 1 : 0);
  Matrix eye2 = Matrix::eyes(10);
  EXPECT_EQ(eye1, eye2);
}

TEST(MatrixStaticMembersCall, getZeros) {
  Matrix zeros1 = Matrix::zeros(10);
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++) EXPECT_EQ(zeros1(i, j), 0);
  Matrix example(10, 1, {1, 3, 24, 22, 4, 34, 3, 4, 5, 10});
  EXPECT_EQ(zeros1 * example, Matrix(10, 1));
}
