#pragma once

#include <optional>
#include "point.h"
#include "color.h"
#include "object.h"
#include "ray.h"

class Sphere : public Object{
    public:
        Point center;
        double radius;

        Sphere();
        Sphere(Point center, double radius, Color color);
        Sphere(Point center, double radius, Color color, Vec roughness, Vec shine);
        optional<LitPoint> colide(Ray ray) const override;

    private:
        Vector get_normal(Point p) const override;
};
