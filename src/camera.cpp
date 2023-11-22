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

Camera::Camera(double width, double height, double n_l, double n_c, double d){
    this->origin = Point(0, 0, 0);
    this->i = Vector(1, 0,  0);
    this->j = Vector(0, 1,  0);
    this->k = Vector(0, 0, -1);
    this->width = width;
    this->height = height;
    this->n_l = n_l;
    this->n_c = n_c;
    this->d = d;
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

void Camera::lookAt(Point eye, Point at, Point up){
    this->origin = eye;
    this->k = (at - eye).normalize();
    Vector v_up = up - eye;

    this->i = (v_up & this->k).normalize();
    this->j = this->k & this->i;
}

void Camera::lookAt(Point at, Point up){
    this->lookAt(this->origin, at, up);
}