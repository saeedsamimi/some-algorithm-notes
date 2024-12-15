//
// Created by Saeed Samimi on 5/24/2024.
//

#ifndef OBJECT_TERMFUNCTION_H
#define OBJECT_TERMFUNCTION_H

#include "basefunction.h"

class TermFunction : public BaseFunction {
 private:
  double m_coeff, m_exp;

  friend class PolynomialFunction;

  struct Compare {
    bool operator()(const TermFunction *, const TermFunction *);
  };

 public:
  TermFunction(double coeff, double exp = 0);
  double evaluate(double input) override;
};

#endif  // OBJECT_TERMFUNCTION_H
