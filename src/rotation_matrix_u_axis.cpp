#include "../headers/rotation_matrix_u_axis.h"
#include <math.h>

RotationMatrixUAxis::RotationMatrixUAxis() : Matrix(){}

RotationMatrixUAxis::RotationMatrixUAxis(double** matrix) : Matrix(matrix){}

RotationMatrixUAxis::RotationMatrixUAxis(Vector u,double radians){
    u = u.normalize();
    this->matrix = new double* [4] {
        new double[4] {    cos(radians) + pow(u.x, 2) * (1 - cos(radians)),   u.x * u.y * (1 - cos(radians)) - u.z * sin(radians),   u.x * u.z * (1 - cos(radians)) + u.y * sin(radians),   0},
        new double[4] {u.y * u.x * (1 - cos(radians)) + u.z * sin(radians),       cos(radians) + pow(u.y, 2) * (1 - cos(radians)),   u.y * u.z * (1 - cos(radians)) - u.x * sin(radians),   0},
        new double[4] {u.z * u.x * (1 - cos(radians)) - u.y * sin(radians),   u.z * u.y * (1 - cos(radians)) + u.x * sin(radians),       cos(radians) + pow(u.z, 2) * (1 - cos(radians)),   0},
        new double[4] {                                                  0,                                                     0,                                                      0,  1}
    };
}