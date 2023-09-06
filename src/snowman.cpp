#include <math.h>
#include <optional>
#include <SDL2/SDL.h>
#include <iostream>
#include <limits>
#include "../headers/camera.h"
#include "../headers/canvas.h"
#include "../headers/color.h"
#include "../headers/object.h"
#include "../headers/point.h"
#include "../headers/ray.h"
#include "../headers/vec.h"
#include "../headers/sphere.h"
#include "../headers/scene.h"
#include "../headers/cylinder.h"
#include "../headers/plane.h"
#include "../headers/light.h"
#include "../headers/cone.h"
#include "../headers/compound_object.h"
#include "../headers/snowman.h"

using namespace std;

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

    //Point(0, -40, - 100)

    /*Cylinder braco_direito = Cylinder(Point(14, 8, -100), Vector(0.7, -0.3, 0).normalize(), 1, 15, Color(205, 133, 63));
    Cylinder braco_esquerdo = Cylinder(Point(-14, 8, -100), Vector(-0.7, -0.3, 0).normalize(), 1, 15, Color(205, 133, 63));
    Plane plano = Plane(Point(0, -40, -100), Vector(0, 1, 0).normalize(), Color(70, 130, 180));

    Cone nariz = Cone(Point(0, 23.5, -95), Point(0, 23.5, -80), 1.5, Color(255, 177, 24));

    Cylinder chapeu = Cylinder(Point(0, 32, -100), Vector(0,1,0).normalize(), 12, 0.5, Color(0, 0, 0));
    Cylinder chapeu2 = Cylinder(Point(0, 36.5, -100), Vector(0, 1, 0).normalize(), 9, 4, Color(0, 0, 0));
    Cylinder chapeu3 = Cylinder(Point(0, 34, -100), Vector(0, 1, 0).normalize(), 9.1, 2, Color(255, 255, 255));

    Sphere olho1 = Sphere(Point(2.5,  25, -90), 1, Color(0, 0, 0));
    Sphere olho2 = Sphere(Point(-2.5,  25, -90), 1, Color(0, 0, 0));

    Sphere boca1 = Sphere(Point(-1.94602,  20.6649, -91.2012), 0.5, Color(0, 0, 0));
    Sphere boca2 = Sphere(Point(-1.5756,  20.4828, -91.2187), 0.5, Color(0, 0, 0));
    Sphere boca3 = Sphere(Point(-1.20525,   20.3038, -91.2539), 0.5, Color(0, 0, 0));
    Sphere boca4 = Sphere(Point(-0.648669,  20.2941, -91.2004), 0.5, Color(0, 0, 0));
    Sphere boca5 = Sphere(Point(-0.0926492,   20.2902, -91.1791), 0.5, Color(0, 0, 0));
    Sphere boca6 = Sphere(Point(0.0926492,   20.2902, -91.1791), 0.5, Color(0, 0, 0));
    Sphere boca7 = Sphere(Point(0.648669,  20.2941, -91.2004), 0.5, Color(0, 0, 0));
    Sphere boca8 = Sphere(Point(1.20525,   20.3038, -91.2539), 0.5, Color(0, 0, 0));
    Sphere boca9 = Sphere(Point(1.5756,  20.4828, -91.2187), 0.5, Color(0, 0, 0));
    Sphere boca10 = Sphere(Point(1.94602,  20.6649, -91.2012), 0.5, Color(0, 0, 0));


    Sphere botao1 = Sphere(Point(0.106044, 10.4984, -86.0445), 1, Color(0, 0, 0));
    Sphere botao2 = Sphere(Point(0.10401, 5.0965, -84.0101), 1, Color(0, 0, 0));
    Sphere botao3 = Sphere(Point(0.0990099, -0.0990099, -79.0099), 1, Color(0, 0, 0));

    //scene.addObject(&cabeca);
    //scene.addObject(&olho1);
    //scene.addObject(&olho2);
    //scene.addObject(&olho2);
    //scene.addObject(&nariz);

    //scene.addObject(&boca1);
    //scene.addObject(&boca2);
    //scene.addObject(&boca3);
    //scene.addObject(&boca4);
    //scene.addObject(&boca5);
    //scene.addObject(&boca6);
    //scene.addObject(&boca7);
    //scene.addObject(&boca8);
    //scene.addObject(&boca9);
    //scene.addObject(&boca10);

    //scene.addObject(&tronco);
    //scene.addObject(&barriga);
    //scene.addObject(&botao1);
    //scene.addObject(&botao2);
    //scene.addObject(&botao3);
    //scene.addObject(&braco_direito);
    //scene.addObject(&braco_esquerdo);
    //scene.addObject(&plano);
    //scene.addObject(&chapeu);
    //scene.addObject(&chapeu2);
    //scene.addObject(&chapeu3);*/
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