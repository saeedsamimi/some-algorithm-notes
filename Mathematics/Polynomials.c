// Created by SAM-Tech on 1/22/2024.
#include <stdio.h>
#include <math.h>

#define MAX_TERM 1024

typedef struct {
  double coefficient;
  int exponent;
} Term;

typedef struct {
  int termCount;
  Term terms[MAX_TERM];
} Polynomial;

void insertTerm(Polynomial *, Term *);

void printPolynomial(Polynomial *);

int search(Polynomial *, int);

void sumPolynomial(Polynomial *, Polynomial *, Polynomial *);

void multiplyPolynomial(Polynomial *, Polynomial *, Polynomial *);

double valuePolynomial(Polynomial *, double);

void differentiationPolynomial(Polynomial *);

int main() {
  Polynomial poly;
  poly.termCount = 0;
  Term term = {25, 60};
  Term term2 = {24, 10};
  insertTerm(&poly, &term);
  insertTerm(&poly, &term2);
  insertTerm(&poly, &term2);
  Polynomial poly2 = poly;
  poly2.terms[0].exponent = 2;
  term2.exponent = 45;
  insertTerm(&poly2, &term2);
  term2.exponent = 20;
  insertTerm(&poly2, &term2);
  Polynomial temp;
  sumPolynomial(&poly, &poly2, &temp);
  printf("Poly1: ");
  printPolynomial(&poly);
  printf("Poly1(x=3): %.0lf\n", valuePolynomial(&poly, 3));
  printf("Poly2: ");
  printPolynomial(&poly2);
  printf("Poly2(x=2): %.0lf\n", valuePolynomial(&poly, 2));
  printf("Poly1 + Poly2: ");
  printPolynomial(&temp);
  printf("Poly1 + Poly2(x=1.1): %.5lf\n", valuePolynomial(&temp, 1.1));
  multiplyPolynomial(&poly, &poly2, &temp);
  printf("Poly1 * Poly2: ");
  printPolynomial(&temp);
  printf("Poly1 * Poly2(x=1.1): %.5lf\n", valuePolynomial(&temp, 1.1));
  differentiationPolynomial(&temp);
  printf("(Poly1 * Poly2)\': ");
  printPolynomial(&temp);
  return 0;
}

void insertTerm(Polynomial *poly, Term *term) {
  int index = search(poly, term->exponent);
  if (index == -1) {
    poly->terms[poly->termCount] = *term;
    int i = poly->termCount - 1;
    while (i >= 0 && poly->terms[i].exponent > term->exponent) {
      poly->terms[i + 1] = poly->terms[i];
      i--;
    }
    poly->terms[i + 1] = *term;
    poly->termCount++;
  } else
    poly->terms[index].coefficient += term->coefficient;
}

int search(Polynomial *poly, int exponent) {
  // using binary search
  int start = 0;
  int end = poly->termCount - 1;
  int middle;
  while (end >= start) {
    middle = (start + end) / 2;
    if (exponent > poly->terms[middle].exponent)
      start = middle + 1;
    else if (exponent < poly->terms[middle].exponent)
      end = middle - 1;
    else
      return middle;
  }
  return -1;
}

void printPolynomial(Polynomial *poly) {
  if (poly->termCount) {
    printf("%.0lf*x^%d", poly->terms[0].coefficient, poly->terms[0].exponent);
    for (int i = 1; i < poly->termCount; i++)
      printf(" + %.0lf*x^%d", poly->terms[i].coefficient, poly->terms[i].exponent);
    printf("\n");
  }
}

void sumPolynomial(Polynomial *p1, Polynomial *p2, Polynomial *out) {
  int i, j, k;
  i = j = k = 0;
  while (i < p1->termCount && j < p2->termCount) {
    if (p1->terms[i].exponent < p2->terms[j].exponent)
      out->terms[k] = p1->terms[i++];
    else if (p1->terms[i].exponent > p2->terms[j].exponent)
      out->terms[k] = p2->terms[j++];
    else {
      out->terms[k].exponent = p2->terms[j].exponent;
      out->terms[k].coefficient = p1->terms[i].coefficient + p2->terms[j].coefficient;
      i++, j++;
    }
    k++;
  }
  for (; i < p1->termCount; i++, k++)
    out->terms[k] = p1->terms[i];
  for (; j < p2->termCount; j++, k++)
    out->terms[k] = p2->terms[j];
  out->termCount = k;
}

void multiplyPolynomial(Polynomial *p1, Polynomial *p2, Polynomial *out) {
  out->termCount = 0;
  int i, j;
  Term tmp;
  for (i = 0; i < p1->termCount; i++)
    for (j = 0; j < p2->termCount; j++) {
      tmp.exponent = p1->terms[i].exponent + p2->terms[j].exponent;
      tmp.coefficient = p1->terms[i].coefficient * p2->terms[j].coefficient;
      insertTerm(out, &tmp);
    }
}

void differentiationPolynomial(Polynomial *p) {
  for (int i = 0; i < p->termCount; i++) {
    p->terms[i].coefficient *= p->terms[i].exponent;
    p->terms[i].exponent--;
  }
}

double valuePolynomial(Polynomial *f, double x) {
  double buff = 0;
  for (int i = 0; i < f->termCount; i++)
    buff += f->terms[i].coefficient * pow(x, f->terms[i].exponent);
  return buff;
}