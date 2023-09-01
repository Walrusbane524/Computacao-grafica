#ifndef CYLINDER_FACE
#define CYLINDER_FACE

#include "object.h"

class CylindricalFace : public Object{
    public:
    Point base_center;
    Vector direction;
    double radius;
    double height;

    CylindricalFace();
    CylindricalFace(Point center, Vector direction, double radius, double height, Color color);

    optional<double> colide(Ray ray) const override;
};

#endif