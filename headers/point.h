#pragma once

#include "vec.h"
#include "matrix.h"

class Point : public Vec{
    public:
        Point();
        Point(Vec v);
        Point(double x, double y, double z);

        Point transform(Matrix matrix);
};