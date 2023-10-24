#include <math.h>
#include "../headers/cylindrical_face.h"

#include <iostream>
using namespace std;

CylindricalFace::CylindricalFace(){
    this->base_center = Point(0, 0, -100);
    this->radius = 10.0;
    this->direction = Vector(0, 1, 0);
    this->material = Material();
}

CylindricalFace::CylindricalFace(Point center, Vector direction, double radius, double height){
    this->base_center = center;
    this->radius = radius;
    this->height = height;
    this->direction = direction;
    this->material = Material();
}
CylindricalFace::CylindricalFace(Point center, Vector direction, double radius, double height, Material material){
    this->base_center = center;
    this->radius = radius;
    this->height = height;
    this->direction = direction;
    this->material = material;
}

Vector CylindricalFace::get_normal(Point p) const{
    Vector v = p - this->base_center;
    Vector projection = this->direction * (v.dot(this->direction));
    Vector h = v - projection;
    return h.normalize();
}

optional<LitPoint> CylindricalFace::colide(Ray ray) const{
    if((ray.direction.x == this->direction.x && 
       ray.direction.y == this->direction.y &&
       ray.direction.z == this->direction.z) ||
       (ray.direction.x == -this->direction.x && 
       ray.direction.y == -this->direction.y &&
       ray.direction.z == -this->direction.z))
    return nullopt;

    Vector w = ray.p_inicial - this->base_center;

    double a = ray.direction.dot(ray.direction) - pow(ray.direction.dot(this->direction), 2);
    double b = w.dot(ray.direction) * 2 - w.dot(this->direction) * ray.direction.dot(this->direction) * 2;
    double c = w.dot(w) - pow(w.dot(this->direction), 2) - pow(this->radius, 2);

    double delta = pow(b, 2) - 4 * a * c;

    if (delta < 0) return nullopt;

    double t_1 = (-b - sqrt(delta))/(2 * a);
    double t_2 = (-b + sqrt(delta))/(2 * a);
    double smallest_t;

    Point p_intersect_1 = Point(ray.p_inicial + (ray.direction * t_1));
    Vector v_1 = p_intersect_1 - this->base_center;
    Vector projection_1 = this->direction * v_1.dot(this->direction);
    double distance_along_axis_1 = projection_1.magnitude();

    Point p_intersect_2 = Point(ray.p_inicial + (ray.direction * t_2));
    Vector v_2 = p_intersect_2 - this->base_center;
    Vector projection_2 = this->direction * v_2.dot(this->direction);
    double distance_along_axis_2 = projection_2.magnitude();

    if(projection_1.dot(this->direction) > 0 && distance_along_axis_1 < this->height){
        if(projection_2.dot(this->direction) > 0 && distance_along_axis_2 < this->height && t_2 < t_1) smallest_t = t_2;
        else smallest_t = t_1;
    }
    else if(projection_2.dot(this->direction) > 0 && distance_along_axis_2 < this->height) smallest_t = t_2;
    else return nullopt;

    Point p_intersect = ray.p_inicial + (ray.direction * smallest_t);
    Vector normal = this->get_normal(p_intersect);

    return LitPoint(p_intersect, smallest_t, normal, this->material);
}

