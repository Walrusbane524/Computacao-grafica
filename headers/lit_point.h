#pragma once
#include "vec.h"
#include "vector.h"
#include "color.h"


class LitPoint: public Vec{
    public:
        Vector normal;
        double t;
        Color color;
        Vec roughness;
        Vec shine;

        LitPoint();
        LitPoint(Vec v, double t, Vector normal, Color color);
        LitPoint(Vec v, double t, Vector normal, Color color, Vec roughness, Vec shine);
        LitPoint(double x, double y, double z, double t, Vector normal, Color color);
        LitPoint(double x, double y, double z, double t, Vector normal, Color color, Vec roughness, Vec shine);
};