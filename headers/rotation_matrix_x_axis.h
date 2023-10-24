#pragma once
#include "matrix.h"
#include "vector.h"

class RotationMatrixXAxis : public Matrix{
    public:

    RotationMatrixXAxis();
    RotationMatrixXAxis(double** matrix);
    RotationMatrixXAxis(double radians);
};