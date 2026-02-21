//
// Created by joao_martins on 07-06-2023.
//

#ifndef CIRCUITOELETRICO_EQSOLVER_H
#define CIRCUITOELETRICO_EQSOLVER_H

#include <iostream>
#include <Eigen/Core>
#include <vector>
#include "FCmatrixAlgo.h"
using namespace std;
using namespace Eigen;


class EqSolver {
private:
    Matrix <double, Dynamic, Dynamic> M;
    Matrix <double, Dynamic, 1> b;

public:
    EqSolver(Matrix <double, Dynamic, Dynamic>&, Matrix <double, Dynamic, 1>&);
    void Print();
    const Matrix <double, Dynamic, 1> GaussSolver(bool pivot = false);
    const Matrix <double, Dynamic, 1> LUSolver(bool pivot = false);
    bool diagonal_dominant();
    bool tester (Matrix <double, Dynamic, 1>, Matrix <double, Dynamic, 1>, double);
    void IterativeJacobiSolver(Matrix <double, Dynamic, 1>&, int, double tol = 1.E-3);
    void IterativeGaussSeidelSolver(Matrix <double, Dynamic, 1>&, int, double tol = 1.E-3);

};


#endif //CIRCUITOELETRICO_EQSOLVER_H
