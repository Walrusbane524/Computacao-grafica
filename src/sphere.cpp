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
}

optional<double> Sphere::colide(Ray ray){
    Vector w = ray.p_inicial - center;
    double a = ray.direction.scalar(ray.direction);
    double _b = w.scalar(ray.direction);
    double b = 2 * _b;
    double c = w.scalar(w) - pow(radius, 2);
    double delta = pow(b, 2) - 4 * a * c;

    if (delta >= 0){
        double root_1 = -_b + sqrt(delta);
        double answer = root_1;
        if (delta > 0){
            double root_2 = -_b - sqrt(delta);
            if (root_2 < root_1) answer = root_2;
        }
        return answer;
    }
    else return nullopt;
}