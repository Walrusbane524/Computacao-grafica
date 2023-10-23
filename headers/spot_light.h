#pragma once
#include "point_light.h"

class SpotLight : public PointLight{
    public:
        Vector direction;
        double angle_degrees;

        SpotLight();
        SpotLight(Point point,  Vector direction, double angle_degrees, double i_r, double i_g, double i_b);

        Vec get_diffuse_and_specular(LitPoint intersect, vector<Object*> objects, Ray camera_ray) const override;
};