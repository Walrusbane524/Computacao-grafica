#include "../headers/scale_matrix.h"

ScaleMatrix::ScaleMatrix() : Matrix(){}

ScaleMatrix::ScaleMatrix(Vec multiplier){
    this->matrix = new double* [4] {
        new double[4] {multiplier.x,              0,               0,              0},
        new double[4] {           0,   multiplier.y,               0,              0},
        new double[4] {           0,              0,    multiplier.z,              0},
        new double[4] {           0,              0,               0,              1}
    };
}