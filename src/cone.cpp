#include "../headers/cone.h"
#include "../headers/conical_face.h"
#include "../headers/plane.h"

Cone::Cone(){
    this->base_center = Point(0, 0, -100);
    this->radius = 10;
    this->color = Color(255, 0, 0);
    this->material = Material();

    Vector direction = Vector(0, 1, 0);
    Vector inverse_direction = Vector(-direction.x, -direction.y, -direction.z);

    Plane* base_plane = new Plane(base_center, inverse_direction, color, this->material);
    ConicalFace* cone_face = new ConicalFace(base_center, direction, radius, 20, color, this->material);

    sub_objects.push_back(base_plane);
    sub_objects.push_back(cone_face);
}

Cone::Cone(Point base_center, Point tip, double radius, Color color){
    this->base_center = base_center;
    this->radius = radius;
    this->color = color;
    this->material = Material();

    Vector direction = (tip - base_center).normalize();

    Plane* base_plane = new Plane(base_center, direction, color, this->material);
    ConicalFace* cone_face = new ConicalFace(base_center, tip, radius, color, this->material);

    sub_objects.push_back(base_plane);
    sub_objects.push_back(cone_face);
}

Cone::Cone(Point base_center, Point tip, double radius, Color color, Material material){
    this->base_center = base_center;
    this->radius = radius;
    this->color = color;
    this->material = material;

    Vector direction = (tip - base_center).normalize();

    Plane* base_plane = new Plane(base_center, direction, color, this->material);
    ConicalFace* cone_face = new ConicalFace(base_center, tip, radius, color, this->material);

    sub_objects.push_back(base_plane);
    sub_objects.push_back(cone_face);
}

Cone::Cone(Point base_center, Vector direction, double radius, double height, Color color){
    this->base_center = base_center;
    this->radius = radius;
    this->material = Material();

    Plane* base_plane = new Plane(base_center, direction, color, this->material);
    ConicalFace* cone_face = new ConicalFace(base_center, direction, radius, height, color, this->material);

    sub_objects.push_back(base_plane);
    sub_objects.push_back(cone_face);
}

Cone::Cone(Point base_center, Vector direction, double radius, double height, Color color, Material material){
    this->base_center = base_center;
    this->radius = radius;
    this->material = material;

    Plane* base_plane = new Plane(base_center, direction, color, this->material);
    ConicalFace* cone_face = new ConicalFace(base_center, direction, radius, height, color, this->material);

    sub_objects.push_back(base_plane);
    sub_objects.push_back(cone_face);
}

Vector Cone::get_normal(Point p) const{

    return Vector();
}

optional<LitPoint> Cone::colide(Ray ray) const{
    double smallest_root = numeric_limits<double>::infinity();
    LitPoint closest_point;

    optional<LitPoint> intersect_base = sub_objects[0]->colide(ray);
    optional<LitPoint> intersect_cone = sub_objects[1]->colide(ray);
                
    if (intersect_base.has_value() && intersect_base.value().t > 0){
        double t_base = intersect_base.value().t;
        
        Point p_intersect_base = Point(ray.p_inicial + ray.direction * t_base);
        if((p_intersect_base - base_center).magnitude() <= radius && t_base < smallest_root) {
            smallest_root = t_base; 
            closest_point = intersect_base.value();
        }
    }
    if (intersect_cone.has_value() && intersect_cone.value().t > 0){
        double t_cone = intersect_cone.value().t;
        if(t_cone < smallest_root) {
            smallest_root = t_cone;
            closest_point = intersect_cone.value();
        }
    }

    if (smallest_root != numeric_limits<double>::infinity()) return closest_point;
    return nullopt;
}
