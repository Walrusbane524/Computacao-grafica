#define _USE_MATH_DEFINES
#include <math.h>
#include "../headers/textured_sphere.h"

TexturedSphere::TexturedSphere(Sphere sphere, Texture* texture){
    this->sphere = sphere;
    this->texture = texture;
    this->rotation_matrix = nullptr;
}

optional<LitPoint> TexturedSphere::colide(Ray ray) const{
    optional<LitPoint> intersect = this->sphere.colide(ray);
    
    /*
    cout << "vx.x = " << vx.x << endl;
    cout << "vx.y = " << vx.y << endl;
    cout << "vx.z = " << vx.z << endl;

    cout << "vy.x = " << vy.x << endl;
    cout << "vy.y = " << vy.y << endl;
    cout << "vy.z = " << vy.z << endl;
    */

    if (intersect.has_value() && intersect.value().t > 0){
        LitPoint point = intersect.value();
        Color color = calculate_color(point);

        return LitPoint(point, point.t, point.normal, point.material, color);
    }
    else 
        return intersect;
}

Color TexturedSphere::calculate_color(Point p) const{
    Vector distance_from_center = (p - sphere.center).normalize();

    if(this->rotation_matrix != nullptr) 
        distance_from_center = *rotation_matrix * distance_from_center;

    double u = 0.5 - (atan2(distance_from_center.z, distance_from_center.x))/(2 * M_PI);
    double v = 0.5 - asin(distance_from_center.y)/M_PI;

    //cout << "u = " << u << endl;
    //cout << "v = " << v << endl;

    Point uv = Point(abs(u), abs(v), 0);

    return this->texture->sample(uv);
}  

void TexturedSphere::info(){
    this->sphere.info();
}