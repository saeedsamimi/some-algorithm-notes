//
// Created by Saeed Samimi on 5/24/2024.
//

#ifndef OBJECT_SUMFUNCTION_H
#define OBJECT_SUMFUNCTION_H

#include "basefunction.h"

class SumFunction : public BaseFunction {
 private:
  BaseFunction *m_f1, *m_f2;

 public:
  SumFunction(BaseFunction *func1, BaseFunction *func2);
  double evaluate(double input) override;
};

#endif  // OBJECT_SUMFUNCTION_H
