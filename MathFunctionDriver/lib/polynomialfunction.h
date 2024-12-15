//
// Created by Saeed Samimi on 5/24/2024.
//

#ifndef OBJECT_POLYNOMIALFUNCTION_H
#define OBJECT_POLYNOMIALFUNCTION_H

#include <initializer_list>
#include <vector>

#include "basefunction.h"
#include "termfunction.h"

class PolynomialFunction : public BaseFunction {
  using Terms = std::vector<TermFunction *>;

 private:
  Terms m_terms;

 public:
  PolynomialFunction(const std::initializer_list<TermFunction *> &&);
  double evaluate(double input) override;
};

#endif  // OBJECT_POLYNOMIALFUNCTION_H
