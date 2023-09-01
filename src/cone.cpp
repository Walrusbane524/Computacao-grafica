#include "../headers/cone.h"
#include "../headers/conical_face.h"
#include "../headers/plane.h"

Cone::Cone(){
    this->base_center = Point(0, 0, -100);
    this->radius = 10;
    this->color = Color(255, 0, 0);
    Vector direction = Vector(0, 1, 0);

    Plane* base_plane = new Plane(base_center, direction, color);
    ConicalFace* cone_face = new ConicalFace(base_center, direction, radius, 20, color);

    sub_objects.push_back(base_plane);
    sub_objects.push_back(cone_face);
}

Cone::Cone(Point base_center, Point tip, double radius, Color color){
    this->base_center = base_center;
    this->radius = radius;
    this->color = color;
    Vector direction = (tip - base_center).normalize();

    Plane* base_plane = new Plane(base_center, direction, color);
    ConicalFace* cone_face = new ConicalFace(base_center, tip, radius, color);

    sub_objects.push_back(base_plane);
    sub_objects.push_back(cone_face);
}

Cone::Cone(Point base_center, Vector direction, double radius, double height, Color color){
    this->base_center = base_center;
    this->radius = radius;

    Plane* base_plane = new Plane(base_center, direction, color);
    ConicalFace* cone_face = new ConicalFace(base_center, direction, radius, height, color);

    sub_objects.push_back(base_plane);
    sub_objects.push_back(cone_face);
}


optional<double> Cone::colide(Ray ray) const{
    double smallest_root = numeric_limits<double>::infinity();

    optional<double> intersect_base = sub_objects[0]->colide(ray);
    optional<double> intersect_cone = sub_objects[1]->colide(ray);
                
    if (intersect_base.has_value() && intersect_base.value() > 0){
        double t_base = intersect_base.value();
        
        Point p_intersect_base = Point(ray.p_inicial + ray.direction * t_base);
        if((p_intersect_base - base_center).magnitude() <= radius && t_base < smallest_root) smallest_root = t_base; 
    }
    if (intersect_cone.has_value() && intersect_cone.value() > 0){
        double t_cone = intersect_cone.value();
        if(t_cone < smallest_root) smallest_root = t_cone;
    }


    if (smallest_root != numeric_limits<double>::infinity()) return smallest_root;
    return nullopt;
}
