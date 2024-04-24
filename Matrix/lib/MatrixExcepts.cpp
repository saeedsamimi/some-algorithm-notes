#include "MatrixExcepts.hpp"

const char *MatrixBadAlloc::what() const noexcept {
  return "The matrix rows and cols must be positive";
}

MatrixBadAlloc::MatrixBadAlloc() noexcept = default;

MatrixBadArithmeticCall::MatrixBadArithmeticCall() noexcept = default;

const char *MatrixBadArithmeticCall::what() const noexcept {
  return "The matrix arithmetic operation called bad, the evaluation cannot "
         "start";
}

MatrixOutOfRange::MatrixOutOfRange() noexcept
    : std::out_of_range("the index is out of range") {}
