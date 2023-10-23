#pragma once
#include "point.h"
#include "color.h"
#include "lit_point.h"
#include "object.h"
#include <vector>

class Light{
    public:
        double i_r;
        double i_g;
        double i_b;

        Light();
        Light(double i_r, double i_g, double i_b);

        virtual Vec get_diffuse_and_specular(LitPoint intersect, vector<Object*> objects, Ray camera_ray) const = 0;

        Vec operator*(const Vec v);
        Vec operator*(const Vec v) const;
};