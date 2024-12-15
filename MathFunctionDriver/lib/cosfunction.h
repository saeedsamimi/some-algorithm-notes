//
// Created by Saeed Samimi on 5/24/2024.
//

#ifndef OBJECT_COSFUNCTION_H
#define OBJECT_COSFUNCTION_H
#include "basefunction.h"

class CosFunction : public BaseFunction {
 private:
  BaseFunction *m_func;

 public:
  CosFunction(BaseFunction *func1);
  double evaluate(double input) override;
};

#endif  // OBJECT_COSFUNCTION_H
