#include <gtest/gtest.h>
#include <matrices/matrix.h>


TEST(MatrixTest, DefaultConstructor) {
  Matrix<int> matrix;
  EXPECT_EQ(matrix.Rows(), 0);
  EXPECT_EQ(matrix.Columns(), 0);
}

TEST(MatrixTest, ParamConstructor) {
  Matrix<int> matrix(3, 4);
  EXPECT_EQ(matrix.Rows(), 3);
  EXPECT_EQ(matrix.Columns(), 4);
}

TEST(MatrixTest, CopyConstructor) {
  Matrix<int> matrix1(2, 2);
  matrix1.SelectRef(0, 0) = 1;
  matrix1.SelectRef(0, 1) = 2;
  matrix1.SelectRef(1, 0) = 3;
  matrix1.SelectRef(1, 1) = 4;

  Matrix<int> matrix2(matrix1);
  EXPECT_EQ(matrix2.Select(0, 0), 1);
  EXPECT_EQ(matrix2.Select(0, 1), 2);
  EXPECT_EQ(matrix2.Select(1, 0), 3);
  EXPECT_EQ(matrix2.Select(1, 1), 4);
}

TEST(MatrixTest, MoveConstructor) {
  Matrix<int> matrix1(2, 2);
  matrix1.SelectRef(0, 0) = 1;

  Matrix<int> matrix2(std::move(matrix1));

  EXPECT_EQ(matrix2.Rows(), 2);
  EXPECT_EQ(matrix2.Columns(), 2);
  EXPECT_EQ(matrix2.Select(0, 0), 1);

  // Original matrix should be empty
  EXPECT_EQ(matrix1.Rows(), 0);
  EXPECT_EQ(matrix1.Columns(), 0);
}

TEST(MatrixTest, AssignmentOperator) {
  Matrix<int> matrix1(2, 2);
  matrix1.SelectRef(0, 0) = 5;
  matrix1.SelectRef(1, 1) = 10;

  Matrix<int> matrix2;
  matrix2 = matrix1;

  EXPECT_EQ(matrix2.Rows(), 2);
  EXPECT_EQ(matrix2.Columns(), 2);
  EXPECT_EQ(matrix2.Select(0, 0), 5);
  EXPECT_EQ(matrix2.Select(1, 1), 10);
}

TEST(MatrixTest, OutOfBoundsAccess) {
  Matrix<int> matrix(2, 2);

  EXPECT_THROW(matrix.SelectRef(2, 2), std::out_of_range);
  EXPECT_THROW(matrix.SelectRef(3, 0), std::out_of_range);
  EXPECT_THROW(matrix.SelectRef(-1, 0), std::out_of_range);
}

TEST(MatrixTest, ProxyBracketOperator) {
  Matrix<int> matrix(3, 3);
  matrix.SelectRef(1, 1) = 100;

  EXPECT_EQ(matrix[1][1], 100);

  const Matrix<int> const_matrix(matrix);
  EXPECT_EQ(const_matrix[1][1], 100);
}

TEST(MatrixTest, AssignVectorOfVectors) {
  std::vector<std::vector<int>> vec = {{1, 2}, {3, 4}};
  Matrix<int> matrix;
  matrix = vec;

  EXPECT_EQ(matrix.Rows(), 2);
  EXPECT_EQ(matrix.Columns(), 2);
  EXPECT_EQ(matrix.Select(0, 0), 1);
  EXPECT_EQ(matrix.Select(1, 1), 4);
}

TEST(MatrixTest, ResizeMatrix) {
  Matrix<int> matrix(2, 2);
  matrix.Rows(3);
  matrix.Columns(3);

  EXPECT_EQ(matrix.Rows(), 3);
  EXPECT_EQ(matrix.Columns(), 3);
}

TEST(MatrixTest, GetPrintableMatrix) {
  Matrix<int> matrix(2, 2);
  matrix.SelectRef(0, 0) = 1;
  matrix.SelectRef(0, 1) = 2;
  matrix.SelectRef(1, 0) = 3;
  matrix.SelectRef(1, 1) = 4;

  std::string expected_output = "1 2 \n3 4 \n\n";
  EXPECT_EQ(matrix.GetPrintableMatrix(), expected_output);
}