#ifndef OBJECT
#define OBJECT

#include "ray.h"
#include "color.h"
#include <optional>

using namespace std;

class Object{
    public:
    Color color; 
    virtual optional<double> colide(Ray ray) const = 0;
};

#endif