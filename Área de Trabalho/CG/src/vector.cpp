#include "../headers/point.h"
#include "../headers/vector.h"

Vector::Vector() : Vec(0, 0, 0){}

Vector::Vector(Vec v) : Vec(v.x, v.y, v.z){}

Vector::Vector(Point p) : Vec(p.x, p.y, p.z){}

Vector::Vector(double x, double y, double z) : Vec(x, y, z){}
