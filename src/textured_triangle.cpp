#include "../headers/textured_triangle.h"
#include <iostream>

TexturedTriangle::TexturedTriangle(vector<Point> uv_points, Texture* texture_pointer) : Triangle(){
    this->uv_points = uv_points;
    this->texture = texture_pointer;
}

TexturedTriangle::TexturedTriangle(Vector normal, Point p1, Point p2, Point p3, Material material, vector<Point> uv_points, Texture* texture_pointer) : Triangle(normal, p1, p2, p3, material){
    this->uv_points = uv_points;
    this->texture = texture_pointer;
}

TexturedTriangle::TexturedTriangle(Triangle triangle, vector<Point> uv_points, Texture* texture_pointer) : TexturedTriangle(triangle.plane.normal, triangle.p1, triangle.p2, triangle.p3, triangle.material, uv_points, texture_pointer){}

TexturedTriangle::TexturedTriangle(Point p1, Point p2, Point p3, Material material, vector<Point> uv_points, Texture* texture_pointer) : Triangle(p1, p2, p3, material){
    this->uv_points = uv_points;
    this->texture = texture_pointer;
}

optional<LitPoint> TexturedTriangle::colide(Ray ray) const{
    optional<LitPoint> intersect = Triangle::colide(ray);
    if(intersect.has_value() && intersect.value().t > 0){
        LitPoint point = intersect.value();
        Point texture_point = get_uv(point);
        Color color = this->texture->sample(texture_point);
        cout << "Color:" << endl;
        cout << "R = " << color.r << endl;
        cout << "G = " << color.g << endl;
        cout << "B = " << color.b << endl;
        return LitPoint(point, point.t, point.normal, point.material, color);
    }
    else return nullopt;
}

Point TexturedTriangle::get_uv(Point p) const{
    Vector r1 = this->p2 - this->p1;
    Vector r2 = this->p3 - this->p1;

    Vector s1 = this->p1 - p;
    Vector s2 = this->p2 - p;
    Vector s3 = this->p3 - p;

    double total_area = (r1 & r2).magnitude(); 

    double a1 = (s3 & s1).dot(plane.normal);
    double a2 = (s1 & s2).dot(plane.normal);

    double c1 = a1/total_area;
    double c2 = a2/total_area;
    double c3 = 1 - c1 - c2;

    Point texture_point = uv_points[0] * c1 + uv_points[1] * c2 + uv_points[3] * c3;;
    return texture_point;
}