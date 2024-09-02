#include <iostream>
#include "Matrix.hpp"

int main()
{
    constexpr Matrix<2, 3, int> mat1{{1, 2, 3, 4, 5, 6}};
    constexpr Matrix<3, 2, int> mat2{{7, 8, 9, 10, 11, 12}};

    constexpr auto mat3 = mat1 * mat2;
    constexpr auto mat4 = mat1.transpose();

    std::cout << "Matrix 1:\n"
              << mat1;
    std::cout << "Matrix 2:\n"
              << mat2;
    std::cout << "Matrix 3 (Matrix 1 * Matrix 2):\n"
              << mat3;
    std::cout << "Matrix 4 (Transpose of Matrix 1):\n"
              << mat4;
    Matrix<3, 3, double> mat{{2, -1, -2, -4, 5, 3, -4, -2, 8}};

    auto [L, U] = mat.lu();
    std::cout << "mat: \n"
              << mat;
    std::cout << "Matrix L:\n"
              << L;
    std::cout << "Matrix U:\n"
              << U;
    std::cout << "Determinant of mat: " << mat.determinant() << std::endl;

    auto [R, UU] = mat.ru();
    std::cout << "Matrix R (RU Decomposition):\n"
              << R;
    std::cout << "Matrix UU (RU Decomposition):\n"
              << UU;

    constexpr auto mulMat = mat4.mul(mat2);
    std::cout << "Multipilcation of mat1 and mat2 is:\n"
              << mulMat;

    Matrix<4, 4, int> A = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16};

    // Compute the determinant of matrix A
    int detA = A.determinant();

    std::cout << "Determinant of A: " << detA << '\n';
    return 0;
}
