#pragma once
#include "vec.h"
#include "vector.h"
#include "color.h"
#include "material.h"

class LitPoint: public Vec{
    public:
        Vector normal;
        double t;
        Color color;
        Material material;

        LitPoint();
        LitPoint(Vec v, double t, Vector normal, Color color);
        LitPoint(Vec v, double t, Vector normal, Color color, Material material);
        LitPoint(double x, double y, double z, double t, Vector normal, Color color);
        LitPoint(double x, double y, double z, double t, Vector normal, Color color, Material material);
};