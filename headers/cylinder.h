#pragma once

#include "compound_object.h"

class Cylinder : public CompoundObject{
    public:

        Point base_center;
        Point top_center;
        double radius;

        optional<LitPoint> colide(Ray ray) const override;

        Cylinder(Point base_center, Point top_center, double radius, Color color);
        Cylinder(Point base_center, Point top_center, double radius, Color color, Material material);
        Cylinder(Point base_center, Vector direction, double radius, double height, Color color);
        Cylinder(Point base_center, Vector direction, double radius, double height, Color color, Material material);
    
    private:
        Vector get_normal(Point p) const override;
};
