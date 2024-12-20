#include <gtest/gtest.h>
#include <matrices/cyclic_matrix.h>

TEST(CyclicMatrixTest, ConstructionAndSize) {
  CyclicMatrix<int> cyclic_matrix(3, 3);
  EXPECT_EQ(cyclic_matrix.Rows(), 3);
  EXPECT_EQ(cyclic_matrix.Columns(), 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(cyclic_matrix.Select(i, j), 0);  // Default initialized to 0
    }
  }
}

TEST(CyclicMatrixTest, VectorAssignment) {
  std::vector<std::vector<int>> vec = {{1, 2}, {3, 4}};
  CyclicMatrix<int> cyclic_matrix;
  cyclic_matrix = vec;

  EXPECT_EQ(cyclic_matrix.Rows(), 2);
  EXPECT_EQ(cyclic_matrix.Columns(), 2);
  EXPECT_EQ(cyclic_matrix.Select(0, 0), 1);
  EXPECT_EQ(cyclic_matrix.Select(1, 1), 4);
}

TEST(CyclicMatrixTest, PositiveOverflowAccess) {
  CyclicMatrix<int> cyclic_matrix(3, 3);
  cyclic_matrix.SelectRef(0, 0) = 1;
  cyclic_matrix.SelectRef(1, 1) = 2;
  cyclic_matrix.SelectRef(2, 2) = 3;

  EXPECT_EQ(cyclic_matrix.Select(3, 3), 1);  // wraps to (0,0)
  EXPECT_EQ(cyclic_matrix.Select(4, 4), 2);  // wraps to (1,1)
  EXPECT_EQ(cyclic_matrix.Select(5, 5), 3);  // wraps to (2,2)
}

TEST(CyclicMatrixTest, NegativeOverflowAccess) {
  CyclicMatrix<int> cyclic_matrix(3, 3);
  cyclic_matrix.SelectRef(0, 0) = 1;
  cyclic_matrix.SelectRef(1, 1) = 2;
  cyclic_matrix.SelectRef(2, 2) = 3;

  EXPECT_EQ(cyclic_matrix.Select(-1, -1), 3);  // wraps to (2,2)
  EXPECT_EQ(cyclic_matrix.Select(-2, -2), 2);  // wraps to (1,1)
  EXPECT_EQ(cyclic_matrix.Select(-3, -3), 1);  // wraps to (0,0)
}

TEST(CyclicMatrixTest, PositiveOverflowElementAccess) {
  CyclicMatrix<int> cyclic_matrix(3, 3);
  cyclic_matrix.SelectRef(0, 0) = 1;
  cyclic_matrix.SelectRef(1, 1) = 2;
  cyclic_matrix.SelectRef(2, 2) = 3;

  EXPECT_EQ(cyclic_matrix.Select(9), 1);  // wraps to element 0
  EXPECT_EQ(cyclic_matrix.Select(13), 2);  // wraps to element 4
  EXPECT_EQ(cyclic_matrix.Select(17), 3);  // wraps to element 8
}

TEST(CyclicMatrixTest, SetAndGetValues) {
  CyclicMatrix<int> cyclic_matrix(2, 2);
  cyclic_matrix.SelectRef(0, 0) = 5;
  cyclic_matrix.SelectRef(1, 1) = 10;

  EXPECT_EQ(cyclic_matrix.Select(0, 0), 5);
  EXPECT_EQ(cyclic_matrix.Select(1, 1), 10);
  EXPECT_EQ(cyclic_matrix.Select(2, 2), 5);  // Cyclic access to (0, 0)
}

TEST(CyclicMatrixTest, GetPrintableMatrix) {
  CyclicMatrix<int> cyclic_matrix(2, 2);
  cyclic_matrix.SelectRef(0, 0) = 1;
  cyclic_matrix.SelectRef(0, 1) = 2;
  cyclic_matrix.SelectRef(1, 0) = 3;
  cyclic_matrix.SelectRef(1, 1) = 4;

  std::string expected_output = "1 2 \n3 4 \n\n";
  EXPECT_EQ(cyclic_matrix.GetPrintableMatrix(), expected_output);
}

TEST(CyclicMatrixTest, CopyConstructor) {
  CyclicMatrix<int> original(2, 2);
  original.SelectRef(0, 0) = 1;

  CyclicMatrix<int> copy = original;
  EXPECT_EQ(copy.Select(0, 0), 1);
  EXPECT_EQ(copy.Rows(), 2);
  EXPECT_EQ(copy.Columns(), 2);
}

TEST(CyclicMatrixTest, CopyAssignment) {
  CyclicMatrix<int> matrix1(2, 2);
  matrix1.SelectRef(0, 0) = 1;

  CyclicMatrix<int> matrix2;
  matrix2 = matrix1;

  EXPECT_EQ(matrix2.Select(0, 0), 1);
  EXPECT_EQ(matrix2.Rows(), 2);
  EXPECT_EQ(matrix2.Columns(), 2);
}
