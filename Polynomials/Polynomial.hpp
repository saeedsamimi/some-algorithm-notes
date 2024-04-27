#ifndef APP_POLYNOMIAL_HPP
#define APP_POLYNOMIAL_HPP

#include <ostream>
#include <vector>

class Polynomial;

class Term {
 public:
  Term(int coeff, int exp = 0);
  Term operator+() const;
  Term operator+(const Term &) const;
  Term operator-() const;
  Term operator-(const Term &) const;
  Term operator*(const Term &) const;
  int operator()(int) const;

  friend class Polynomial;

  friend std::ostream &operator<<(std::ostream &, const Polynomial &);

 private:
  int m_coeff, m_exp;

  struct Compare {
    bool operator()(const Term &, const Term &);
  };
};

class Polynomial : std::vector<Term> {
 public:
  Polynomial();
  Polynomial(const std::initializer_list<Term> &&);
  Polynomial operator+(const Term &) const;
  Polynomial operator+(const Polynomial &) const;
  Polynomial &operator+=(const Term &);
  Polynomial &operator+=(const Polynomial &);
  Polynomial operator*(const Term &) const;
  Polynomial operator*(const Polynomial &) const;
  Polynomial &operator*=(const Term &);
  Polynomial &operator*=(const Polynomial &);
  Polynomial operator-(const Term &) const;
  Polynomial operator-(const Polynomial &) const;
  Polynomial &operator-=(const Polynomial &);
  Polynomial &operator-=(const Term &);
  Polynomial operator+() const;
  Polynomial operator-() const;
  int operator()(int) const;
  friend std::ostream &operator<<(std::ostream &, const Polynomial &);
};

#endif  // APP_POLYNOMIAL_HPP
