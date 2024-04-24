#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <iostream>

class Matrix {
 private:
  int **m_data;
  int m_cols, m_rows;

 public:
  Matrix(int rows, int cols);
  Matrix(int rows, int cols, const std::initializer_list<int> &&list);
  Matrix(const Matrix &mat);
  ~Matrix();
  int operator()(int row, int col) const;
  int &operator()(int row, int col);
  Matrix operator+(const Matrix &mat) const;
  Matrix operator-(const Matrix &mat) const;
  Matrix operator-() const;
  Matrix operator*(const Matrix &mat) const;
  Matrix operator*(int i) const;
  friend Matrix operator*(int i, Matrix &mat);
  Matrix &operator=(const Matrix &mat);
  bool operator==(const Matrix &mat) const;
  bool operator!=(const Matrix &mat) const;
  static Matrix eyes(int size);
  static Matrix zeros(int size);
  [[nodiscard]] int determinant() const;
  [[nodiscard]] Matrix getMinorMatrix(int e_row, int e_col) const;
  friend std::ostream &operator<<(std::ostream &out, const Matrix &mat);
};

#endif  // MATRIX_H