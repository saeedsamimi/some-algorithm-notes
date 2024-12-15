#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <array>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

template <std::size_t Rows, std::size_t Cols, typename T>
class Matrix {
  static_assert(Rows && Cols, "The matrix dimension must be positive");
  static_assert(std::is_arithmetic_v<T>,
                "Matrix elements must be an integral type");
  std::array<T, Rows * Cols> data_;

  using MatrixPair = std::pair<Matrix<Rows, Cols, T>, Matrix<Rows, Cols, T>>;

 public:
  constexpr Matrix() : data_{} {}

  constexpr Matrix(T value) { data_.fill(value); }

  constexpr Matrix(const std::initializer_list<T> &init) {
    if (init.size() != Rows * Cols) {
      throw std::invalid_argument(
          "Initializer list size does not match matrix dimensions");
    }
    std::copy(init.begin(), init.end(), data_.begin());
  }

  constexpr T &operator()(std::size_t row, std::size_t col) {
    return data_[row * Cols + col];
  }

  constexpr const T &operator()(std::size_t row, std::size_t col) const {
    return data_[row * Cols + col];
  }

  constexpr std::size_t rows() const { return Rows; }

  constexpr std::size_t cols() const { return Cols; }

  constexpr Matrix<Rows, Cols, T> operator+(
      const Matrix<Rows, Cols, T> &other) const {
    Matrix<Rows, Cols, T> result;
    for (std::size_t i = 0; i < Rows * Cols; ++i) {
      result.data_[i] = this->data_[i] + other.data_[i];
    }
    return result;
  }

  constexpr Matrix<Rows, Cols, T> operator-(
      const Matrix<Rows, Cols, T> &other) const {
    Matrix<Rows, Cols, T> result;
    for (std::size_t i = 0; i < Rows * Cols; ++i) {
      result.data_[i] = this->data_[i] - other.data_[i];
    }
    return result;
  }

  constexpr Matrix<Rows, Cols, T> operator*(T scalar) const {
    Matrix<Rows, Cols, T> result;
    for (std::size_t i = 0; i < Rows * Cols; ++i) {
      result.data_[i] = this->data_[i] * scalar;
    }
    return result;
  }

  template <std::size_t OtherCols>
  constexpr Matrix<Rows, OtherCols, T> operator*(
      const Matrix<Cols, OtherCols, T> &other) const {
    Matrix<Rows, OtherCols, T> result{};
    for (std::size_t i = 0; i < Rows; ++i) {
      for (std::size_t j = 0; j < OtherCols; ++j) {
        for (std::size_t k = 0; k < Cols; ++k) {
          result(i, j) += (*this)(i, k) * other(k, j);
        }
      }
    }
    return result;
  }

  constexpr T determinant() const {
    static_assert(Rows == Cols,
                  "Matrix must be square to compute determinant.");

    if constexpr (Rows == 1) {
      return this->operator()(0, 0);
    } else if constexpr (Rows == 2) {
      return this->operator()(0, 0) * this->operator()(1, 1) -
             this->operator()(0, 1) * this->operator()(1, 0);
    } else {
      T det = 0;
      for (std::size_t j = 0; j < Cols; ++j) {
        det += (this->operator()(0, j) * minor(0, j).determinant() *
                (j % 2 == 0 ? 1 : -1));
      }
      return det;
    }
  }

  constexpr Matrix<Rows - 1, Cols - 1, T> minor(std::size_t row,
                                                std::size_t col) const {
    static_assert(Rows > 1 && Cols > 1,
                  "Matrix must be larger than 1x1 to compute minor.");

    Matrix<Rows - 1, Cols - 1, T> result;
    std::size_t newRow = 0, newCol = 0;

    for (std::size_t i = 0; i < Rows; ++i) {
      for (std::size_t j = 0; j < Cols; ++j) {
        if (i != row && j != col) {
          result(newRow, newCol) = this->operator()(i, j);
          newCol++;
          if (newCol == Cols - 1) {
            newCol = 0;
            newRow++;
          }
        }
      }
    }
    return result;
  }

  constexpr Matrix<Cols, Rows, T> transpose() const {
    Matrix<Cols, Rows, T> result;
    for (std::size_t i = 0; i < Rows; ++i) {
      for (std::size_t j = 0; j < Cols; ++j) {
        result(j, i) = (*this)(i, j);
      }
    }
    return result;
  }

  constexpr Matrix<Rows, Cols, T> mul(const Matrix<Rows, Cols, T> &mat) const {
    Matrix<Rows, Cols, T> temp = *this;
    for (std::size_t i = 0; i < Rows * Cols; ++i) {
      temp.data_[i] *= mat.data_[i];
    }
    return temp;
  }

  constexpr MatrixPair lu() const {
    static_assert(Rows == Cols, "LU decomposition requires a square matrix");

    Matrix<Rows, Cols, T> L{};
    Matrix<Rows, Cols, T> U = *this;

    for (std::size_t i = 0; i < Rows; ++i) {
      L(i, i) = 1;  // Set the diagonal elements of L to 1

      for (std::size_t j = i + 1; j < Rows; ++j) {
        if (U(i, i) == 0) {
          throw std::runtime_error(
              "LU decomposition requires a non-singular matrix");
        }
        T factor = U(j, i) / U(i, i);
        L(j, i) = factor;
        for (std::size_t k = i; k < Cols; ++k) {
          U(j, k) -= factor * U(i, k);
        }
      }
    }

    return std::make_pair(L, U);
  }

  constexpr MatrixPair ru() const {
    static_assert(Rows == Cols, "RU decomposition requires a square matrix");

    Matrix<Rows, Cols, T> R = *this;
    Matrix<Rows, Cols, T> U{};

    for (std::size_t i = 0; i < Rows; ++i) {
      for (std::size_t j = i + 1; j < Rows; ++j) {
        if (R(i, i) == 0) {
          throw std::runtime_error(
              "RU decomposition requires a non-singular matrix");
        }
        T factor = R(j, i) / R(i, i);
        for (std::size_t k = i; k < Cols; ++k) {
          R(j, k) -= factor * R(i, k);
        }
        U(j, i) = factor;
      }
    }

    return std::make_pair(R, U);
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const Matrix<Rows, Cols, T> &matrix) {
    for (std::size_t i = 0; i < Rows; ++i) {
      for (std::size_t j = 0; j < Cols; ++j) {
        os << matrix(i, j) << " ";
      }
      os << '\n';
    }
    return os;
  }
};

#endif  // MATRIX_HPP