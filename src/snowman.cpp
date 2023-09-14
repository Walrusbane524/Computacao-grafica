#include "../headers/sphere.h"
#include "../headers/scene.h"
#include "../headers/cylinder.h"
#include "../headers/cone.h"
#include "../headers/snowman.h"
#include <iostream>

SnowmanObject::SnowmanObject(Point point){

    Sphere* cabeca = new Sphere((point + Point(0, 65, 0)), 10, Color(255, 255, 255));
    Sphere* tronco = new Sphere((point + Point(0, 45, 0)), 15, Color(255, 255, 255));
    Sphere* barriga = new Sphere((point + Point(0, 20, 0)), 20, Color(255, 255, 255));

    this->sub_objects.push_back(cabeca);
    this->sub_objects.push_back(tronco);
    this->sub_objects.push_back(barriga);

    Cylinder* braco_direito = new Cylinder(point + Point(14, 48, 0), Vector(0.7, -0.3, 0).normalize(), 1, 15, Color(205, 133, 63));
    Cylinder* braco_esquerdo = new Cylinder(point + Point(-14, 48, 0), Vector(-0.7, -0.3, 0).normalize(), 1, 15, Color(205, 133, 63));

    this->sub_objects.push_back(braco_direito);
    this->sub_objects.push_back(braco_esquerdo);

    Cylinder* chapeu = new Cylinder(point + Point(0, 72, 0), Vector(0,1,0).normalize(), 12, 0.5, Color(0, 0, 0));
    Cylinder* chapeu2 = new Cylinder(point + Point(0, 74, 0), Vector(0, 1, 0).normalize(), 9.1, 2, Color(255, 255, 255));
    Cylinder* chapeu3= new Cylinder(point + Point(0, 76.5, 0), Vector(0, 1, 0).normalize(), 9, 4, Color(0, 0, 0));

    this->sub_objects.push_back(chapeu);
    this->sub_objects.push_back(chapeu2);
    this->sub_objects.push_back(chapeu3);

    Sphere* olho1 = new Sphere((point + Point(2.5, 65, 9.5)), 1, Color(0, 0, 0));
    Sphere* olho2 = new Sphere((point + Point(-2.5, 65, 9.5)), 1, Color(0, 0, 0));

    this->sub_objects.push_back(olho1);
    this->sub_objects.push_back(olho2);

    Sphere* boca1 = new Sphere((point + Point(-1.94602,  60.6649, 8.7988)), 0.5, Color(0, 0, 0));
    Sphere* boca2 = new Sphere((point + Point(-1.57560,  60.4828, 8.7813)), 0.5, Color(0, 0, 0));
    Sphere* boca3 = new Sphere((point + Point(-1.20525,  60.3038, 8.7461)), 0.5, Color(0, 0, 0));
    Sphere* boca4 = new Sphere((point + Point(-0.648669, 60.2941, 8.7996)), 0.5, Color(0, 0, 0));
    Sphere* boca5 = new Sphere((point + Point(-0.0926492, 60.2902,8.8209)), 0.5, Color(0, 0, 0));
    Sphere* boca6 = new Sphere((point + Point(0.0926492,   60.2902, 8.8209)), 0.5, Color(0, 0, 0));
    Sphere* boca7 = new Sphere((point + Point(0.648669,60.2941, 8.7996)), 0.5, Color(0, 0, 0));
    Sphere* boca8 = new Sphere((point + Point(1.20525, 60.3038, 8.7461)), 0.5, Color(0, 0, 0));
    Sphere* boca9 = new Sphere((point + Point(1.5756,  60.4828, 8.7813)), 0.5, Color(0, 0, 0));
    Sphere* boca10 = new Sphere((point+ Point(1.94602,  60.6649, 8.7988)), 0.5, Color(0, 0, 0));

    this->sub_objects.push_back(boca1);
    this->sub_objects.push_back(boca2);
    this->sub_objects.push_back(boca3);
    this->sub_objects.push_back(boca4);
    this->sub_objects.push_back(boca5);
    this->sub_objects.push_back(boca6);
    this->sub_objects.push_back(boca7);
    this->sub_objects.push_back(boca8);
    this->sub_objects.push_back(boca9);
    this->sub_objects.push_back(boca10);


    Sphere* botao1 = new Sphere((point + Point(0.106044, 50.4984, 14)), 1, Color(0, 0, 0));
    Sphere* botao2 = new Sphere((point + Point(0.10401, 45.0965, 15)), 1, Color(0, 0, 0));
    Sphere* botao3 = new Sphere((point + Point(0.0990099, 40.0990099, 14)), 1, Color(0, 0, 0));

    this->sub_objects.push_back(botao1);
    this->sub_objects.push_back(botao2);
    this->sub_objects.push_back(botao3);

    Cone* nariz = new Cone((point + Point(0, 63.5, 5)), (point + Point(0, 63.5, 20)), 1.5, Color(255, 177, 24));

    this->sub_objects.push_back(nariz);

    //Point(0, -40, -100)
}

optional<LitPoint> SnowmanObject::colide(Ray ray) const{
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

Vector SnowmanObject::get_normal(Point p) const{
    return Vector();
}