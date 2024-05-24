//
// Created by Saeed Samimi on 5/24/2024.
//

#ifndef OBJECT_CONSTANTFUNCTION_H
#define OBJECT_CONSTANTFUNCTION_H
#include "basefunction.h"

class ConstantFunction : public BaseFunction{
private:
  double m_data;
public:
  ConstantFunction(double d);
  double evaluate(double) override;
};


#endif //OBJECT_CONSTANTFUNCTION_H
