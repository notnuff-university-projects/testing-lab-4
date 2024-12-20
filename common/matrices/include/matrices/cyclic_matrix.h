#ifndef LAB1__CYCLIC_MATRIX_H_
#define LAB1__CYCLIC_MATRIX_H_

#include <vector>
#include <stdexcept>
#include <sstream>

#include "matrix.h"

template<typename ValueType>
class CyclicMatrix : public Matrix<ValueType> {
 public:
  using Matrix<ValueType>::Matrix;

  CyclicMatrix& operator=(const std::vector<std::vector<ValueType>>& init_vectors);

  virtual ~CyclicMatrix()=default;

  ValueType& SelectRef(int row, int column) override;
  const ValueType &SelectRef(int row, int column) const override;
  const ValueType &SelectRef(int element_number) const override;
  ValueType& SelectRef(int element_number) override;
};


#include "../../src/cyclic_matrix.inl"

#endif //LAB1__CYCLIC_MATRIX_H_
