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
    this->roughness = Vec(1, 1, 1);
    this->shine = Vec(1, 1, 1);
}
Plane::Plane(Point center, Vector normal, Color color, Vec roughness, Vec shine){
    this->center = center;
    this->normal = normal;
    this->color = color;
    this->roughness = roughness;
    this->shine = shine;
}

optional<LitPoint> Plane::colide(Ray ray) const {
    double divisor = normal.dot(ray.direction);

    if(divisor == 0.0) return nullopt;

    Vector w = ray.p_inicial - center;

    double t = -(normal.dot(w)/divisor);
    Point p_intersect = ray.p_inicial + (ray.direction * t);

    return LitPoint(p_intersect, t, this->normal, this->color, this->roughness, this->shine);
};

Vector Plane::get_normal(Point p) const{
    return this->normal;
}