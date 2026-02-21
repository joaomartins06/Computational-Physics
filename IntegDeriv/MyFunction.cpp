//
// Created by joao_martins on 07-06-2023.
//
#include <cmath>
#include "MyFunction.h"

MyFunction :: MyFunction(string s, double p1, double p2, double p3): Functor (s, p1, p2, p3){};

double MyFunction :: operator()(double x){
   return (param1/param2)*exp(-x/(param2*param3));
}

