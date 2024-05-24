//
// Created by Saeed Samimi on 5/24/2024.
//

#include "cosfunction.h"
#include <cmath>

CosFunction::CosFunction(BaseFunction *func1)
        : m_func(func1) {}

double CosFunction::evaluate(double input) {
  return std::cos(m_func->evaluate(input));
}
