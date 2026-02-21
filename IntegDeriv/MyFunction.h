//
// Created by joao_martins on 07-06-2023.
//

#ifndef HW4_MYFUNCTION_H
#define HW4_MYFUNCTION_H
#include "Functor.h"

class MyFunction: public Functor{
public:

    MyFunction(string s = "myfunction", double p1 = 0, double p2 = 0, double p3 = 0);
    ~MyFunction() = default;
    virtual double operator()(double);
};


#endif //HW4_MYFUNCTION_H
