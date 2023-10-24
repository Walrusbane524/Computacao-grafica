#pragma once
#include "matrix.h"
#include "vector.h"

class TranslationMatrix : public Matrix{
    public:

    TranslationMatrix();
    TranslationMatrix(double** matrix);
    TranslationMatrix(Vector v);
};