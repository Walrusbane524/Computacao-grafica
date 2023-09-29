#include "../headers/triangle.h"
#include <iostream>

using namespace std;

Triangle::Triangle(){
    this->p1 = Point(-10, -10, -100);
    this->p2 = Point(10, -10, -100);
    this->p3 = Point(0, -10, -110);
    this->plane = Plane(p1, Vector(0, 1, 0), Color(255, 0, 0));
    this->material = Material();
}

Triangle::Triangle(Vector normal, Point p1, Point p2, Point p3, Material material){
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->plane = Plane(p1, normal, Color(255, 0, 0));
    this->material = material;
}

optional<LitPoint> Triangle::colide(Ray ray) const {
    optional<LitPoint> intersect = this->plane.colide(ray);
    if(intersect.has_value() && intersect.value().t > 0){

        Vector r1 = p2 - p1;
        Vector r2 = p3 - p1;

        Vector s1 = p1 - intersect.value();
        Vector s2 = p2 - intersect.value();
        Vector s3 = p3 - intersect.value();

        /*
        cout << "s1.x = " << s1.x << endl;
        cout << "s1.y = " << s1.y << endl;
        cout << "s1.z = " << s1.z << endl << endl;

        cout << "s3.x = " << s3.x << endl;
        cout << "s3.y = " << s3.y << endl;
        cout << "s3.z = " << s3.z << endl << endl;
        */

        double total_area = (r1 & r2).magnitude();

        //cout << "total_area = " << total_area << endl << endl; 

        double a1 = (s3 & s1).dot(plane.normal);
        double a2 = (s1 & s2).dot(plane.normal);

        double c1 = a1/total_area;
        double c2 = a2/total_area;
        double c3 = 1 - c1 - c2;

        /*
        cout << "c1 = " << c1 << endl;
        cout << "c2 = " << c2 << endl;
        cout << "c3 = " << c3 << endl;
        */

        if(c1 < 0 || c2 < 0 || c3 < 0) return nullopt;
        return intersect.value();
    }
    return nullopt;
}

Vector Triangle::get_normal(Point p) const{
    return this->plane.normal;
}
