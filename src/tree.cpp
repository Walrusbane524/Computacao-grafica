#include "../headers/sphere.h"
#include "../headers/scene.h"
#include "../headers/cylinder.h"
#include "../headers/cone.h"
#include "../headers/tree.h"
#include <iostream>

TreeObject::TreeObject(Point point){

    Cylinder* tronco = new Cylinder(point, Vector(0, 1, 0).normalize(), 4.5, 50, Color(153, 51, 0));
    this->sub_objects.push_back(tronco);

    Cone* folha = new Cone((point + Point(0, 45, 0)), (point + Point(0, 70, 0)), 7, Color(51, 204, 51));
    this->sub_objects.push_back(folha);

    /*
    Sphere* bola1 = new Sphere((point + Point(-10, 25, 0)), 3, Color(255, 0, 0));
    this->sub_objects.push_back(bola1);*/

}

optional<LitPoint> TreeObject::colide(Ray ray) const{
    double smallest_t = numeric_limits<double>::infinity();
    LitPoint nearest_point;

    for(Object* o : this->sub_objects){
        optional<LitPoint> intersect_point = o->colide(ray);
        if (intersect_point.has_value() && intersect_point.value().t < smallest_t){
            smallest_t = intersect_point.value().t;
            nearest_point = intersect_point.value();
        }
    }

    if (smallest_t < numeric_limits<double>::infinity()) return nearest_point;
    return nullopt;
}

Vector TreeObject::get_normal(Point p) const{
    return Vector();
}