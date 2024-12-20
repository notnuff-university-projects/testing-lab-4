#ifndef LAB1__MATRIX_INL
#define LAB1__MATRIX_INL

#include <vector>
#include <stdexcept>
#include <sstream>

template<typename ValueType>
ProxyBracketHelper<ValueType> Matrix<ValueType>::operator[](const int row) {
  return ProxyBracketHelper<ValueType>(this, row);
}

template<typename ValueType>
const ProxyBracketHelper<ValueType> Matrix<ValueType>::operator[](const int row) const {
  const auto proxy = ProxyBracketHelper<ValueType>(const_cast<Matrix<ValueType>*>(this), row);
  return proxy;
}


template<typename ValueType>
Matrix<ValueType>::Matrix(const std::vector<std::vector<ValueType>>& init_vectors) {
  rows_ = init_vectors.size();
  columns_ = init_vectors.front().size();
  for(const auto &item : init_vectors) {
    one_dimension_vector_.emplace(item.begin(), item.end());
  }
}

template<typename ValueType>
Matrix<ValueType>& Matrix<ValueType>::operator=(const std::vector<std::vector<ValueType>>& init_vectors) {
  rows_ = init_vectors.size();
  columns_ = init_vectors.front().size();
  for(const auto &item : init_vectors) {
    one_dimension_vector_.insert(
          one_dimension_vector_.end(),
          item.begin(),
          item.end()
        );
  }
  return *this;
}

template<typename ValueType>
std::string Matrix<ValueType>::GetPrintableMatrix() const {
  std::stringstream ss;
  for(int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      ss << SelectRef(i, j) << " ";
    }
    ss << "\n";
  }
  ss << "\n";

  return ss.str();
}


template<typename ValueType>
Matrix<ValueType>::Matrix()
    : rows_(0), columns_(0) {

      }


template<typename ValueType>
Matrix<ValueType> &Matrix<ValueType>::operator=(Matrix &&other) noexcept {
  if (this != &other) {
    rows_ = other.rows_;
    columns_ = other.columns_;
    one_dimension_vector_ = std::move(other.one_dimension_vector_);

// Invalidate the other matrix
    other.rows_ = 0;
    other.columns_ = 0;
  }
  return *this;
}


template<typename ValueType>
Matrix<ValueType>::Matrix(Matrix &&other) noexcept
    : rows_(other.rows_), columns_(other.columns_),
      one_dimension_vector_(std::move(other.one_dimension_vector_)) {

  // Invalidate the other matrix
  other.rows_ = 0;
  other.columns_ = 0;
}

template<typename ValueType>
Matrix<ValueType>& Matrix<ValueType>::operator=(const Matrix &other)  {
  if (this != &other) {
    rows_ = other.rows_;
    columns_ = other.columns_;
    one_dimension_vector_ = other.one_dimension_vector_;
    // Recalculate other dependent members if needed
    Recalculate();
  }

  return *this;
}

template<typename ValueType>
Matrix<ValueType>::Matrix(const Matrix &other)
    : rows_(other.rows_),
      columns_(other.columns_),
      one_dimension_vector_(other.one_dimension_vector_) {

}

template<typename ValueType>
ValueType Matrix<ValueType>::Select(int element_number) const {
  return SelectRef(element_number);
}

template<typename ValueType>
ValueType& Matrix<ValueType>::SelectRef(int element_number) {
  if( one_dimension_vector_.size() <= element_number ) {
    std::stringstream err;
    err << "Elements in matrix: " << rows_ * columns_
        << "Tried to access element number: " << element_number;

    throw std::out_of_range( err.str() );
  }

  return one_dimension_vector_[element_number];
}

template<typename ValueType>
const ValueType& Matrix<ValueType>::SelectRef(int element_number) const {
  return const_cast<Matrix<ValueType>*>(this)->SelectRef(element_number);
}

template<typename ValueType>
bool Matrix<ValueType>::IsOutOfBounds(int row, int column) const {
  if(row < 0 || column < 0) return true;
  if(rows_ <= row || columns_ <= column) return true;
  return false;
}

template<typename ValueType>
ValueType Matrix<ValueType>::Select(int row, int column) const {
  return SelectRef(row, column);
}

template<typename ValueType>
ValueType& Matrix<ValueType>::SelectRef(int row, int column) {
  if( IsOutOfBounds(row, column) ) {
    std::stringstream err;
    err << "Matrix dimensions:" << "\n"
        << "rows=" << rows_ << " "
        << "columns=" << columns_ << "\n"
        << "Tried to access:" << "\n"
        << "row=" << row << " "
        << "column=" << column << "\n";
    throw std::out_of_range( err.str() );
  }

  return SelectRef(row * columns_ + column);
}

template<typename ValueType>
const ValueType& Matrix<ValueType>::SelectRef(int row, int column) const {
  return const_cast<Matrix<ValueType>*>(this)->SelectRef(row, column);
}

template<typename ValueType>
void Matrix<ValueType>::Columns(int count) {
  columns_ = count;
}

template<typename ValueType>
int Matrix<ValueType>::Columns() const {
  return columns_;
}

template<typename ValueType>
int Matrix<ValueType>::Rows() const {
  return rows_;
}

template<typename ValueType>
void Matrix<ValueType>::Rows(int count) {
  rows_ = count;
}

template<typename ValueType>
Matrix<ValueType>::Matrix(
    int rows,
    int columns)
    : rows_(rows), columns_(columns) {
  Recalculate();
}

template<typename ValueType>
void Matrix<ValueType>::Recalculate() {
  one_dimension_vector_.resize(rows_ * columns_);
}


#endif //LAB1__MATRIX_INL
