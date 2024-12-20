#ifndef LAB1__MATRIX_H_
#define LAB1__MATRIX_H_

#include <vector>
#include <stdexcept>
#include <sstream>
#include <functional>
#include <iostream>
#include <iomanip>

// the basic matrix class, providing easy two-dimensional array

// this Martix class is based onto single std::vector,
// so basically it should be faster than simple vector of vectors
// also, with this class, there is no need to
// worry about inconsistent sizes of vectors

// note - any resizing of already filled Matrix will invalidate its existing elements

// WARNING: don`t ever use bool as type for this matrix
// as it would fuck all up

template<typename ValueType>
class ProxyBracketHelper;

template<typename ValueType>
class Matrix {
 public:
  Matrix(); // default constructor
  Matrix(const Matrix& other); // copy constructor for da vector

  Matrix(Matrix&& other) noexcept; // rvalue constructor (move construct) for da speed when returning from function

  explicit Matrix(const std::vector<std::vector<ValueType>>& init_vectors);
  Matrix& operator=(const std::vector<std::vector<ValueType>>& init_vectors);

  Matrix& operator=(const Matrix& other);
  Matrix& operator=(Matrix&& other) noexcept; //rvalue copy assigment operator for da speed

  Matrix(int rows, int columns);
  virtual ~Matrix()=default;

  void Rows(int count);
  int Rows() const;

  void Columns(int count);
  int Columns() const;

  ValueType Select(int row, int column) const;
  virtual ValueType& SelectRef(int row, int column);
  virtual const ValueType& SelectRef(int row, int column) const;

  ValueType Select(int element_number) const;
  virtual ValueType& SelectRef(int element_number);
  virtual const ValueType& SelectRef(int element_number) const;

  bool IsOutOfBounds(int row, int column) const;

  std::string GetPrintableMatrix() const;

  ProxyBracketHelper<ValueType> operator[] (int row);
  const ProxyBracketHelper<ValueType> operator[] (int row) const;

 protected:
  void Recalculate();

  int rows_;
  int columns_;

  std::vector<ValueType> one_dimension_vector_;
};


template<typename ValueType>
class ProxyBracketHelper {
  public:
  ProxyBracketHelper()=delete;

  explicit ProxyBracketHelper(Matrix<ValueType>* matrix_p, int row)
      : owner_matrix_(matrix_p), current_row_(row) {}

  void SetRow(const int row) {
    current_row_ = row;
  }

  ValueType& operator[] (const int column) {
    return owner_matrix_->SelectRef(current_row_, column);
  };

  const ValueType& operator[] (const int column) const {
    return owner_matrix_->SelectRef(current_row_, column);
  };

 protected:
  Matrix<ValueType>* owner_matrix_;
  int current_row_;
};

#include "../../src/matrix.inl"

#endif //LAB1__MATRIX_H_
