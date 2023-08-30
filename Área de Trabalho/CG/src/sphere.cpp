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

optional<double> Sphere::colide(Ray ray) const {
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
        double root_1 = (-b + sqrt(delta))/(2 * a);
        double root_2 = (-b - sqrt(delta))/(2 * a);
        double answer = root_1;

        // std::cout << "t1 = " << root_1 << std::endl;
        // std::cout << "t2 = " << root_2 << std::endl;

        if (root_2 < root_1) answer = root_2;
        return answer;
    }
    else return nullopt;
}