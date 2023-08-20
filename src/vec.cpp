#include <math.h>
#include "../headers/vec.h"

Vec::Vec(){
    x = 0;
    y = 0;
    z = 0;
}
        
Vec::Vec(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec Vec::operator+(Vec v){
    return Vec(v.x + x, v.y + y, v.z + z);
}
Vec Vec::operator-(Vec v){
    return Vec(v.x - x, v.y - y, v.z - z);
}
Vec Vec::operator*(double d){
    return Vec(x * d, y * d, z * d);
}
Vec Vec::operator/(double d){
    return Vec(x / d, y / d, z / d);
}
double Vec::scalar(Vec v){
    return v.x * x + v.y * y + v.z * z;
}
double Vec::modulo(){
    return sqrt(this->scalar(*this));
}