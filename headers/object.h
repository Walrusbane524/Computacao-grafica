#ifndef OBJECT
#define OBJECT

#include "ray.h"
#include <optional>

using namespace std;

class Object{
    public: 
    optional<double> colide(Ray ray);
};

#endif