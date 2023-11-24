#include "../headers/triangle.h"
#include <iostream>

using namespace std;

Triangle::Triangle(){
    this->p1 = Point(-10, -10, -100);
    this->p2 = Point(10, -10, -100);
    this->p3 = Point(0, -10, -110);
    this->plane = Plane(p1, Vector(0, 1, 0));
    this->material = Material();
    this->texture = nullptr;
}

Triangle::Triangle(Vector normal, Point p1, Point p2, Point p3, Material material, vector<Point> uv_points, Texture* texture_ptr){
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->plane = Plane(p1, normal);
    this->material = material;
    this->uv_points = uv_points;
    this->texture = texture_ptr;
}
Triangle::Triangle(Point p1, Point p2, Point p3, Material material, vector<Point> uv_points, Texture* texture_ptr){
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    Vector a1 = p2 - p1;
    Vector a2 = p3 - p1;
    Vector normal = (a1 & a2).normalize();
    this->plane = Plane(p1, normal);
    this->material = material;
    this->uv_points = uv_points;
    this->texture = texture_ptr;
}

Triangle::Triangle(Point p1, Point p2, Point p3, Material material, vector<Point> uv_points, vector<Vector> normals, Texture* texture) : Triangle(p1, p2, p3, material, uv_points, texture){
    this->normals = normals;
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

        //cout << "total_area = " << total_area << endl << endl; 

        double a1 = (s3 & s1).dot(plane.normal);
        double a2 = (s1 & s2).dot(plane.normal);

        double c1 = a1/total_area;
        double c2 = a2/total_area;
        double c3 = 1 - c1 - c2;


        if(c1 < 0 || c2 < 0 || c3 < 0) 
            return nullopt;

        LitPoint point = intersect.value();
        /*
        cout << "Normal before interpolation:" << endl;
        cout << "x = " << point.normal.x << endl;
        cout << "y = " << point.normal.y << endl;
        cout << "z = " << point.normal.z << endl;
        */
        if(!normals.empty()){
            point.normal = get_normal(point);
            /*
            cout << "Normal after interpolation:" << endl;
            cout << "x = " << point.normal.x << endl;
            cout << "y = " << point.normal.y << endl;
            cout << "z = " << point.normal.z << endl;
            */
        }

        if(this->texture != nullptr){
            
            Point texture_point = get_uv(point);
            Color color = this->texture->sample(texture_point);
            /*
            cout << "Color:" << endl;
            cout << "R = " << color.r << endl;
            cout << "G = " << color.g << endl;
            cout << "B = " << color.b << endl;
            */
            return LitPoint(point, point.t, point.normal, point.material, color);
        }
        else
            return intersect.value();
    }
    return nullopt;
}

void Triangle::transform(Matrix matrix){
    this->p1 = matrix * this->p1;
    this->p2 = matrix * this->p2;
    this->p3 = matrix * this->p3;
}

Vector Triangle::get_normal(Point p) const{
    Vector r1 = this->p2 - this->p1;
    Vector r2 = this->p3 - this->p1;

    Vector s1 = this->p1 - p;
    Vector s2 = this->p2 - p;
    Vector s3 = this->p3 - p;

    double total_area = (r1 & r2).magnitude(); 

    double a1 = (s3 & s1).dot(plane.normal);
    double a2 = (s1 & s2).dot(plane.normal);
    double a3 = (s2 & s3).dot(plane.normal);

    double c1 = a1/total_area;
    double c2 = a2/total_area;
    double c3 = a3/total_area;

    Point normal_point = normals[0] * c3 + normals[1] * c1 + normals[2] * c2;;
    return normal_point;
}


Point Triangle::get_uv(Point p) const{
    Vector r1 = this->p2 - this->p1;
    Vector r2 = this->p3 - this->p1;

    Vector s1 = this->p1 - p;
    Vector s2 = this->p2 - p;
    Vector s3 = this->p3 - p;

    double total_area = (r1 & r2).magnitude(); 

    double a1 = (s3 & s1).dot(plane.normal);
    double a2 = (s1 & s2).dot(plane.normal);
    double a3 = (s2 & s3).dot(plane.normal);

    double c1 = a1/total_area;
    double c2 = a2/total_area;
    double c3 = a3/total_area;

    Point texture_point = uv_points[0] * c3 + uv_points[1] * c1 + uv_points[2] * c2;;
    texture_point.y = 1 - texture_point.y;

    texture_point.x -= floor(texture_point.x);
    texture_point.y -= floor(texture_point.y);
/*
    cout << "Baricentric coordinates:" << endl;
    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;
    cout << "c3 = " << c3 << endl;

    cout << "Texture:" << endl;
    cout << "u = " << texture_point.x << endl;
    cout << "v = " << texture_point.y << endl;
    cout << "w = " << texture_point.z << endl;
   
*/
    return texture_point;
}
