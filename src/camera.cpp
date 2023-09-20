#include <math.h>
#include "../headers/camera.h"

Camera::Camera(){
    origin = Point(0, 0, 0);
    i = Vector(1, 0, 0);
    j = Vector(0, 1, 0);
    j = Vector(0, 0, -1);
    width = 2;
    height = 2;
    n_l = 400;
    n_c = 400;
    d = 3;
    delta_x = abs(width)/n_c;
    delta_y = abs(height)/n_l;
}

Camera::Camera(Point position, Vector i, Vector j, Vector k, double width, double height, double n_l, double n_c, double d){
    this->origin = position;
    this->i = i.normalize();
    this->j = j.normalize();
    this->k = k.normalize();
    this->width = width;
    this->height = height;
    this->n_l = n_l;
    this->n_c = n_c;
    this->d = d;
    delta_x = abs(width)/n_c;
    delta_y = abs(height)/n_l;
}