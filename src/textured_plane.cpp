#include "../headers/textured_plane.h"

TexturedPlane::TexturedPlane(Plane plane, Vector vector, Texture* texture, double scale_factor){
    this->plane = plane;
    this->texture = texture;
    this->vx = this->plane.normal & vector;
    this->vy = this->vx & this->plane.normal;
    this->scale_factor = scale_factor;
}

optional<LitPoint> TexturedPlane::colide(Ray ray) const{
    optional<LitPoint> intersect = this->plane.colide(ray);
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

Color TexturedPlane::calculate_color(Point p) const{
    Vector distance_from_center = p - plane.center;

    double u = this->vx.dot(distance_from_center) * 1/scale_factor;
    double v = this->vy.dot(distance_from_center) * 1/scale_factor;

    //cout << "u = " << u << endl;
    //cout << "v = " << v << endl;

    Point uv = Point(u, v, 0);

    return this->texture->sample(uv);
}  

void TexturedPlane::info(){
    this->plane.info();
}