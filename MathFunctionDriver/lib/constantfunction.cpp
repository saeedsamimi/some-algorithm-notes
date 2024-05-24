//
// Created by Saeed Samimi on 5/24/2024.
//

#include "constantfunction.h"

double ConstantFunction::evaluate(double) {
  return m_data;
}

ConstantFunction::ConstantFunction(double d)
        : m_data(d) {}
