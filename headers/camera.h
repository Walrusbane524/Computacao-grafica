#ifndef CAMERA
#define CAMERA

#include "point.h"
#include "vector.h"

class Camera{
    public:

    Point origin;
    Vector i;
    Vector j;
    Vector k;
    double height;
    double width;
    double n_l;
    double n_c;
    double d;
    double delta_x;
    double delta_y;

    Camera();

    Camera(Point position, Vector i, Vector j, Vector k, double width, double height, double n_l, double n_c, double d);
};

#endif