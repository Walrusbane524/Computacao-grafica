#ifndef CONE
#define CONE

#include "point.h"
#include "compound_object.h"

class Cone : public CompoundObject{
    public:

    Point base_center;
    double radius;

    optional<double> colide(Ray ray) const override;

    Cone();
    Cone(Point base_center, Point tip, double radius, Color color);
    Cone(Point base_center, Vector direction, double radius, double height, Color color);
};

#endif