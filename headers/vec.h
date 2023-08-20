#ifndef VEC
#define VEC
#include <math.h>

class Vec{
    public:
        double x, y, z;

        Vec();
        Vec(double x, double y, double z);
        Vec operator+(Vec& v);
        Vec operator-(Vec& v);
        Vec operator*(double d);
        Vec operator*(Vec& v);
        Vec operator/(double d);
        double dot(Vec& v);
        double modulo();
};

#endif