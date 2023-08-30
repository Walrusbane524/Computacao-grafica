#include "../headers/cylinder.h"
#include "../headers/cylindrical_face.h"
#include "../headers/plane.h"

Cylinder::Cylinder(Point base_center, Point top_center, double radius, Color color){
    
    double height = (top_center - base_center).magnitude();
    Vector direction = (top_center - base_center).normalize();

    this->radius = radius;
    this->base_center = base_center;
    this->top_center = top_center;

    Plane* base_plane = new Plane(base_center, direction, color);
    Plane* top_plane = new Plane(top_center, direction, color);
    CylindricalFace* cylinder_body = new CylindricalFace(base_center, direction, radius, height, color);

    this->sub_objects.push_back(base_plane);
    this->sub_objects.push_back(top_plane);
    this->sub_objects.push_back(cylinder_body);
    this->color = color;
}

Cylinder::Cylinder(Point base_center, Vector direction, double radius, double height, Color color){
    
    Point top_center = Point(base_center + (direction * height));

    this->radius = radius;
    this->base_center = base_center;
    this->top_center = top_center;

    Plane* base_plane = new Plane(base_center, direction, color);
    Plane* top_plane = new Plane(top_center, direction, color);
    CylindricalFace* cylinder_body = new CylindricalFace(base_center, direction, radius, height, color);

    this->sub_objects.push_back(base_plane);
    this->sub_objects.push_back(top_plane);
    this->sub_objects.push_back(cylinder_body);
    this->color = color;
}

optional<double> Cylinder::colide(Ray ray) const{

    double smallest_root = numeric_limits<double>::infinity();

    int cont = 0;
    for(Object* o : this->sub_objects){
        optional<double> intersect = o->colide(ray);
                
        if (intersect.has_value() && intersect.value() > 0){
            double t = intersect.value();
            
            if(cont == 0){
                Point intersect = Point(ray.p_inicial + ray.direction * t);
                if((intersect - base_center).magnitude() <= radius && t < smallest_root) smallest_root = t; 
            }
            else if (cont == 1){
                Point intersect = Point(ray.p_inicial + ray.direction * t);
                if((intersect - top_center).magnitude() <= radius && t < smallest_root) smallest_root = t;
            }
            else if(t < smallest_root) smallest_root = t;
        }
        cont++;
    }

    if (smallest_root != numeric_limits<double>::infinity()) return smallest_root;
    return nullopt;
}
