#ifndef LAB1__CYCLIC_MATRIX_INL_
#define LAB1__CYCLIC_MATRIX_INL_

#include <matrices/cyclic_matrix.h>

template<typename ValueType>
CyclicMatrix<ValueType>& CyclicMatrix<ValueType>::operator=(const std::vector<std::vector<ValueType>>& init_vectors) {
  Matrix<ValueType>::operator=(init_vectors);

  return *this;
}

template<typename ValueType>
ValueType& CyclicMatrix<ValueType>::SelectRef(int element_number) {
  auto size = this->one_dimension_vector_.size();
  element_number %= size;
  if(element_number < 0) element_number += size;

  return Matrix<ValueType>::SelectRef(element_number);
}

template<typename ValueType>
ValueType& CyclicMatrix<ValueType>::SelectRef(int row, int column) {
  row %= this->rows_;
  if(row < 0) row += this->rows_;

  column %= this->columns_;
  if(column < 0) column += this->columns_;

  return Matrix<ValueType>::SelectRef(row, column);
}

template<typename ValueType>
const ValueType &CyclicMatrix<ValueType>::SelectRef(int element_number) const {
  return const_cast<CyclicMatrix*>(this)->SelectRef(element_number);
}

template<typename ValueType>
const ValueType &CyclicMatrix<ValueType>::SelectRef(int row, int column) const {
  return const_cast<CyclicMatrix*>(this)->SelectRef(row, column);
}


#endif //LAB1__CYCLIC_MATRIX_INL_
