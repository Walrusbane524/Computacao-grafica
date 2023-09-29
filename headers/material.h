#pragma once

#include "vec.h"

class Material{
    public:

    Vec shine;
    Vec roughness;

    double reflectivity;

    Material();
    Material(Vec shine, Vec roughness, double reflectivity);
};