//
// Created by joao_martins on 07-06-2023.
//

#include "lightmap.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;

lightmap ::lightmap() = default;
lightmap ::lightmap(lightsource S, array<int,2> ncell, array<float,2> size):nx(ncell[0]), ny(ncell[1]), length(size[0]), width(size[1]){
    luzinhas.push_back(S);
    dx = length/ ncell[0];
    dy = width/ ncell[1];
    float area = dx * dy;
    for (int i = 0; i < ncell[0]; i++){
        vector <cell> vetor;
        for (int j = 0; j < ncell[1]; j++){
            cell celula;
            celula.area = area;
            celula.coordinates[0] = i;
            celula.coordinates[1] = j;
            celula.center[0] = i * dx + dx / 2;
            celula.center[1] = j * dy + dy / 2;
            celula.center[2] = 0;
            float irradiancia = Irradiance(celula.center);
            celula.power = irradiancia;
            vetor.push_back(celula);
        }
        GRID.push_back(vetor);
    }
}

lightmap ::lightmap (array<int,2> ncell, array<float,2> size):nx(ncell[0]), ny(ncell[1]), length(size[0]), width(size[1]) {
    dx = length/ ncell[0];
    dy = width/ ncell[1];
    float area = dx * dy;
    for (int i = 0; i < ncell[0]; i++){
        vector <cell> vetor;
        for (int j = 0; j < ncell[1]; j++){
            cell celula;
            celula.area = area;
            celula.coordinates[0] = i;
            celula.coordinates[1] = j;
            celula.center[0] = i * dx + dx / 2;
            celula.center[1] = j * dy + dy / 2;
            celula.center[2] = 0;
            vetor.push_back(celula);
        }
        GRID.push_back(vetor);
    }
}

float lightmap :: distance2cell(array<float, 3> SourceCoo, array<float,3> PointCoo){
    float distance = sqrt((SourceCoo[0]-PointCoo[0])*(SourceCoo[0]-PointCoo[0]) + (SourceCoo[1]-PointCoo[1])*(SourceCoo[1]-PointCoo[1])+ (SourceCoo[2]-PointCoo[2])*(SourceCoo[2]-PointCoo[2]));
    return distance;
}

float lightmap :: Irradiance(array<float,3> PointCoo){
    float irradiancia = 0;
    for (int i = 0; i < luzinhas.size(); i++){
        irradiancia += (luzinhas[i].power * luzinhas[i].coo[2])/(4*M_PI*pow(distance2cell(luzinhas[i].coo, PointCoo),3));
    }
    return irradiancia;
}

pair <int, int> lightmap :: GetCellIndex(float x, float y) const{
    pair <int, int> retorno;
    retorno.first = floor(x/dx);
    retorno.second = floor(y/dy);
    return retorno;
}

pair <float,float> lightmap :: GetCellCoo(int x, int y) const {
    pair<float, float> retorno;
    for (int i = 0; i < GRID.size(); i++){
        for (int j = 0; j < GRID[i].size(); j++){
            if (GRID[i][j].coordinates[0] == x && GRID[i][j].coordinates[1] == y) {
                retorno.first = GRID[i][j].center[0];
                retorno.second = GRID[i][j].center[1];
                return retorno;
            }
        }
    }
    return retorno;
}

double lightmap :: GetCellPower(int index_x , int index_y) const{
    for (const auto &celulas: GRID) {
        for (const auto &celula: celulas) {
            if (*celula.coordinates == index_x && *(celula.coordinates + 1) == index_y) {
                return celula.power;
            }
        }
    }
    return 0;
}

double lightmap :: GetCellPower(float x, float y) const{
    pair <int, int> par = GetCellIndex(x,y);
    double power = GetCellPower(par.first, par.second);
    return power;
}

int lightmap:: GetCellNx() const{
    return nx;
}

int lightmap :: GetCellNy() const{
    return ny;
}

const cell& lightmap :: GetMaxCell(){
    int x = 0;
    int y = 0;

    for (int i = 0; i < GRID.size(); i++){
        for (int j = 0; j < GRID[i].size(); j++){
            if (GRID[i][j].power > GRID[x][y].power){x = i; y=j;}
        }
    }
    return GRID[x][y];
}

float lightmap :: CellPower(const cell& C){
    return C.power*C.area;
}

void lightmap :: AddLightSource (lightsource L){
    luzinhas.push_back(L);
    for (auto& celulas: GRID){
        for (auto& celula: celulas){
            celula.power = Irradiance(celula.center);
        }
    }
}

vector<vector<cell>> lightmap :: GetCells () const{
    return GRID;
}

float lightmap :: Total_Power(){
    float soma = 0;
    for (const auto& celulas: GRID){
        for (const auto& celula: celulas){
            soma += CellPower(celula);
        }
    }
    return soma;
}

void lightmap :: Print(){
    for (const auto& celulas: GRID){
        for (const auto& celula: celulas){
            cout << "{" << celula.center[0] << ", " << celula.center[1] << "}";
            cout << "{" << celula.coordinates[0] << ", " << celula.coordinates[1] << "}" << endl;
            cout << celula.area << ", " << celula.power << endl << endl;
        }
    }
}

array<float,3> lightmap :: GetNormal(){
    return {0,0,1};
}


