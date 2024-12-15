#include <iostream>

#include "lib/function"

using namespace std;

int main() {
  ConstantFunction f1(12);
  ConstantFunction f2(34);
  ConstantFunction f3(13);
  ConstantFunction f4(14);

  cout << "f1: " << f1.evaluate(0) << endl;
  cout << "f2: " << f2.evaluate(0) << endl;
  cout << "f3: " << f3.evaluate(0) << endl;
  cout << "f4: " << f4.evaluate(0) << endl;

  SumFunction su1(&f1, &f2);
  SumFunction su2(&f3, &f4);

  cout << "sum1: f1 + f2: " << su1.evaluate(0) << endl;
  cout << "sum2: f3 + f4: " << su2.evaluate(0) << endl;

  ProductFunction prod1(&su1, &su2);
  ProductFunction prod2(&f3, &su2);

  cout << "prod1: sum1 * sum2: " << prod1.evaluate(0) << endl;
  cout << "prod1: f3 * sum2: " << prod2.evaluate(0) << endl;

  SumFunction sut(&prod1, &prod2);
  cout << "sut: prod1 + prod2: " << sut.evaluate(12) << endl;

  SqrtFunction sqrt1(new ConstantFunction(13));
  cout << "Sqrt(13): " << sqrt1.evaluate(0) << endl;

  TermFunction f(12, 3);
  cout << "12x^3 for [1,10]: " << endl;

  for (int i = 1; i <= 10; i++) cout << i << ": \t" << f.evaluate(i) << endl;

  PolynomialFunction g({new TermFunction{1, 1}, new TermFunction{-0.1, 2},
                        new TermFunction{4, 3}});

  cout << "x - 0.1x^2 + 4x^3 for [1,10]: " << endl;

  for (int i = 1; i <= 10; i++) cout << i << ": \t" << g.evaluate(i) << endl;

  SumFunction h(new TermFunction{.5, 2},
                new ProductFunction{new ConstantFunction{-10},
                                    new SinFunction{new TermFunction{1, 1}}});

  cout << "x^2/2 - 10sin(x): " << endl;
  for (int i = 1; i <= 10; i++) cout << i << ": \t" << h.evaluate(i) << endl;
}
