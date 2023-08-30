#ifndef VECTOR
#define VECTOR

#include "point.h"
#include "vec.h"

class Vector : public Vec{
    public:
    Vector();
    Vector(Vec v);
    Vector(Point p);
    Vector(double x, double y, double z);
};

#endif