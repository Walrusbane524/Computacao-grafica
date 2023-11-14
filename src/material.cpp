#include "../headers/material.h"

Material::Material(){
    this->shine = Vec(0.8, 0.8, 0.8);
    this->roughness = Vec(0.8, 0.8, 0.8);
    this->ambient = Vec(0.8, 0.8, 0.8);
    this->reflectivity = 1;
}
Material::Material(Vec shine, Vec roughness, Vec ambient, double reflectivity){
    this->shine = shine;
    this->roughness = roughness;
    this->ambient = ambient;
    this->reflectivity = reflectivity;
}