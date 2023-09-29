#include "../headers/material.h"

Material::Material(){
    this->shine = Vec(0.7, 0.7, 0.7);
    this->roughness = Vec(0.7, 0.7, 0.7);
    this->reflectivity = 1;
}
Material::Material(Vec shine, Vec roughness, double reflectivity){
    this->shine = shine;
    this->roughness = roughness;
    this->reflectivity = reflectivity;
}