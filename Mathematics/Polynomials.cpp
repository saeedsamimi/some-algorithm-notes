#include "Polynomials.h"
#include <iostream>

using namespace std;

int main() {
  Polynomials poly;
  poly.insertTerm(2, 3);
  poly.insertTerm(3, 5);
  poly.insertTerm(1, 3);
  Term term(2,3);
  poly += term;
  for (int i = 0; i < 50; i++)
    poly.insertTerm(60 - i, i + 1);
  cout << poly;
  return 0;
}