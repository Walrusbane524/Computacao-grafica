#include "../headers/spot_light.h"
#include <math.h>

#define PI 3.14159265

SpotLight::SpotLight() : PointLight() {
    this->direction = Vector(0, -1, -1).normalize();
    this->angle_degrees = 60;
}

SpotLight::SpotLight(Point point, Vector direction, double angle_degrees, double i_r, double i_g, double i_b) : PointLight(point, i_r, i_g, i_b) {
    this->direction = direction;
    this->angle_degrees = angle_degrees;
}

Vec SpotLight::get_diffuse_and_specular(LitPoint intersect, vector<Object*> objects, Ray camera_ray) const{

    double radians = this->angle_degrees * (PI/180);
    double cosine = cos(radians);
    Vector l = ((Point)intersect - this->point).normalize();

    if ((l.dot(this->direction)) >= cosine)
        return PointLight::get_diffuse_and_specular(intersect, objects, camera_ray);
    
    return Vec(0, 0, 0);
}