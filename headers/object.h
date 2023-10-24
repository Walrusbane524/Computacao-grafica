#pragma once

#include "ray.h"
#include "color.h"
#include "lit_point.h"
#include "material.h"
#include <optional>

using namespace std;

class Object{
    public:

        Material material;

        virtual optional<LitPoint> colide(Ray ray) const = 0;
    private:
        virtual Vector get_normal(Point p) const = 0;
};