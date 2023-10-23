#pragma once
#include "light.h"

class PointLight : public Light{
    public:
        Point point;

        PointLight();
        PointLight(Point point, double i_r, double i_g, double i_b);

        Vec get_diffuse_and_specular(LitPoint intersect, vector<Object*> objects, Ray camera_ray) const override;
};