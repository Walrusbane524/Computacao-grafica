#pragma once

#include "object.h"
#include "vector.h"
#include <vector>

using namespace std;

class CompoundObject : public Object{
    public:
        vector<Object*> sub_objects; 
        virtual optional<LitPoint> colide(Ray ray) const = 0;
    private:
        virtual Vector get_normal(Point p) const = 0;
};  