#include "../headers/conical_face.h"
#include <iostream>

ConicalFace::ConicalFace(){
    this->base_center = Point(0, 0, -100);
    this->direction = Vector(0, 1, 0);
    this->height = 20;
    this->radius = 10;
    this->tip = this->base_center + (this->direction * this->height);
    this->material = Material();
}
ConicalFace::ConicalFace(Point base_center, Point tip, double radius){
    Vector h = tip - base_center;

    this->base_center = base_center;
    this->direction = h.normalize();
    this->height = h.magnitude();
    this->radius = radius;
    this->tip = tip;
    this->material = Material();
}
ConicalFace::ConicalFace(Point base_center, Point tip, double radius, Material material){
    Vector h = tip - base_center;

    this->base_center = base_center;
    this->direction = h.normalize();
    this->height = h.magnitude();
    this->radius = radius;
    this->tip = tip;
    this->material = material;
}
ConicalFace::ConicalFace(Point base_center, Vector direction, double radius, double height){
    this->base_center = base_center;
    this->direction = direction;
    this->height = height;
    this->radius = radius;
    this->tip = this->base_center + (this->direction * this->height);
    this->material = Material();
}
ConicalFace::ConicalFace(Point base_center, Vector direction, double radius, double height, Material material){
    this->base_center = base_center;
    this->direction = direction;
    this->height = height;
    this->radius = radius;
    this->tip = this->base_center + (this->direction * this->height);
    this->material = material;
}

Vector ConicalFace::get_normal(Point p) const{
    return ((p * this->tip) & this->direction).normalize();
}

optional<LitPoint> ConicalFace::colide(Ray ray) const{
    
    Vector v = this->tip - ray.p_inicial;
    Vector dr = ray.direction;

    double cos_ = height/sqrt(height * height + radius * radius);

    double a = pow(dr.dot(direction), 2) - dr.dot(dr) * pow(cos_, 2);
    double b = 2 * (v.dot(dr) * pow(cos_, 2) - 2 * (v.dot(direction)) * (dr.dot(direction)));
    double c = pow(v.dot(direction), 2) - (v.dot(v)) * pow(cos_, 2);

    double delta = pow(b, 2) - 4 * a * c;

    if(delta <= 0) return nullopt;

    double t_1 = (-b - sqrt(delta))/(2*a);
    double t_2 = (-b + sqrt(delta))/(2*a);
    double smallest_t;

    Point p_intersect_1 = Point(ray.p_inicial + (ray.direction * t_1));
    Vector v_1 = p_intersect_1 - this->base_center;
    Vector projection_1 = this->direction * v_1.dot(this->direction);
    double distance_along_axis_1 = projection_1.magnitude();

    Point p_intersect_2 = Point(ray.p_inicial + (ray.direction * t_2));
    Vector v_2 = p_intersect_2 - this->base_center;
    Vector projection_2 = this->direction * v_2.dot(this->direction);
    double distance_along_axis_2 = projection_2.magnitude();

    if(distance_along_axis_1 > 0 && distance_along_axis_1 < this->height){
        if(distance_along_axis_2 > 0 && distance_along_axis_2 < this->height && t_2 < t_1) smallest_t = t_2;
        else smallest_t = t_1;
    }
    else if(distance_along_axis_2 > 0 && distance_along_axis_2 < this->height) smallest_t = t_2;
    else return nullopt;

    Point p_intersect = ray.p_inicial + (ray.direction * smallest_t);
    Vector normal = this->get_normal(p_intersect);

    return LitPoint(p_intersect, smallest_t, normal, this->material);
}

