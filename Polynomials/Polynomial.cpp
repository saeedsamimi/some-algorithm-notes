#include "Polynomial.hpp"

#include <algorithm>
#include <cmath>

Polynomial::Polynomial() : std::vector<Term>() {}

Polynomial::Polynomial(const std::initializer_list<Term> &&terms)
    : std::vector<Term>(terms) {
  std::sort(begin(), end(), Term::Compare());
  auto iter = begin() + 1;
  while (iter < end()) {
    if (iter->m_exp == (iter - 1)->m_exp) {
      (iter - 1)->m_coeff += iter->m_coeff;
      erase(iter);
      if (!(iter - 1)->m_coeff) erase(iter - 1);
    } else
      iter++;
  }
}

Polynomial Polynomial::operator+(const Term &t) const {
  Polynomial temp = *this;
  temp += t;
  return temp;
}

std::ostream &operator<<(std::ostream &os, const Polynomial &polynomial) {
  for (const Term &term : polynomial)
    os << std::showpos << term.m_coeff << std::noshowpos << "x^" << term.m_exp
       << ' ';
  return os;
}

Polynomial Polynomial::operator+(const Polynomial &poly) const {
  auto iter1 = begin();
  auto iter2 = poly.begin();
  Polynomial t;
  while (iter1 != end() && iter2 != poly.end()) {
    if (iter1->m_exp > iter2->m_exp) {
      t.push_back(*iter1);
      ++iter1;
    } else if (iter2->m_exp > iter1->m_exp) {
      t.push_back(*iter2);
      ++iter2;
    } else {
      Term out = *iter1 + *iter2;
      if (out.m_coeff) t.push_back(out);
      ++iter1;
      ++iter2;
    }
  }
  while (iter1 != end()) {
    t.push_back(*iter1);
    iter1++;
  }
  while (iter2 != poly.end()) {
    t.push_back(*iter2);
    iter2++;
  }
  return t;
}

Polynomial Polynomial::operator-(const Polynomial &poly) const {
  return operator+(-poly);
}

Polynomial Polynomial::operator-() const {
  Polynomial temp = *this;
  for (auto &item : temp) item = -item;
  return temp;
}

Polynomial Polynomial::operator-(const Term &t) const { return operator+(-t); }

Polynomial Polynomial::operator+() const { return *this; }

Polynomial Polynomial::operator*(const Term &t) const {
  Polynomial temp;
  for (auto &item : *this) temp.push_back(item * t);
  return temp;
}

Polynomial Polynomial::operator*(const Polynomial &poly) const {
  Polynomial temp;
  for (auto &item1 : *this)
    for (auto &item2 : poly) temp += item1 * item2;
  return temp;
}

Polynomial &Polynomial::operator+=(const Term &t) {
  auto iter = begin();
  while (iter != end() && iter->m_exp > t.m_exp) iter++;
  if (iter != end() && iter->m_exp == t.m_exp) {
    int newCoeff = iter->m_coeff + t.m_coeff;
    if (newCoeff)
      iter->m_coeff = newCoeff;
    else
      erase(iter);
  } else
    insert(iter, t);
  return *this;
}

Polynomial &Polynomial::operator+=(const Polynomial &poly) {
  return *this = this->operator+(poly);
}

int Polynomial::operator()(int a) const {
  int sum = 0;
  for (auto &item : *this) sum += item(a);
  return sum;
}

Polynomial &Polynomial::operator-=(const Polynomial &poly) {
  return *this = this->operator-(poly);
}

Polynomial &Polynomial::operator-=(const Term &t) {
  return *this = this->operator-(t);
}

Polynomial &Polynomial::operator*=(const Term &t) {
  return *this = this->operator*(t);
}

Polynomial &Polynomial::operator*=(const Polynomial &poly) {
  return *this = this->operator*(poly);
}

Term::Term(int coeff, int exp) : m_coeff(coeff), m_exp(exp) {}

Term Term::operator+() const { return *this; }

Term Term::operator+(const Term &t) const {
  if (t.m_exp == m_exp) return {t.m_coeff + m_coeff, m_exp};
  throw std::invalid_argument(
      "The right operand must be the same as left operand in exponentiation");
}

Term Term::operator-() const { return {-m_coeff, m_exp}; }

Term Term::operator-(const Term &t) const { return operator+(-t); }

Term Term::operator*(const Term &t) const {
  return {t.m_coeff * m_coeff, t.m_exp + m_exp};
}

int Term::operator()(int a) const { return m_coeff * std::pow(a, m_exp); }

bool Term::Compare::operator()(const Term &t1, const Term &t2) {
  return t1.m_exp > t2.m_exp;
}
