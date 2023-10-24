#pragma once
#include "matrix.h"
#include "vector.h"

class RotationMatrixZAxis : public Matrix{
    public:

    RotationMatrixZAxis();
    RotationMatrixZAxis(double** matrix);
    RotationMatrixZAxis(double radians);
};