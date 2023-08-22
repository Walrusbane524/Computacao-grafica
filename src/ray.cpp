#include "../headers/point.h"
#include "../headers/vector.h"
#include "../headers/ray.h"

Ray::Ray(){
    p_inicial = Point();
    direction = Vector(0, 0, -1);
}
Ray::Ray(Point p_inicial, Vector direction){
    this->p_inicial = p_inicial;
    this->direction = direction;
}
Ray::Ray(Point p_inicial, Point p_ray){
    this->p_inicial = p_inicial;
    this->direction = (p_inicial - p_ray).normalize();
}
