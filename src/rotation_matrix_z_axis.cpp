#include "../headers/rotation_matrix_z_axis.h"
#include <math.h>

RotationMatrixZAxis::RotationMatrixZAxis() : Matrix(){}

RotationMatrixZAxis::RotationMatrixZAxis(double** matrix) : Matrix(matrix){}

RotationMatrixZAxis::RotationMatrixZAxis(double radians){
    this->matrix = new double* [4] {
        new double[4] {cos(radians),   -sin(radians),    0,     0},
        new double[4] {sin(radians),    cos(radians),    0,     0},
        new double[4] {           0,               0,    1,     0},
        new double[4] {           0,               0,    0,     1}
    };
}