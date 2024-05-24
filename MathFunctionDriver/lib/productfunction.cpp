//
// Created by Saeed Samimi on 5/24/2024.
//

#include "productfunction.h"

double ProductFunction::evaluate(double input) {
  return m_f1->evaluate(input) * m_f2->evaluate(input);
}

ProductFunction::ProductFunction(BaseFunction *func1, BaseFunction *func2)
        : m_f1(func1), m_f2(func2) {}
