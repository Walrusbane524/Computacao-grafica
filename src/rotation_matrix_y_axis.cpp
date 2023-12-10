#include "../headers/rotation_matrix_y_axis.h"
#include <math.h>

RotationMatrixYAxis::RotationMatrixYAxis() : Matrix(){}

RotationMatrixYAxis::RotationMatrixYAxis(double** matrix) : Matrix(matrix){}

RotationMatrixYAxis::RotationMatrixYAxis(double angle_degrees){
    double radians = angle_degrees * (3.1415/180);
    this->matrix = new double* [4] {
        new double[4] { cos(radians),   0,    sin(radians),     0},
        new double[4] {            0,   1,               0,     0},
        new double[4] {-sin(radians),   0,    cos(radians),     0},
        new double[4] {            0,   0,               0,     1}
    };
}