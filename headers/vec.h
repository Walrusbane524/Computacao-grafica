#pragma once

#include <math.h>
#include "color.h"

class Vec{
    public:
        double x, y, z;

        Vec();
        Vec(double x, double y, double z);
        Vec operator+(const Vec& v);
        Vec operator-(const Vec& v);
        Vec operator-(const Vec& v) const;
        Vec operator*(const double d);
        Vec operator*(const double d) const;
        Vec operator*(const Vec& v) const;
        Color operator*(const Color& c) const;
        Vec operator/(const double d);

        double dot(const Vec& v);
        double dot(const Vec& v) const;

        // Vectorial product
        Vec operator&(const Vec& v) const;

        double magnitude();
        Vec normalize();
};