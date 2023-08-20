#ifndef RAY
#define RAY

#include "point.h"
#include "vector.h"

class Ray{
    public:
    Point p_inicial;
    Vector direction;

    Ray();
    Ray(Point p_inicial, Vector direction);
    Ray(Point p_inicial, Point p_ray);
};

#endif