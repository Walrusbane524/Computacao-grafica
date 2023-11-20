#pragma once

#include "object.h"
#include "vector.h"
#include "compound_object.h"
#include <vector>

class TreeObject : public CompoundObject{
    public:
        TreeObject(Point center);
        optional<LitPoint> colide(Ray ray) const override;
    private:
        Vector get_normal(Point p) const;
};  