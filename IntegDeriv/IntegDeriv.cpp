//
// Created by joao_martins on 15-06-2023.
//

#include "IntegDeriv.h"

IntegDeriv ::IntegDeriv(Functor& f): func(f){}

double IntegDeriv::first_derivative(double x, double h){
    double retorno;
    retorno = ((func(x-2*h)+8*func(x+h))-(8*func(x-h)+func(x+2*h)))/(12*h);
    return retorno;
}

double IntegDeriv ::second_derivative(double x, double h){
    double retorno;
    retorno = (-func(x-2*h)+16*func(x-h)-30*func(x)+16*func(x+h)-func(x+2*h))/(12*h*h);
    return retorno;
}

double IntegDeriv ::fourth_derivative(double x, double h){
    double retorno;
    retorno = (-second_derivative(x-2*h,h)+16*second_derivative(x-h,h)-30*second_derivative(x,h)+
            16*second_derivative(x+h,h)-second_derivative(x+2*h,h))/(12*h*h);
    return retorno;
}
int IntegDeriv :: factorial(int n){
    if (n == 0) return 1;
    return n* factorial(n-1);
}

int IntegDeriv ::combination(int n, int k){
    return factorial(n)/(factorial(k)*factorial(n-k));
}

void IntegDeriv ::TrapezoidalRule(double xi, double xf, double& integral, double& erro){
    double Erro = erro;
    int it  = 32;
    while (erro >= Erro && it < pow(2, 12)){
        double step = abs(xf-xi)/it;
        double soma = 0;
        double x = xi;
        vector <double> derivadas;
        for (int i = 0; i < it; i++){
            soma += func(x) + func(x + step);
            x+= step;
            derivadas.push_back(abs(second_derivative(x,step)));
        }
        integral = step*soma/2;
        double M = *max_element(derivadas.begin(), derivadas.end());
        erro = M*pow(xf-xi, 3)/(it*it*12);
        it *= 2;
    }
}

void IntegDeriv ::simpsonRule(double xi, double xf, double& integral, double& erro){
    double Erro = erro;
    int it = 2;
    while (erro >= Erro && it < pow(2, 12)){
        double step = (xf-xi)/it;
        double soma = 0;
        double x = xi+step;
        vector <double> derivadas;
        for (int i = 0; i < it/2; i++){
            soma += func(x-step) + 4*func(x) + func(x+step);
            x += 2*step;
            derivadas.push_back(fourth_derivative(x,step));
        }
        integral = step*soma/3;
        double M = *max_element(derivadas.begin(), derivadas.end());
        erro = M*pow(xf-xi, 5)/(180*pow(it, 4));
        it *= 2;
    }
}

void IntegDeriv :: integrateMC(double xi, double xf, double& integral, double& erro, int& seed) {
    minstd_rand R(seed);
    uniform_real_distribution<double> D(xi, xf);
    int it = 8;
    double Erro = erro;
    while (erro >= Erro && it < pow(2, 12)) {
        double soma1 = 0;
        double soma2 = 0;
        for (int i = 0; i < it; i++) {
            double valor = func(D(R));
            soma1 += valor;
            soma2 += valor * valor;
        }
        integral = ((xf - xi) / it) * soma1;

        erro = ((xf - xi) / sqrt(it)) * sqrt(soma2 / it - (soma1 / it) * (soma1 / it));
        it *= 2;
    }
}


void IntegDeriv ::integrateMC_2D(double xi, double xf, double yi, double yf, function<double(double,double)> F,double& integral, double& erro, int& seed) {
    minstd_rand R1(seed);
    minstd_rand R2(time(0) + seed);
    uniform_real_distribution<double> D1(xi,xf);
    uniform_real_distribution<double> D2(yi, yf);
    double diferenca = erro;
    int it = 10000;
    while (diferenca >= erro && it < 1.E6){
        double integral_ant = integral;
        double soma = 0;
        for (int i = 0; i < it; i++){
            soma += F(D1(R1), D2(R2));
        }
        integral = (xf-xi)*(yf-yi)*soma/it;
        diferenca = abs(integral_ant-integral);
        it += 100;
    }
}

void IntegDeriv ::MidPoint(double xi, double xf, int fatias, double& integral, double& erro){
    double step = (xf-xi)/fatias;
    double soma = 0;
    vector <double> derivadas;
    for (int i = 0; i < fatias; i++){
        double p_medio = (xi+step*i + xi+step*(i+1))/2;
        soma += step * func(p_medio);
        derivadas.push_back(abs(second_derivative(xi + step*i,step)));
    }
    double max_derivada = *max_element(derivadas.begin(), derivadas.end());
    integral = soma;
    erro = max_derivada*pow(xf-xi, 3)/(24*fatias*fatias);
}
/*
double IntegDeriv ::n_derivative(double x, double h, int n) {
    double soma = 0;
    for (int k = 0; k < n; k++){
        soma += pow(-1,n+k)* combination(n,k)*func(x+k*h);
    }
    return soma/pow(h,n);

}*/