#include "../headers/cylinder.h"
#include "../headers/cylindrical_face.h"
#include "../headers/plane.h"

Cylinder::Cylinder(Point base_center, Point top_center, double radius, Color color){
    
    double height = (top_center - base_center).magnitude();
    Vector direction = (top_center - base_center).normalize();
    Vector inverse_direction = Vector(-direction.x, -direction.y, -direction.z);

    this->radius = radius;
    this->base_center = base_center;
    this->top_center = top_center;
    this->roughness = Vec(1, 1, 1);
    this->shine = Vec(1, 1, 1);

    Plane* base_plane = new Plane(base_center, inverse_direction, color, this->roughness, this->shine);
    Plane* top_plane = new Plane(top_center, direction, color, this->roughness, this->shine);
    CylindricalFace* cylinder_body = new CylindricalFace(base_center, direction, radius, height, color, this->roughness, this->shine);

    this->sub_objects.push_back(base_plane);
    this->sub_objects.push_back(top_plane);
    this->sub_objects.push_back(cylinder_body);
    this->color = color;
}

Cylinder::Cylinder(Point base_center, Point top_center, double radius, Color color, Vec roughness, Vec shine){
    
    double height = (top_center - base_center).magnitude();
    Vector direction = (top_center - base_center).normalize();
    Vector inverse_direction = Vector(-direction.x, -direction.y, -direction.z);

    this->radius = radius;
    this->base_center = base_center;
    this->top_center = top_center;
    this->roughness = roughness;
    this->shine = shine;

    Plane* base_plane = new Plane(base_center, inverse_direction, color, this->roughness, this->shine);
    Plane* top_plane = new Plane(top_center, direction, color, this->roughness, this->shine);
    CylindricalFace* cylinder_body = new CylindricalFace(base_center, direction, radius, height, color, this->roughness, this->shine);

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
    this->roughness = Vec(1, 1, 1);
    this->shine = Vec(1, 1, 1);

    Plane* base_plane = new Plane(base_center, direction, color, this->roughness, this->shine);
    Plane* top_plane = new Plane(top_center, direction, color, this->roughness, this->shine);
    CylindricalFace* cylinder_body = new CylindricalFace(base_center, direction, radius, height, color, this->roughness, this->shine);

    this->sub_objects.push_back(base_plane);
    this->sub_objects.push_back(top_plane);
    this->sub_objects.push_back(cylinder_body);
    this->color = color;
}

Cylinder::Cylinder(Point base_center, Vector direction, double radius, double height, Color color, Vec roughness, Vec shine){
    
    Point top_center = Point(base_center + (direction * height));

    this->radius = radius;
    this->base_center = base_center;
    this->top_center = top_center;
    this->roughness = roughness;
    this->shine = shine;

    Plane* base_plane = new Plane(base_center, direction, color, this->roughness, this->shine);
    Plane* top_plane = new Plane(top_center, direction, color, this->roughness, this->shine);
    CylindricalFace* cylinder_body = new CylindricalFace(base_center, direction, radius, height, color, this->roughness, this->shine);

    this->sub_objects.push_back(base_plane);
    this->sub_objects.push_back(top_plane);
    this->sub_objects.push_back(cylinder_body);
    this->color = color;
}

Vector Cylinder::get_normal(Point p) const {
    return Vector();
}

optional<LitPoint> Cylinder::colide(Ray ray) const{

    double smallest_root = numeric_limits<double>::infinity();
    LitPoint closest_point;

    int cont = 0;
    for(Object* o : this->sub_objects){
        optional<LitPoint> intersect = o->colide(ray);
                
        if (intersect.has_value() && intersect.value().t > 0){
            double t = intersect.value().t;
            Point intersect_point = Point(intersect.value().x, intersect.value().y, intersect.value().z);
            
            if(cont == 0){
                if((intersect_point - base_center).magnitude() <= radius && t < smallest_root) {
                    smallest_root = t;
                    closest_point = intersect.value();
                }
            }
            else if (cont == 1){
                if((intersect_point - top_center).magnitude() <= radius && t < smallest_root) {
                    smallest_root = t;
                    closest_point = intersect.value();
                }
            }
            else if(t < smallest_root) {
                smallest_root = t;
                closest_point = intersect.value();
            }
        }
        cont++;
    }

    if (smallest_root != numeric_limits<double>::infinity()) return closest_point;
    return nullopt;
}
