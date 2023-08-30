#ifndef SPHERE
#define SPHERE

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
    optional<double> colide(Ray ray) const override;
};

#endif