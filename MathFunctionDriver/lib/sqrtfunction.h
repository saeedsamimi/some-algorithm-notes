//
// Created by Saeed Samimi on 5/24/2024.
//

#ifndef OBJECT_RADICALFUNCTION_H
#define OBJECT_RADICALFUNCTION_H

#include "basefunction.h"

class SqrtFunction : public BaseFunction {
private:
  BaseFunction *m_func;
public:
  SqrtFunction(BaseFunction *func1);
  double evaluate(double input) override;
};


#endif //OBJECT_RADICALFUNCTION_H
