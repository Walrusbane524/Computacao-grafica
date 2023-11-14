#include "../headers/point.h"

Point::Point() : Vec(0, 0, 0){}

Point::Point(Vec v) : Vec(v.x, v.y, v.z){}

Point::Point(double x, double y, double z) : Vec(x, y, z){}

Point Point::transform(Matrix matrix){
    return matrix * *this;
}
