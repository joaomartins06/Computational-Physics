//
// Created by joao_martins on 01-06-2023.
//

#include <iostream>
#include <vector>
#include <Eigen/Core>
using namespace std;
using namespace Eigen;

#include "FCmatrixAlgo.h"

void FCmatrixAlgo :: myfunc1(Matrix<double, Dynamic, Dynamic>& matriz, Matrix<double, Dynamic, 1>& constantes, int i){
    for (int j = i+1; j < matriz.rows(); j++){
        double lambda = matriz(j,i)/matriz(i,i);
        matriz.row(j) -= lambda * matriz.row(i);
        constantes.row(j) -= lambda * constantes.row(i);
    }
}

void FCmatrixAlgo :: organizer(Matrix<double, Dynamic, Dynamic>& matriz, Matrix<double, Dynamic, 1>& constantes, int i, int n){
    for(int j = i; j < matriz.rows()-1; j++){
        if (matriz(j,n) == 0){
            for (int k = j+1; k < matriz.rows(); k++) {
                if(matriz(k,n) != 0) {
                    matriz.row(j).swap(matriz.row(k));
                    constantes.row(j).swap(constantes.row(k));
                    organizer(matriz, constantes, j, n);
                    break;
                }
            }
        }
    }
}

void FCmatrixAlgo :: myfunc2(Matrix<double, Dynamic, Dynamic>& matriz, Matrix<double, Dynamic, 1>& constantes, int i){
    for(int j = i-1; j >= 0; j--){
        double lambda = matriz(j,i)/matriz(i,i);
        matriz.row(j) -= lambda * matriz.row(i);
        constantes.row(j) -= lambda * constantes.row(i);
    }
}

void FCmatrixAlgo ::pivoting(Matrix<double, Dynamic, Dynamic>& matriz, Matrix<double, Dynamic, 1>& constantes,  VectorXd& vetor, int i) {
    int x = i; int y = i;
    for (int j = i; j < matriz.rows(); j++){
        if (abs(matriz(j,i))/vetor(j) > abs(matriz(x,y))/vetor(x)){
            x = j; y = i;
        }
    }
    matriz.row(i).swap(matriz.row(x));
    constantes.row(i).swap(constantes.row(x));
    vetor.row(i).swap(vetor.row(x));
}


void FCmatrixAlgo ::GaussElimination(Matrix<double, Dynamic, Dynamic>& matriz, Matrix<double, Dynamic, 1>& constantes){
    for(int i = 0; i < matriz.rows()-1; i++){
        organizer(matriz, constantes, i, i);
        myfunc1(matriz, constantes, i);
    }

    for (int i = matriz.rows()-1; i >= 0; i--){
        myfunc2(matriz, constantes, i);
    }
}

void FCmatrixAlgo ::GaussEliminationPivot(Matrix<double, Dynamic, Dynamic>&  matriz, Matrix<double, Dynamic, 1>& constantes){
    VectorXd vetor = matriz.cwiseAbs().rowwise().maxCoeff();
    for (int i = 0; i < matriz.rows()-1; i++){
        pivoting(matriz, constantes, vetor, i);
        myfunc1(matriz, constantes, i);
    }
    for (int i = matriz.rows()-1; i >= 0; i--){
        myfunc2(matriz, constantes, i);
    }
}

void FCmatrixAlgo ::LUdecomposition(Matrix<double, Dynamic, Dynamic>& matriz, Matrix<double, Dynamic, 1>& constantes, bool bpivot) {
    if (!bpivot) {
        vector<vector<double>> vetores;
        for (int i = 0; i < matriz.rows() - 1; i++) {
            organizer(matriz, constantes, i, i);
            vector<double> lambdas;
            for (int j = i + 1; j < matriz.rows(); j++) {
                double lambda = matriz(j, i) / matriz(i, i);
                lambdas.push_back(lambda);
                matriz.row(j) -= lambda * matriz.row(i);
            }
            vetores.push_back(lambdas);
        }

        for (int i = 0; i < matriz.cols() - 1; i++) {
            for (int j = i + 1; j < matriz.rows(); j++) {
                matriz(j, i) = vetores[i][j - i - 1];
            }
        }
    }
    else{
        VectorXd vetor = matriz.cwiseAbs().rowwise().maxCoeff();
        vector<vector<double>> vetores;
        for (int i = 0; i < matriz.rows() - 1; i++) {
            vector<double> lambdas;
            pivoting(matriz, constantes, vetor, i);
            for (int j = i + 1; j < matriz.rows(); j++){
                double lambda = matriz(j, i) / matriz(i, i);
                matriz.row(j) -= lambda * matriz.row(i);
                lambdas.push_back(lambda);
            }
            vetores.push_back(lambdas);
        }
        for (int i = 0; i < matriz.cols() - 1; i++) {
            for (int j = i + 1; j < matriz.rows(); j++) {
                matriz(j, i) = vetores[i][j - i - 1];
            }
        }
    }
}

void FCmatrixAlgo :: Print(Matrix<double, Dynamic, Dynamic>& matriz, Matrix<double, Dynamic, 1>& constantes){
    for(int i = 0; i < matriz.rows(); i++){
        cout << matriz.row(i) << " | " << constantes.row(i) << endl;
    }
}