//
// Created by joao_martins on 07-06-2023.
//

#ifndef HW3_LIGHTMAP_H
#define HW3_LIGHTMAP_H

#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include "cell.h"
#include "lightsource.h"

using namespace std;

class lightmap {
private:
    vector <vector<cell>> GRID;
    float width;
    float length;
    float dx;
    float dy;
    int nx;
    int ny;
    vector <lightsource> luzinhas;

public:
    lightmap();
    lightmap(lightsource S, array<int,2> ncell, array<float,2> size);
    lightmap (array<int,2> ncell, array<float,2> size);
    float distance2cell(array<float, 3> SourceCoo, array<float,3> PointCoo);
    float Irradiance(array<float,3> PointCoo);
    pair <int, int> GetCellIndex(float x, float y) const;
    pair <float,float> GetCellCoo(int x, int y) const;
    double GetCellPower(int index_x , int index_y) const;
    double GetCellPower(float x, float y) const;
    int GetCellNx() const;
    int GetCellNy() const;
    const cell& GetMaxCell();
    float CellPower(const cell& C);
    void AddLightSource (lightsource L);
    vector<vector<cell>> GetCells () const;
    float Total_Power();
    void Print();
    array<float,3> GetNormal();

};

#endif //HW3_LIGHTMAP_H
