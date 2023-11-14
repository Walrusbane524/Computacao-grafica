#pragma once

#include "vec.h"
#include "point.h"

class Vector : public Vec{
    public:
    Vector();
    Vector(Vec v);
    Vector(Point p);
    Vector(double x, double y, double z);
};