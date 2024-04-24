#ifndef MATRIX_EXCEPTS_HPP
#define MATRIX_EXCEPTS_HPP

#include <stdexcept>

class MatrixBadAlloc : std::bad_alloc {
 public:
  MatrixBadAlloc() noexcept;
  [[nodiscard]] const char *what() const noexcept override;
};

class MatrixBadArithmeticCall : std::bad_exception {
 public:
  MatrixBadArithmeticCall() noexcept;
  [[nodiscard]] const char *what() const noexcept override;
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() noexcept;
};

#endif  // MATRIX_EXCEPTS_HPP
