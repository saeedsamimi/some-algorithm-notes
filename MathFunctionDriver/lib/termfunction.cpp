//
// Created by Saeed Samimi on 5/24/2024.
//

#include "termfunction.h"
#include <cmath>

bool TermFunction::Compare::operator()(const TermFunction *term1, const TermFunction *term2) {
  return term1->m_exp > term2->m_exp;
}

TermFunction::TermFunction(double coeff, double exp)
        : m_coeff(coeff), m_exp(exp) {}

double TermFunction::evaluate(double input) {
  return m_coeff * std::pow(input,m_exp);
}
