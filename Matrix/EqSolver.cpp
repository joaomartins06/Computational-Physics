//
// Created by joao_martins on 07-06-2023.
//

#include "EqSolver.h"

using namespace std;
using namespace Eigen;


EqSolver :: EqSolver (Matrix <double, Dynamic, Dynamic>& matriz, Matrix <double, Dynamic, 1>& constantes){
    M = matriz;
    b = constantes;
}

void EqSolver::Print() {
    cout << "Matriz:" << endl;
    cout << M << endl;
    cout << "constantes:" << endl;
    cout << b << endl;
}

const Matrix <double, Dynamic, 1> EqSolver :: GaussSolver(bool pivot){
    FCmatrixAlgo alg;
    Matrix <double, Dynamic, Dynamic> matriz;
    Matrix <double, Dynamic, 1> constantes;
    matriz = M; constantes = b;
    if (pivot){
        alg.GaussEliminationPivot(matriz, constantes);
    }
    else{
        alg.GaussElimination(matriz, constantes);
    }
    for (int i = 0; i < matriz.rows(); i++){
        constantes.row(i) = constantes.row(i)/matriz(i, i);
    }
    return constantes;
}

const Matrix <double, Dynamic, 1> EqSolver :: LUSolver(bool pivot){
    FCmatrixAlgo alg;
    Matrix <double, Dynamic, Dynamic> matriz;
    Matrix <double, Dynamic, 1> constantes;
    matriz = M; constantes = b;
    Matrix <double, Dynamic, Dynamic> L (matriz.rows(), matriz.cols());
    L.setIdentity();
    Matrix <double, Dynamic, Dynamic> U (matriz.rows(), matriz.cols());
    alg.LUdecomposition(matriz, constantes, pivot);
    for (int i = 0; i < matriz.rows(); i++){
        for (int j = 0; j < i; j++){
            L(i,j) = matriz(i,j);
        }
    }

    for (int i = 0; i < matriz.rows(); i++){
        for (int j = i; j < matriz.cols(); j++){
            U(i,j) = matriz(i,j);
        }
    }

    Matrix <double, Dynamic, 1> y (matriz.rows(),1);
    for (int k = 0; k < matriz.rows(); k++){
        double sum = 0;
        for (int i = 0; i < k; i++){
            sum += y(i,0) * L(k,i);
        }
        y(k,0) = constantes(k,0) - sum;
    }

    Matrix <double, Dynamic, 1> solutions (matriz.rows(),1);
    for (int k = matriz.rows()-1; k >= 0; k--){
        double sum = 0;
        for (int i = k+1; i < matriz.rows(); i++){
            sum += solutions(i,0) * U(k,i);
        }
        solutions (k,0) = (y(k,0)-sum)/U(k,k);
    }
    return solutions;
}

bool EqSolver :: diagonal_dominant(){
    for (int i = 0; i < M.rows(); i++){
        double pivot = M(i,i);
        double sum = M.cwiseAbs().row(i).sum()-abs(pivot);
        if (abs(pivot) < sum) return false;
    }
    return true;
}

bool EqSolver :: tester (Matrix <double, Dynamic, 1> vetor1, Matrix <double, Dynamic, 1> vetor2, double tol){
    for (int i = 0; i < vetor1.rows(); i++){
        if(abs(vetor1(i, 0) - vetor2(i,0)) > tol) {
            return false;
        }
    }
    return true;
}

void EqSolver :: IterativeJacobiSolver(Matrix <double, Dynamic, 1>& x, int itmax, double tol){
    bool btol = false;
    int it = 0;
    Matrix <double, Dynamic, 1> x_aux;
    while (!btol && (it++<itmax)){
        x_aux = x;
        for (int i = 0; i < M.rows(); i++){
            x(i,0) = 0;
            for (int j = 0; j < M.rows(); j++) {
                if (i != j) x(i, 0) += -M(i, j) * x_aux(j, 0);
            }
            x(i,0) += b(i,0);
            x(i,0) /= M(i,i);
            btol = tester(x, x_aux, tol);
            //btol = tester(x, x_aux, tol);
            //if (tester(x, x_aux, tol)) btol = true;
            //else btol = false;

        }
    }
    if (it == itmax-1){
        cout << "As soluções divergiram, logo podem não ser satisfatórios" << endl;
    }

}

void EqSolver::IterativeGaussSeidelSolver(Matrix <double, Dynamic, 1>& x, int itmax, double tol){
    x.setZero();
    Matrix <double, Dynamic, 1> x_aux;
    x_aux.setZero();
    bool btol = false;
    int it = 0;
    while (!btol && (it++ < 1000)){
        x_aux = x;
        for (int i=0; i<M.rows(); i++){
            x(i,0) = 0;
            for (int j=0; j<M.rows(); j++){
                if (i != j) x(i,0) += -M(i,j)*x(j,0);
            }
            x(i,0) += b(i,0);
            x(i,0) /= M(i,i);
            btol = tester(x, x_aux, tol);
        }
    }
    cout << it;
    if (it == itmax-1){
        cout << "As soluções divergiram, logo podem não ser satisfatórios" << endl;
    }
}

