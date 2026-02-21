//
// Created by joao_martins on 07-06-2023.
//
#include <iostream>
#include <string>
#include "Functor.h"
#include <cmath>
#include <vector>

using namespace std;

TCanvas* Functor :: c = nullptr;

Functor :: Functor (string s, double p1, double p2, double p3):name(s), param1(p1), param2(p2), param3(p3){
   c = new TCanvas("c", "canvas functor", 1000, 1000);
};

double Functor :: operator()(double x){
    return 0;
};

void Functor :: Draw (double xi, double xf, int num, string xtitle, string ytitle){

    double steps = (xf - xi)/num;
    vector <double> abxixas;
    vector <double> ordenadas;
    double x = xi;
    for (int i = 0; i < num; i++){
        abxixas.push_back(x);
        ordenadas.push_back((*this)(x));
        x+=steps;
    }

    TGraph* G = new TGraph(ordenadas.size(), abxixas.data(), ordenadas.data());
    G->SetLineColor(kRed+2);
    G->SetLineWidth(4);
    G->SetTitle("Functor");
    G->GetXaxis()-> SetTitle("x");
    G->GetYaxis()-> SetTitle("y");
    TApplication A("A",0,0);
    //c = new TCanvas("canvas", "", 1200, 1200);
    G->Draw();
    c->Update();
    gSystem -> ProcessEvents();
    c-> WaitPrimitive();

};
