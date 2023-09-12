#include "../headers/triangle.h"

Triangle::Triangle(){
    this->p1 = Point(-10, -10, -100);
    this->p2 = Point(10, -10, -100);
    this->p3 = Point(0, -10, -110);
    this->plane = Plane(p1, Vector(0, 1, 0), Color(255, 0, 0));
}

Triangle::Triangle(Vector normal, Point p1, Point p2, Point p3){
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->plane = Plane(p1, normal, Color(255, 0, 0));
}

optional<LitPoint> Triangle::colide(Ray ray) const {
    optional<LitPoint> intersect = this->plane.colide(ray);
    if(intersect.has_value() && intersect.value().t > 0){
        Vector r1 = p2 - p1;
        Vector r2 = p3 - p1;

        Vector s1 = p1 - intersect.value();
        Vector s2 = p2 - intersect.value();
        Vector s3 = p3 - intersect.value();

        double total_area = (r1 & r2).magnitude();
        double a1 = (s3 & s1).magnitude();
        double a2 = (s1 & s2).magnitude();

        double c1 = a1/total_area;
        double c2 = a2/total_area;
        double c3 = 1 - (c1 + c2);

        if(c1 < 0 || c2 < 0 || c3 < 0) return nullopt;
        return intersect.value();
    }
    return nullopt;
}

Vector Triangle::get_normal(Point p) const{
    return this->plane.normal;
}
