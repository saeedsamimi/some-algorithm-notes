#include <Matrix.hpp>
#include <iostream>

#ifdef WIN32
#include <Windows.h>
#endif  // WIN32

using namespace std;

int main() {
#ifdef WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif
  Matrix a(3, 2, {1, 1, 1, 2, 2, 2});
  Matrix b(2, 3, {1, 2, 1, 1, 2, 2});
  Matrix r(5, 5, {1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 12, 14, 16,
                  18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40});
  cout << r;
  cout << "Determinant is: " << r.determinant() << endl;
  cout << "Matrix1: \n" << a;
  cout << "Matrix2: \n" << b;
  Matrix C(a * b);
  Matrix D(b * a);
  cout << "Matrix1 * Matrix2: \n" << C;
  cout << "And the |Mat1 * Mat2| = " << C.determinant() << endl;
  cout << "Matrix2 * Matrix1: \n" << b * a;
  cout << "And the |Mat2 * Mat1| = " << D.determinant() << endl;
  return 0;
}