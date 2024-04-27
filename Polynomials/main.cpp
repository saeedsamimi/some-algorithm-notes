#include <Polynomial.hpp>
#include <iostream>

using namespace std;

int main() {
  Polynomial p1{{1, 2}, {3, 4}, {5, 6}};
  cout << "Poly #1: " << p1 << endl;
  Polynomial p2{{2, 3}, {4, 5}, {4, 6}};
  cout << "Poly #2: " << p2 << endl;
  Polynomial p3{{4, 5}, {1, 2}, {6, 1}};
  cout << "Poly #3: " << p3 << endl;
  cout << "Poly1 + Poly2: " << p1 + p2 << endl;
  cout << "Poly1 + Poly3: " << p1 + p3 << endl;
  cout << "Poly2 + Poly3: " << p2 + p3 << endl;
  cout << "Poly1 + Poly2 + Poly3: " << p1 + p2 + p3 << endl;
  cout << "Ploy1 * poly3: " << p1 * p3 << endl;
  Polynomial p4{1, {2, 3}};
  cout << "Poly4 : " << p4 << endl;
  for (int i = -10; i <= 10; i++)
    cout << "Poly4 (x=" << i << "): " << p4(i) << endl;
  return 0;
}