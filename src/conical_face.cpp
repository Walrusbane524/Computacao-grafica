#include "../headers/conical_face.h"
#include <iostream>

ConicalFace::ConicalFace(){
    this->base_center = Point(0, 0, -100);
    this->direction = Vector(0, 1, 0);
    this->height = 20;
    this->radius = 10;
    this->color = Color(255, 0, 0);
    this->tip = this->base_center + (this->direction * this->height);
}
ConicalFace::ConicalFace(Point base_center, Point tip, double radius, Color color){
    Vector h = tip - base_center;

    this->base_center = base_center;
    this->direction = h.normalize();
    this->height = h.magnitude();
    this->radius = radius;
    this->color = color;
    this->tip = tip;
}
ConicalFace::ConicalFace(Point base_center, Vector direction, double radius, double height, Color color){
    this->base_center = base_center;
    this->direction = direction;
    this->height = height;
    this->radius = radius;
    this->color = color;
    this->tip = this->base_center + (this->direction * this->height);
}

optional<double> ConicalFace::colide(Ray ray) const{
    
    double angle = atan(radius/height);
    Vector v = this->base_center - this->tip;

    double a = pow(ray.direction.dot(this->direction), 2) - (ray.direction.dot(ray.direction)) * pow(cos(angle), 2);
    double b = v.dot(ray.direction) * pow(cos(angle), 2) - (v.dot(this->direction)) * (ray.direction.dot(this->direction));
    double c = pow(v.dot(this->direction), 2) - (v.dot(v)) * pow(cos(angle), 2);

    double delta = pow(b, 2) - 4 * a * c;

    if(delta <= 0) return nullopt;

    double t_1 = (-b - sqrt(delta))/(2*a);
    double t_2 = (-b + sqrt(delta))/(2*a);

    cout << "t_1 = " << t_1 << endl;
    cout << "t_2 = " << t_2 << endl;

    Point p_intersect_1 = Point(ray.p_inicial + (ray.direction * t_1));
    Vector v_1 = p_intersect_1 - this->base_center;
    Vector projection_1 = this->direction * v_1.dot(this->direction);
    double distance_along_axis_1 = projection_1.magnitude();

    Point p_intersect_2 = Point(ray.p_inicial + (ray.direction * t_2));
    Vector v_2 = p_intersect_2 - this->base_center;
    Vector projection_2 = this->direction * v_2.dot(this->direction);
    double distance_along_axis_2 = projection_2.magnitude();

    if(distance_along_axis_1 > 0 && distance_along_axis_1 < this->height){
        if(distance_along_axis_2 > 0 && distance_along_axis_2 < this->height && t_2 < t_1) return t_2;
        else return t_1;
    }
    else if(distance_along_axis_2 > 0 && distance_along_axis_2 < this->height) return t_2;
    
    return nullopt;
}

