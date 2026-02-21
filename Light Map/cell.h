//
// Created by joao_martins on 08-06-2023.
//

#ifndef HW3_CELL_H
#define HW3_CELL_H

#include <array>
using namespace std;

struct cell{
    array <float,3> center;
    int coordinates [2];
    float area;
    float power;
};

#endif //HW3_CELL_H
