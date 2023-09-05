#include <optional>
#include "../headers/point.h"
#include "../headers/color.h"
#include "../headers/vector.h"
#include "../headers/ray.h"
#include "../headers/object.h"
#include "../headers/sphere.h"

Sphere::Sphere(){
    center = Point();
    radius = 1;
    color = Color(255, 0, 0);
}

Sphere::Sphere(Point center, double radius, Color color){
    this->center = center;
    this->radius = radius;
    this->color = color;
    this->roughness = Vec(1, 1, 1);
    this->shine = Vec(1, 1, 1);
}

Sphere::Sphere(Point center, double radius, Color color, Vec roughness, Vec shine){
    this->center = center;
    this->radius = radius;
    this->color = color;
    this->roughness = roughness;
    this->shine = shine;
}

Vector Sphere::get_normal(Point p) const{
    return (p - this->center)/this->radius;
}

optional<LitPoint> Sphere::colide(Ray ray) const {
    Vector w = ray.p_inicial - center;
    double a = ray.direction.dot(ray.direction);
    double b = 2 * w.dot(ray.direction);
    double c = w.dot(w) - pow(radius, 2);
    double delta = pow(b, 2) - (4 * a * c);
 
    // std::cout << "c.x = " << center.x << std::endl;
    // std::cout << "c.y = " << center.y << std::endl;
    // std::cout << "c.z = " << center.z << std::endl;
    // std::cout << "w.x = " << w.x << std::endl;
    // std::cout << "w.y = " << w.y << std::endl;
    // std::cout << "w.z = " << w.z << std::endl;
    // std::cout << "a = " << a << std::endl;
    // std::cout << "b = " << b << std::endl;
    // std::cout << "c = " << c << std::endl;

    if (delta > 0){
        double t_1 = (-b + sqrt(delta))/(2 * a);
        double t_2 = (-b - sqrt(delta))/(2 * a);
        double smallest_t = t_1;

        // std::cout << "t1 = " << root_1 << std::endl;
        // std::cout << "t2 = " << root_2 << std::endl;

        if (t_2 < t_1) smallest_t = t_2;

        Point p_intersect = ray.p_inicial + (ray.direction * smallest_t);
        Vector normal = get_normal(p_intersect);

        return LitPoint(p_intersect, smallest_t, normal, this->color, this->roughness, this->shine);
    }
    else return nullopt;
}