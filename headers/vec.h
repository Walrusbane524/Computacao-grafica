#ifndef VEC
#define VEC
#include <math.h>

class Vec{
    public:
        double x, y, z;

        Vec();
        Vec(double x, double y, double z);
        Vec operator+(const Vec& v);
        Vec operator-(const Vec& v);
        Vec operator*(const double d);
        Vec operator*(const Vec& v);
        Vec operator/(const double d);
        double dot(const Vec& v);
        double modulo();
};

#endif