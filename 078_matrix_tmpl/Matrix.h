#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix
{
 private:
  int numRows;
  int numColumns;
  std::vector<T> ** rows;

 public:
  Matrix();
  Matrix(int r, int c);
  Matrix(const Matrix & rhs);
  ~Matrix();
  Matrix & operator=(const Matrix & rhs);
  int getRows() const;
  int getColumns() const;
  const std::vector<T> & operator[](int index) const;
  std::vector<T> & operator[](int index);
  bool operator==(const Matrix & rhs) const;
  Matrix operator+(const Matrix & rhs) const;

  template<typename S>
  friend std::ostream & operator<<(std::ostream & s, const Matrix<S> & rhs);
};

//Functions
template<typename T>
Matrix<T>::Matrix() : numRows(0), numColumns(0), rows(NULL) {}

template<typename T>
Matrix<T>::Matrix(int r, int c) : numRows(r), numColumns(c), rows(new std::vector<T> *[r]()) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new std::vector<T>(numColumns);
  }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns),
    rows(new std::vector<T> *[rhs.numRows]()) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new std::vector<T>(*rhs.rows[i]);
  }
}

template<typename T>
Matrix<T>::~Matrix() {
  for (int i = 0; i < numRows; i++) {
    if (rows[i] != NULL) {
      delete rows[i];
      rows[i] = NULL;
    }
  }
  if (rows != NULL) {
    delete[] rows;
    rows = NULL;
  }
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs) {
  if (this != &rhs) {
    std::vector<T> ** tempRows = new std::vector<T> *[rhs.numRows]();
    for (int i = 0; i < rhs.numRows; i++) {
      tempRows[i] = new std::vector<T>(*rhs.rows[i]);
    }
    for (int i = 0; i < numRows; i++) {
      if (rows[i] != NULL) {
        delete rows[i];
        rows[i] = NULL;
      }
    }
    if (rows != NULL) {
      delete[] rows;
      rows = NULL;
    }
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = tempRows;
    for (int i = 0; i < numRows; i++) {
      rows[i] = tempRows[i];
    }
  }
  return *this;
}

template<typename T>
int Matrix<T>::getRows() const {
  return numRows;
}

template<typename T>
int Matrix<T>::getColumns() const {
  return numColumns;
}

template<typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

template<typename T>
std::vector<T> & Matrix<T>::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
  if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
    return false;
  }
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      if ((*this)[i][j] != rhs[i][j]) {
        return false;
      }
    }
  }
  return true;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  Matrix<T> ans(numRows, numColumns);
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      ans[i][j] = (*this)[i][j] + rhs[i][j];
    }
  }
  return ans;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    typename std::vector<T>::const_iterator it = rhs.rows[i]->begin();
    s << "{";
    while (it != rhs.rows[i]->end()) {
      s << *it;
      if (it < rhs.rows[i]->end() - 1) {
        s << ", ";
      }
      ++it;
    }
    s << "}";
    if (i < rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}

#endif
