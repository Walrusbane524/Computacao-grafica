#include "../headers/lit_point.h"

LitPoint::LitPoint(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->normal = Vector(0, 1, 0);
    this->color = Color(255, 255, 255);
    this->material = Material();
}

LitPoint::LitPoint(Vec v, double t, Vector normal){
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->t = t;
    this->normal = normal;
    this->material = Material();
    this->color = Color(255, 255, 255);
}

LitPoint::LitPoint(Vec v, double t, Vector normal, Material material){
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->t = t;
    this->normal = normal;
    this->material = material;
    this->color = Color(255, 255, 255);
}

LitPoint::LitPoint(Vec v, double t, Vector normal, Material material, Color color){
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->t = t;
    this->normal = normal;
    this->material = material;
    this->color = color;
}

LitPoint::LitPoint(double x, double y, double z, double t, Vector normal){
    this->x = x;
    this->y = y;
    this->z = z;
    this->t = t;
    this->normal = normal;
    this->material = Material();
    this->color = Color(255, 255, 255);
}
LitPoint::LitPoint(double x, double y, double z, double t, Vector normal, Material material){
    this->x = x;
    this->y = y;
    this->z = z;
    this->t = t;
    this->normal = normal;
    this->material = material;
    this->color = Color(255, 255, 255);
}
LitPoint::LitPoint(double x, double y, double z, double t, Vector normal, Material material, Color color){
    this->x = x;
    this->y = y;
    this->z = z;
    this->t = t;
    this->normal = normal;
    this->material = material;
    this->color = color;
}