#pragma once
#include "matrix.h"
#include "vector.h"

class RotationMatrixYAxis : public Matrix{
    public:

    RotationMatrixYAxis();
    RotationMatrixYAxis(double** matrix);
    RotationMatrixYAxis(double radians);
};