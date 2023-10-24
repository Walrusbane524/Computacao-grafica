#pragma once
#include "vec.h"
#include <array>

class Matrix{
    public:
    double** matrix;


    Matrix();
    Matrix(double** matrix);

    double at(int l, int c);
    
    Vec operator*(Vec v);
    Matrix operator*(Matrix v);
};