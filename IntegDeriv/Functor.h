//
// Created by joao_martins on 07-06-2023.
//

#ifndef HW4_FUNCTOR_H
#define HW4_FUNCTOR_H
#include <iostream>
#include <string>

#include "TCanvas.h"
#include "TApplication.h"
#include "TGraph.h"
#include "TSystem.h"
#include "TAxis.h"

using namespace std;

class Functor {
public:
    Functor(string s = "Functor", double p1 = 0, double p2 = 0, double p3 = 0);
    ~Functor() = default;
    virtual void Draw( double, double, int, string xtitle = "x", string ytitle = "y");
    virtual double operator()(double x);

protected:
    static TCanvas *c;
    string name;
    //Caso haja necessecidade de acrescentar parâmetros a funções
    double param1;
    double param2;
    double param3;
};


#endif //HW4_FUNCTOR_H
