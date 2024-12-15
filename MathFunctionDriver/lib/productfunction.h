//
// Created by Saeed Samimi on 5/24/2024.
//

#ifndef OBJECT_PRODUCTFUNCTION_H
#define OBJECT_PRODUCTFUNCTION_H
#include "basefunction.h"

class ProductFunction : public BaseFunction {
 private:
  BaseFunction *m_f1, *m_f2;

 public:
  ProductFunction(BaseFunction *func1, BaseFunction *func2);
  double evaluate(double input) override;
};

#endif  // OBJECT_PRODUCTFUNCTION_H
