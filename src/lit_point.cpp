#include "../headers/lit_point.h"

LitPoint::LitPoint(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->normal = Vector(0, 1, 0);
    this->color = Color(255, 0, 0);
    this->roughness = Vec(1, 1, 1);
    this->shine = Vec(1, 1, 1);
}

LitPoint::LitPoint(Vec v, double t, Vector normal, Color color){
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->t = t;
    this->normal = normal;
    this->color = color;
    this->roughness = Vec(1, 1, 1);
    this->shine = Vec(1, 1, 1);
}

LitPoint::LitPoint(Vec v, double t, Vector normal, Color color, Vec roughness, Vec shine){
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->t = t;
    this->normal = normal;
    this->color = color;
    this->roughness = roughness;
    this->shine = shine;
}

LitPoint::LitPoint(double x, double y, double z, double t, Vector normal, Color color){
    this->x = x;
    this->y = y;
    this->z = z;
    this->t = t;
    this->normal = normal;
    this->color = color;
    this->roughness = Vec(1, 1, 1);
    this->shine = Vec(1, 1, 1);
}
LitPoint::LitPoint(double x, double y, double z, double t, Vector normal, Color color, Vec roughness, Vec shine){
    this->x = x;
    this->y = y;
    this->z = z;
    this->t = t;
    this->normal = normal;
    this->color = color;
    this->roughness = roughness;
    this->shine = shine;
}