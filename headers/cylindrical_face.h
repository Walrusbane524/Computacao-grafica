#pragma once

#include "object.h"

class CylindricalFace : public Object{
    public:
        Point base_center;
        Vector direction;
        double radius;
        double height;

        CylindricalFace();
        CylindricalFace(Point center, Vector direction, double radius, double height, Color color);
        CylindricalFace(Point center, Vector direction, double radius, double height, Color color, Vec roughness, Vec shine);

        optional<LitPoint> colide(Ray ray) const override;

    private:
        Vector get_normal(Point p) const override;
};
