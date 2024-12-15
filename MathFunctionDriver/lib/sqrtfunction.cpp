//
// Created by Saeed Samimi on 5/24/2024.
//

#include "sqrtfunction.h"

#include <cmath>

double SqrtFunction::evaluate(double input) {
  return std::sqrt(m_func->evaluate(input));
}

SqrtFunction::SqrtFunction(BaseFunction *func1) : m_func(func1) {}
