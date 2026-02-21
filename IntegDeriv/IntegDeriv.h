//
// Created by joao_martins on 15-06-2023.
//

#ifndef HW4_INTEGDERIV_H
#define HW4_INTEGDERIV_H
#include "Functor.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include <functional>

class IntegDeriv {

private:
    Functor& func;

public:
    IntegDeriv(Functor&);
    ~IntegDeriv() = default;

    double first_derivative(double, double);
    double second_derivative(double, double);
    double fourth_derivative(double, double);
    int factorial(int);
    int combination(int, int);
    void TrapezoidalRule(double, double, double&, double&);
    void MidPoint(double, double, int, double&, double&);
    void simpsonRule(double, double, double&, double&);
    void integrateMC(double, double, double&, double&, int&);
    //void integrateMC_IS(double, double, function<double(double, double)>, double&, int&);
    void integrateMC_2D(double, double, double, double, function<double(double,double)> ,double&, double&, int&);
};


#endif //HW4_INTEGDERIV_H
