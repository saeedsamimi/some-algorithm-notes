//
// Created by Saeed Samimi on 5/24/2024.
//
#include "polynomialfunction.h"

#include <algorithm>

PolynomialFunction::PolynomialFunction(
    const std::initializer_list<TermFunction *> &&terms)
    : m_terms(terms) {
  std::sort(m_terms.begin(), m_terms.end(), TermFunction::Compare());
  auto iter = m_terms.begin() + 1;
  while (iter < m_terms.end()) {
    if ((*iter)->m_exp == (*(iter - 1))->m_exp) {
      (*(iter - 1))->m_coeff += (*iter)->m_coeff;
      m_terms.erase(iter);
      if ((*(iter - 1))->m_coeff == 0) m_terms.erase(iter - 1);
    } else
      iter++;
  }
}

double PolynomialFunction::evaluate(double input) {
  double sum = 0;
  for (auto term : m_terms) sum += term->evaluate(input);
  return sum;
}
