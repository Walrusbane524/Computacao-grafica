#ifndef CYLINDER
#define CYLINDER

#include "compound_object.h"

class Cylinder : public CompoundObject{
    public:

    Point base_center;
    Point top_center;
    double radius;

    optional<double> colide(Ray ray) const override;

    Cylinder();
    Cylinder(Point base_center, Point top_center, double radius, Color color);
    Cylinder(Point base_center, Vector direction, double radius, double height, Color color);
};

#endif