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
    cout << "TexturedSphere = {" << endl;
    this->sphere.info();
    cout << " - Texture        = " << texture->path << endl;
    cout << "}" << endl;
}

void TexturedSphere::translate(){
    this->sphere.translate();
}

void TexturedSphere::rotate(){
    Vector vector;
    int type = 0;
    while(type > 4 || type < 1){
        cout << "Select a type of rotation:" << endl;
        cout << "1. X-axis" << endl;
        cout << "2. Y-axis" << endl;
        cout << "3. Z-axis" << endl;
        cout << "4. U-vector-axis" << endl;
        cin >> type;
        if(type > 4 || type < 1)
            cout << "Insert a valid number!" << endl;
    }
    double radians;
    
    cout << "Insert the angle (radians):" << endl;
    cin >> radians;

    switch(type){
        case 1:
            rotation_matrix = new RotationMatrixXAxis(radians);
        case 2:
            rotation_matrix = new RotationMatrixYAxis(radians);
        case 3:
            rotation_matrix = new RotationMatrixZAxis(radians);
        case 4:
            cout << "Insert the u vector values: " << endl;
            cout << "x = ";
            cin >> vector.x;
            cout << "y = ";
            cin >> vector.y;
            cout << "z = ";
            cin >> vector.z;

            Vector vector;
            
            rotation_matrix = new RotationMatrixUAxis(vector, radians);
    }
    rotate(*rotation_matrix);
}

void TexturedSphere::scale(){
    this->sphere.scale();
}

void TexturedSphere::translate(Matrix matrix){
    this->sphere.translate(matrix);
}
void TexturedSphere::rotate(Matrix matrix){
    this->rotation_matrix = new RotationMatrixUAxis(matrix.matrix);
    this->sphere.rotate(matrix);
}
void TexturedSphere::scale(Matrix matrix){
    this->sphere.scale(matrix);
}