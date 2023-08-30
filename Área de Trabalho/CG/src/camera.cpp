#include <math.h>
#include "../headers/camera.h"

Camera::Camera(){
    origin = Point(0, 0, 0);
    j_ymax = 1;
    j_ymin = -1;
    j_xmax = 1;
    j_xmin = -1;
    n_l = 400;
    n_c = 400;
    d = 3;
    delta_x = abs(j_xmax - j_xmin)/n_c;
    delta_y = abs(j_ymax - j_ymin)/n_l;
}

Camera::Camera(Point position, double j_ymax, double j_ymin, double j_xmax, double j_xmin, double n_l, double n_c, double d){
    origin = position;
    this->j_xmax = j_xmax;
    this->j_xmin = j_xmin;
    this->j_ymax = j_ymax;
    this->j_ymin = j_ymin;
    this->n_l = n_l;
    this->n_c = n_c;
    this->d = d;
    delta_x = abs(j_xmax - j_xmin)/n_c;
    delta_y = abs(j_ymax - j_ymin)/n_l;
}