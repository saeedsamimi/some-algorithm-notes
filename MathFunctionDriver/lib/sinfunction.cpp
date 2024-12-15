//
// Created by Saeed Samimi on 5/24/2024.
//

#include "sinfunction.h"

#include <cmath>

SinFunction::SinFunction(BaseFunction *func1) : m_func(func1) {}

double SinFunction::evaluate(double input) {
  return std::sin(m_func->evaluate(input));
}
