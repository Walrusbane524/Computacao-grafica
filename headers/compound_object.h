#ifndef COMPOUND_OBJECT
#define COMPOUND_OBJECT

#include "object.h"
#include <vector>

using namespace std;

class CompoundObject : public Object{
    public:
    vector<Object*> sub_objects; 
    virtual optional<double> colide(Ray ray) const = 0;
};

#endif