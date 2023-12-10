#include "../headers/rotation_matrix_x_axis.h"
#include <math.h>

RotationMatrixXAxis::RotationMatrixXAxis() : Matrix(){}

RotationMatrixXAxis::RotationMatrixXAxis(double** matrix) : Matrix(matrix){}

RotationMatrixXAxis::RotationMatrixXAxis(double angle_degrees){
    double radians = angle_degrees * (3.1415/180);
    this->matrix = new double* [4] {
        new double[4] {1,   0,               0,             0},
        new double[4] {0,   cos(radians),   -sin(radians),  0},
        new double[4] {0,   sin(radians),    cos(radians),  0},
        new double[4] {0,   0,               0,             1}
    };
}