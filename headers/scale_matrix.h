#pragma once
#include "matrix.h"

class ScaleMatrix : public Matrix{
    public:

    ScaleMatrix();
    ScaleMatrix(Vec multiplier);
};