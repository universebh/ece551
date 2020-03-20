#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(new IntArray *[r]()) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns),
    rows(new IntArray *[rhs.numRows]()) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(*rhs.rows[i]);
  }
}
IntMatrix::~IntMatrix() {
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
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    IntArray ** tempRows = new IntArray *[rhs.numRows]();
    for (int i = 0; i < rhs.numRows; i++) {
      tempRows[i] = new IntArray(*rhs.rows[i]);
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
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
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

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  IntMatrix ans(this->numRows, this->numColumns);
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      ans[i][j] = (*this)[i][j] + rhs[i][j];
    }
  }
  return ans;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];
    if (i < rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}
