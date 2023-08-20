#ifndef POINT
#define POINT
#include "vec.h"

class Point: public Vec{
    public:
        Point();
        Point(Vec v);
        Point(double x, double y, double z);
};
#endif