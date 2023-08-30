#include <math.h>
#include "../headers/cylindrical_face.h"

#include <iostream>
using namespace std;

CylindricalFace::CylindricalFace(){
    this->base_center = Point(0, 0, -100);
    this->radius = 10.0;
    this->direction = Vector(0, 1, 0);
    this->color = Color();
}

CylindricalFace::CylindricalFace(Point center, Vector direction, double radius, double height, Color color){
    this->base_center = center;
    this->radius = radius;
    this->height = height;
    this->direction = direction;
    this->color = color;
}

optional<double> CylindricalFace::colide(Ray ray) const{
    if(ray.direction.x == this->direction.x && 
       ray.direction.y == this->direction.y &&
       ray.direction.z == this->direction.z) 
    return nullopt;

    Vector w = ray.p_inicial - this->base_center;

    double a = ray.direction.dot(ray.direction) - pow(ray.direction.dot(this->direction), 2);
    double b = w.dot(ray.direction) * 2 - w.dot(this->direction) * ray.direction.dot(this->direction) * 2;
    double c = w.dot(w) - pow(w.dot(this->direction), 2) - pow(this->radius, 2);

    double delta = pow(b, 2) - 4 * a * c;

    if (delta <= 0) return nullopt;

    double t_1 = (-b - sqrt(delta))/(2 * a);
    double t_2 = (-b + sqrt(delta))/(2 * a);

    double closest_t = t_2;

    if(t_1 < t_2) closest_t = t_1;

    Point p_intersect = Point(ray.p_inicial + (ray.direction * closest_t));

    Vector v = p_intersect - this->base_center;
    Vector projection = this->direction * v.dot(this->direction);

    double distance_along_axis = projection.magnitude();

    if(distance_along_axis > 0 && distance_along_axis < this->height) return closest_t;
    return nullopt;
}

