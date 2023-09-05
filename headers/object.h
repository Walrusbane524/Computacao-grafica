#pragma once

#include "ray.h"
#include "color.h"
#include "lit_point.h"
#include <optional>

using namespace std;

class Object{
    public:
        Color color;

        Vec roughness;
        Vec shine;

        virtual optional<LitPoint> colide(Ray ray) const = 0;
    private:
        virtual Vector get_normal(Point p) const = 0;
};