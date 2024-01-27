#pragma once

#include <iostream>

class Polynomials;

class Term;

using namespace std;

class Term {
public:
  explicit Term(unsigned int exponent = 0, double coefficient = 0) : exponent(exponent), coefficient(coefficient) {}
  double coefficient;
  unsigned int exponent;
};

class Polynomials {
public:
  Polynomials() : termsCount(0), terms() {}
  
  void operator +=(const Term &term){
    insertTerm(term);
  }
  void operator +=(const double &num){
    insertTerm(0,num);
  }
  void insertTerm(const Term &term){
    insertTerm(term.exponent,term.coefficient);
  }
  void insertTerm(const unsigned int exponent,const double coefficient) {
    int index = search(exponent);
    Term toSearch(exponent, coefficient);
    if (index == -1) {
      this->terms[this->termsCount] = toSearch;
      int i = this->termsCount - 1;
      while (i >= 0 && this->terms[i].exponent > exponent) {
        this->terms[i + 1] = this->terms[i];
        i--;
      }
      this->terms[i + 1] = toSearch;
      this->termsCount++;
    } else
      this->terms[index].coefficient += coefficient;
  }
  
  [[nodiscard]]int search(const unsigned int exponent) const{
    // using binary search
    int start = 0;
    int end = this->termsCount - 1;
    int middle;
    while (end >= start) {
      middle = (start + end) / 2;
      if (exponent > this->terms[middle].exponent)
        start = middle + 1;
      else if (exponent < this->terms[middle].exponent)
        end = middle - 1;
      else
        return middle;
    }
    return -1;
  }
  
  friend ostream &operator<<(ostream &out, const Polynomials &poly);
  
  const static int MAX_TERMS = 100;
private:
  Term terms[MAX_TERMS];
  int termsCount;
};

ostream &operator<<(ostream &out, const Polynomials &poly) {
  if (poly.termsCount > 0) {
    out << poly.terms->coefficient << "x^" << poly.terms->exponent;
    for (int i = 1; i < poly.termsCount; i++)
      out << " + " << poly.terms[i].coefficient << "x^" << poly.terms[i].exponent;
    out << endl;
  }
  return out;
}