#ifndef LIGHT
#define LIGHT
#include "point.h"
#include "color.h"

class Light{
    public:
        Point point;
        double i_r;
        double i_g;
        double i_b;

        Light();
        Light(Point point, double i_r, double i_g, double i_b);

        Vec operator*(const Vec v);
        Vec operator*(const Vec v) const;
};
#endif