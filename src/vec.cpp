#include <math.h>
#include <iostream>
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

Vec Vec::operator+(const Vec& v){
    return Vec(v.x + x, v.y + y, v.z + z);
}
Vec Vec::operator-(const Vec& v){
    return Vec(x - v.x, y - v.y, z - v.z);
}
Vec Vec::operator*(const double d){
    return Vec(x * d, y * d, z * d);
}
Vec Vec::operator/(const double d){
    return Vec(x / d, y / d, z / d);
}
double Vec::dot(const Vec& v){
    return v.x * x + v.y * y + v.z * z;
}

double Vec::dot(const Vec& v) const{
    return v.x * x + v.y * y + v.z * z;
}
Vec Vec::operator*(const double d) const{
    return Vec(x * d, y * d, z * d);
}

double Vec::magnitude(){
    return sqrt(x * x + y * y + z * z);
}

Vec Vec::normalize(){
    double len = magnitude();
    return Vec(x / len, y / len, z / len);
}