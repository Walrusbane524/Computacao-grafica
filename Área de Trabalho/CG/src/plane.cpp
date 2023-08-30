#include <optional>
#include "../headers/plane.h"

Plane::Plane(){
    this->center = Point(0, -10, 0);
    this->color = Color();
    this->normal = Vector(0, 1, 0);
};

Plane::Plane(Point center, Vector normal, Color color){
    this->center = center;
    this->normal = normal;
    this->color = color;
}

optional<double> Plane::colide(Ray ray) const {
    double divisor = normal.dot(ray.direction);

    if(divisor == 0.0) return nullopt;

    Vector w = ray.p_inicial - center;

    return -(normal.dot(w)/divisor);
};