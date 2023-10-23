#include "../headers/directional_light.h"

DirectionalLight::DirectionalLight() : Light(){
    this->direction = Vector(0, -1, -1).normalize();
}

DirectionalLight::DirectionalLight(Vector direction, double i_r, double i_g, double i_b) : Light(i_r, i_g, i_b){
    this->direction = direction;
}

Vec DirectionalLight::get_diffuse_and_specular(LitPoint intersect, vector<Object*> objects, Ray camera_ray) const{

    Ray ray = Ray((Point)intersect, Vector(-this->direction.x, -this->direction.y, -this->direction.z));
    double light_intersect = false;

    for(Object* o : objects){

        optional<LitPoint> intersect = o->colide(ray);
        
        if (intersect.has_value() && intersect.value().t > 0.000001){
            light_intersect = true;
            break;
        }
    }
    if(!light_intersect){

        Vector l_ = Vector((Vector(0, 0, 0) - this->direction).normalize());
        Vector v = Vector(-camera_ray.direction.x, -camera_ray.direction.y, -camera_ray.direction.z);
        Vector r = (intersect.normal * l_.dot(intersect.normal) * 2) - l_;

        double f_dif = l_.dot(intersect.normal);
        double f_spec = pow(v.dot(r), intersect.material.reflectivity);

        if (f_dif < 0) f_dif = 0;
        if (f_spec < 0) f_spec = 0;

        Vec diffuse_intensity = *this * (intersect.material.roughness * f_dif);
        Vec specular_intensity = *this * (intersect.material.shine * f_spec);

        Vec diffuse_specular = diffuse_intensity + specular_intensity;
        return diffuse_specular;
    }
    return Vec(0, 0, 0);
}