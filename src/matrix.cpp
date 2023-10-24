#include "../headers/matrix.h"

Matrix::Matrix(){
    this->matrix = new double* [4] {
        new double[4] {1, 0, 0, 0},
        new double[4] {0, 1, 0, 0},
        new double[4] {0, 0, 1, 0},
        new double[4] {0, 0, 0, 1}
    };
}

Matrix::Matrix(double** matrix){
    this->matrix = matrix;
}

double Matrix::at(int l, int c){
    return this->matrix[l][c];
}

Vec Matrix::operator*(Vec v){
    return Vec(
        v.x * matrix[0][0] + v.y * matrix[0][1] + v.z * matrix[0][2] + v.w * matrix[0][3],
        v.x * matrix[1][0] + v.y * matrix[1][1] + v.z * matrix[1][2] + v.w * matrix[1][3],
        v.x * matrix[2][0] + v.y * matrix[2][1] + v.z * matrix[2][2] + v.w * matrix[2][3],
        v.x * matrix[3][0] + v.y * matrix[3][1] + v.z * matrix[3][2] + v.w * matrix[3][3]
    );
}