//
// Created by Saeed Samimi on 5/24/2024.
//

#ifndef OBJECT_SINFUNCTION_H
#define OBJECT_SINFUNCTION_H

#include "basefunction.h"

class SinFunction : public BaseFunction {
private:
  BaseFunction *m_func;

public:
  SinFunction(BaseFunction *func1);
  double evaluate(double input) override;
};


#endif //OBJECT_SINFUNCTION_H
