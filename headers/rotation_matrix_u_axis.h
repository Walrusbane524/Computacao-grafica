#pragma once
#pragma once
#include "matrix.h"
#include "vector.h"

class RotationMatrixUAxis : public Matrix{
    public:

    RotationMatrixUAxis();
    RotationMatrixUAxis(double** matrix);
    RotationMatrixUAxis(Vector u, double angle_degrees);
};