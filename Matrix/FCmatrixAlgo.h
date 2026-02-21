//
// Created by joao_martins on 01-06-2023.
//

#ifndef CIRCUITOELETRICO_FCMATRIXAGO_H
#define CIRCUITOELETRICO_FCMATRIXAGO_H


#include <iostream>
#include <Eigen/Core>
#include <vector>
using namespace std;
using namespace Eigen;


class FCmatrixAlgo {
public:
    FCmatrixAlgo() = default;
    ~FCmatrixAlgo() = default;

    static void GaussElimination(Matrix<double, Dynamic, Dynamic>&, Matrix<double, Dynamic, 1>&);
    static void GaussEliminationPivot(Matrix<double, Dynamic, Dynamic>&, Matrix<double, Dynamic, 1>&);
    static void myfunc1 (Matrix<double, Dynamic, Dynamic>&, Matrix<double, Dynamic, 1>&, int );
    static void Print(Matrix<double, Dynamic, Dynamic>&, Matrix<double, Dynamic, 1>&);
    static void LUdecomposition(Matrix<double, Dynamic, Dynamic>&, Matrix<double, Dynamic, 1>&, bool pivot = false);
    static void organizer(Matrix<double, Dynamic, Dynamic>&, Matrix<double, Dynamic, 1>&, int, int);
    static void myfunc2 (Matrix<double, Dynamic, Dynamic>&, Matrix<double, Dynamic, 1>&, int);
    static void pivoting(Matrix<double, Dynamic, Dynamic>&, Matrix<double, Dynamic, 1>&,  VectorXd&, int);
};


#endif //CIRCUITOELETRICO_FCMATRIXAGO_H
