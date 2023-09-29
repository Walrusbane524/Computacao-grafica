#pragma once

#include <optional>
#include "plane.h"

class Triangle : public Object{
    public:
        Plane plane;
        Point p1;
        Point p2;
        Point p3;

        Triangle();
        Triangle(Vector normal, Point p1, Point p2, Point p3, Material material);
        optional<LitPoint> colide(Ray ray) const override;

    private:
        Vector get_normal(Point p) const override;
};
