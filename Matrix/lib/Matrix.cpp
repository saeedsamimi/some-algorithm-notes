#include <Matrix.hpp>
#include <MatrixExcepts.hpp>
#include <iomanip>

#define FOR2D(rows, cols)        \
  for (int i = 0; i < rows; i++) \
    for (int j = 0; j < cols; j++)

using std::initializer_list;
using std::ostream, std::istream;

Matrix::Matrix(int rows, int cols) : m_rows(rows), m_cols(cols) {
  if (rows > 0 && cols > 0) {
    m_data = new int *[m_rows];
    for (int i = 0; i < m_rows; i++) m_data[i] = new int[m_cols]{0};
  } else
    throw MatrixBadAlloc();
}

Matrix::Matrix(int rows, int cols, const initializer_list<int> &&list)
    : Matrix(rows, cols) {
  int i, j;
  i = j = 0;
  for (int d : list) {
    m_data[i][j++] = d;
    if (j == m_cols) {
      j = 0;
      if (++i == m_rows) break;
    }
  }
}

std::ostream &operator<<(std::ostream &out, const Matrix &mat) {
  for (int i = 0; i < mat.m_rows; i++) {
    if (i + 1 == mat.m_rows)
      out << "└";
    else if (!i)
      out << "┌";
    else
      out << "│";
    for (int j = 0; j < mat.m_cols; j++)
      out << std::setw(4) << mat.m_data[i][j] << ' ';
    if (i + 1 == mat.m_rows)
      out << "┘";
    else if (!i)
      out << "┐";
    else
      out << "│";
    out << std::endl;
  }
  return out;
}

Matrix::~Matrix() {
  for (int i = 0; i < m_rows; i++) delete[] m_data[i];
  delete[] m_data;
}

Matrix Matrix::operator+(const Matrix &mat) const {
  if (mat.m_rows == m_rows && mat.m_cols == m_cols) {
    Matrix m(m_rows, m_cols);
    FOR2D(m_rows, m_cols) { m.m_data[i][j] = m_data[i][j] + mat.m_data[i][j]; }
    return m;
  } else
    throw MatrixBadArithmeticCall();
}

Matrix Matrix::operator-(const Matrix &mat) const {
  if (mat.m_rows == m_rows && mat.m_cols == m_cols) {
    Matrix m(m_rows, m_cols);
    FOR2D(m_rows, m_cols) { m.m_data[i][j] = m_data[i][j] - mat.m_data[i][j]; }
    return m;
  } else
    throw MatrixBadArithmeticCall();
}

Matrix Matrix::operator*(const Matrix &mat) const {
  if (m_cols == mat.m_rows) {
    Matrix m(m_rows, mat.m_cols);
    FOR2D(m_rows, mat.m_cols) {
      m.m_data[i][j] = 0;
      for (int k = 0; k < mat.m_rows; k++)
        m.m_data[i][j] += m_data[i][k] * mat.m_data[k][j];
    }
    return m;
  } else
    throw MatrixBadArithmeticCall();
}

Matrix Matrix::operator-() const {
  Matrix m(m_rows, m_cols);
  FOR2D(m_rows, m_cols) { m.m_data[i][j] = -m_data[i][j]; }
  return m;
}

int &Matrix::operator()(int row, int col) {
  if (row >= 0 && col >= 0 && col <= m_cols && row <= m_rows)
    return m_data[row][col];
  else
    throw MatrixOutOfRange();
}

int Matrix::operator()(int row, int col) const { return m_data[row][col]; }

Matrix::Matrix(const Matrix &mat) : Matrix(mat.m_rows, mat.m_cols) {
  FOR2D(m_rows, m_cols) { m_data[i][j] = mat.m_data[i][j]; }
}

int Matrix::determinant() const {
  if (m_rows == m_cols) {
    if (m_rows == 1) return **m_data;
    int temp = 0;
    for (int j = 0, k = 1; j < m_cols; j++, k *= -1)
      temp += k * *m_data[j] * getMinorMatrix(0, j).determinant();
    return temp;
  } else
    throw MatrixBadArithmeticCall();
}

Matrix Matrix::getMinorMatrix(int e_row, int e_col) const {
  if (e_row >= 0 && e_row < m_rows && e_col < m_cols && e_col >= 0) {
    Matrix temp(m_rows - 1, m_cols - 1);
    int ri, rj, i, j;
    for (ri = i = 0; i < m_rows; i++) {
      if (i != e_row) {
        for (rj = j = 0; j < m_cols; j++)
          if (j != e_col) temp.m_data[ri][rj++] = m_data[i][j];
        ri++;
      }
    }
    return temp;
  } else
    throw MatrixOutOfRange();
}

bool Matrix::operator==(const Matrix &mat) const {
  if (mat.m_rows == m_rows && mat.m_cols == m_cols) {
    FOR2D(m_rows, m_cols) {
      if (mat.m_data[i][j] != m_data[i][j]) return false;
    }
    return true;
  }
  return false;
}

bool Matrix::operator!=(const Matrix &mat) const { return !operator==(mat); }

Matrix Matrix::operator*(int x) const {
  Matrix m(m_rows, m_cols);
  FOR2D(m_rows, m_cols) { m.m_data[i][j] = x * m_data[i][j]; }
  return m;
}

Matrix &Matrix::operator=(const Matrix &mat) {
  if (operator!=(mat)) {
    this->~Matrix();
    m_rows = mat.m_rows;
    m_cols = mat.m_cols;
    m_data = new int *[m_rows];
    for (int i = 0; i < m_rows; i++) {
      m_data[i] = new int[m_cols];
      for (int j = 0; j < m_cols; j++) m_data[i][j] = mat.m_data[i][j];
    }
  }
  return *this;
}

Matrix operator*(int i, Matrix &mat) { return mat * i; }

Matrix Matrix::eyes(int size) {
  Matrix t(size, size);
  for (int i = 0; i < size; i++) t.m_data[i][i] = 1;
  return t;
}

Matrix Matrix::zeros(int size) { return Matrix(size, size); }

#undef FOR2D
