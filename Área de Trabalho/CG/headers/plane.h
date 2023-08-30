#ifndef PLANE
#define PLANE

#include <optional>
#include "point.h"
#include "color.h"
#include "object.h"
#include "ray.h"

class Plane : public Object{
    public:
    Point center;
    Vector normal;

    Plane();
    Plane(Point center, Vector normal, Color color);
    optional<double> colide(Ray ray) const override;
};

#endif