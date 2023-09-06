#pragma once

#include "object.h"
#include "vector.h"
#include "compound_object.h"
#include <vector>

using namespace std;

class SnowmanObject : public CompoundObject{
    public:
        SnowmanObject(Point center);
        optional<LitPoint> colide(Ray ray) const override;
    private:
        Vector get_normal(Point p) const override;
};  