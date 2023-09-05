#include "../headers/light.h"

Light::Light(){
    this->point = Point(0, 100, -80);
    this->i_r = 1.0;
    this->i_g = 1.0;
    this->i_b = 1.0;
}

Light::Light(Point point, double i_r, double i_g, double i_b){
    this->point = point;
    this->i_r = i_r;
    this->i_g = i_g;
    this->i_b = i_b;
}

Vec Light::operator*(const Vec v){
    return Vec(this->i_r * v.x, this->i_r * v.y, this->i_r * v.z);
}
Vec Light::operator*(const Vec v) const{
    return Vec(this->i_r * v.x, this->i_r * v.y, this->i_r * v.z);
}