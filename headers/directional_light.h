#pragma once
#include "light.h"

class DirectionalLight : public Light{
    public:
        Vector direction;

        DirectionalLight();
        DirectionalLight(Vector direction, double i_r, double i_g, double i_b);

        Vec get_diffuse_and_specular(LitPoint intersect, vector<Object*> objects, Ray camera_ray) const override;
};