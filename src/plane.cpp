#include <optional>
#include "../headers/plane.h"

Plane::Plane(){
    this->center = Point(0, -10, 0);
    this->color = Color();
    this->normal = Vector(0, 1, 0);
    this->material = Material();
};

Plane::Plane(Point center, Vector normal, Color color){
    this->center = center;
    this->normal = normal;
    this->color = color;
    this->material = Material();
}
Plane::Plane(Point center, Vector normal, Color color, Material material){
    this->center = center;
    this->normal = normal;
    this->color = color;
    this->material = material;
}

optional<LitPoint> Plane::colide(Ray ray) const {
    double divisor = normal.dot(ray.direction);

    if(divisor == 0.0) return nullopt;

    Vector w = ray.p_inicial - center;

    double t = -(normal.dot(w)/divisor);
    Point p_intersect = ray.p_inicial + (ray.direction * t);

    return LitPoint(p_intersect, t, this->normal, this->color, this->material);
};

Vector Plane::get_normal(Point p) const{
    return this->normal;
}