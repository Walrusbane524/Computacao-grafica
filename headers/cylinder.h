#pragma once

#include "compound_object.h"

class Cylinder : public CompoundObject{
    public:

        Point base_center;
        Point top_center;
        double radius;

        optional<LitPoint> colide(Ray ray) const override;

        Cylinder(Point base_center, Point top_center, double radius);
        Cylinder(Point base_center, Point top_center, double radius, Material material);
        Cylinder(Point base_center, Vector direction, double radius, double height);
        Cylinder(Point base_center, Vector direction, double radius, double height, Material material);
    
    private:
        Vector get_normal(Point p) const;
};
