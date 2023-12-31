#include "../headers/point.h"
#include "../headers/vector.h"

Vector::Vector() : Vec(0, 0, 0, 0){}

Vector::Vector(Vec v) : Vec(v.x, v.y, v.z, 0){}

Vector::Vector(Point p) : Vec(p.x, p.y, p.z, 0){}

Vector::Vector(double x, double y, double z) : Vec(x, y, z, 0){}
