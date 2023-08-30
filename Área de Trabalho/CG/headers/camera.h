#ifndef CAMERA
#define CAMERA

#include "point.h"

class Camera{
    public:

    Point origin;
    double j_ymax;
    double j_ymin;
    double j_xmax;
    double j_xmin;
    double n_l;
    double n_c;
    double d;
    double delta_x;
    double delta_y;

    Camera();

    Camera(Point position, double j_ymax, double j_ymin, double j_xmax, double j_xmin, double n_l, double n_c, double d);
};

#endif