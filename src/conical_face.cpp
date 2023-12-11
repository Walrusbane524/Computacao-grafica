#include "../headers/conical_face.h"
#include <iostream>

ConicalFace::ConicalFace(){
    this->base_center = Point(0, 0, -100);
    this->direction = Vector(0, 1, 0);
    this->height = 20;
    this->radius = 10;
    this->tip = this->base_center + (this->direction * this->height);
    this->material = Material();
}
ConicalFace::ConicalFace(Point base_center, Point tip, double radius){
    Vector h = tip - base_center;

    this->base_center = base_center;
    this->direction = h.normalize();
    this->height = h.magnitude();
    this->radius = radius;
    this->tip = tip;
    this->material = Material();
}
ConicalFace::ConicalFace(Point base_center, Point tip, double radius, Material material){
    Vector h = tip - base_center;

    this->base_center = base_center;
    this->direction = h.normalize();
    this->height = h.magnitude();
    this->radius = radius;
    this->tip = tip;
    this->material = material;
}
ConicalFace::ConicalFace(Point base_center, Vector direction, double radius, double height){
    this->base_center = base_center;
    this->direction = direction;
    this->height = height;
    this->radius = radius;
    this->tip = this->base_center + (this->direction * this->height);
    this->material = Material();
}
ConicalFace::ConicalFace(Point base_center, Vector direction, double radius, double height, Material material){
    this->base_center = base_center;
    this->direction = direction;
    this->height = height;
    this->radius = radius;
    this->tip = this->base_center + (this->direction * this->height);
    this->material = material;
}

Vector ConicalFace::get_normal(Point p) const{
    return ((p * this->tip) & this->direction).normalize();
}

optional<LitPoint> ConicalFace::colide(Ray ray) const{
    
    Vector v = this->tip - ray.p_inicial;
    Vector dr = ray.direction;

    double cos_ = height/sqrt(height * height + radius * radius);

    double a = pow(dr.dot(direction), 2) - dr.dot(dr) * pow(cos_, 2);
    double b = (v.dot(dr) * pow(cos_, 2) - (v.dot(direction)) * (dr.dot(direction)));
    double c = pow(v.dot(direction), 2) - (v.dot(v)) * pow(cos_, 2);

    double delta = pow(b, 2) - a * c;

    if(delta <= 0) return nullopt;

    double t_1 = (-b - sqrt(delta))/(a);
    double t_2 = (-b + sqrt(delta))/(a);
    double smallest_t;

    Point p_intersect_1 = Point(ray.p_inicial + (ray.direction * t_1));
    double distance_along_axis_1 = (tip - p_intersect_1).dot(direction);

    Point p_intersect_2 = Point(ray.p_inicial + (ray.direction * t_2));
    double distance_along_axis_2 = (tip - p_intersect_2).dot(direction);

    if(distance_along_axis_1 > 0 && distance_along_axis_1 < this->height){
        if(distance_along_axis_2 > 0 && distance_along_axis_2 < this->height && t_2 < t_1) smallest_t = t_2;
        else smallest_t = t_1;
    }
    else if(distance_along_axis_2 > 0 && distance_along_axis_2 < this->height) smallest_t = t_2;
    else return nullopt;

    Point p_intersect = ray.p_inicial + (ray.direction * smallest_t);

    Vector normal = this->get_normal(p_intersect);

    return LitPoint(p_intersect, smallest_t, normal, this->material);
}

void ConicalFace::info(){
    cout << "Conical Face = {" << endl;
    cout << " - Base center = " << "(" << base_center.x << ", " << base_center.y << ", " << base_center.z << ")" << endl;
    cout << " - Tip Point   = " << "(" << tip.x << ", " << tip.y << ", " << tip.z << ")" << endl;
    cout << " - Direction   = " << "(" << direction.x << ", " << direction.y << ", " << direction.z << ")" << endl;
    cout << " - Radius      = " << radius << endl;
    cout << " - Height      = " << height << endl;
    cout << " - Material    = {" << endl;
    cout << "       Kd = (" << material.roughness.x << ", " << material.roughness.y << ", " << material.roughness.z << ")" << endl;
    cout << "       Ke = (" << material.shine.x << ", " << material.shine.y << ", " << material.shine.z << ")" << endl;
    cout << "       Ka = (" << material.ambient.x << ", " << material.ambient.y << ", " << material.ambient.z << ")" << endl;
    cout << "       m  = " << material.reflectivity << endl;
    cout << "   }" << endl;
    cout << "}" << endl;
}

void ConicalFace::translate(){
    Vector vector;
    cout << "Insert the displacement values: " << endl;
    cout << "x = ";
    cin >> vector.x;
    cout << "y = ";
    cin >> vector.y;
    cout << "z = ";
    cin >> vector.z;

    TranslationMatrix matrix = TranslationMatrix(vector);
    translate(matrix);
}

void ConicalFace::rotate(){
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
    Matrix matrix;
    cout << "Insert the angle (degrees):" << endl;
    cin >> radians;
    switch(type){
        case 1:
            matrix = RotationMatrixXAxis(radians);
        break;
        case 2:
            matrix = RotationMatrixYAxis(radians);
        break;
        case 3:
            matrix = RotationMatrixZAxis(radians);
        break;
        case 4:
            cout << "Insert the u vector values: " << endl;
            cout << "x = ";
            cin >> vector.x;
            cout << "y = ";
            cin >> vector.y;
            cout << "z = ";
            cin >> vector.z;

            Vector vector;
            
            matrix = RotationMatrixUAxis(vector, radians);
        break;
    }
    this->rotate(matrix);
}

void ConicalFace::scale(){
    Vector vector;
    cout << "Insert the scaling values: " << endl;
    cout << "x = ";
    cin >> vector.x;
    cout << "y = ";
    cin >> vector.y;
    cout << "z = ";
    cin >> vector.z;

    TranslationMatrix matrix = TranslationMatrix(vector);

    this->scale(matrix);
}

void ConicalFace::translate(Matrix matrix){
    this->base_center = matrix * base_center;
    this->tip = matrix * tip;
}
void ConicalFace::rotate(Matrix matrix){
    this->base_center = matrix * this->base_center;
    this->tip = matrix * this->tip;
    this->height = (tip - base_center).magnitude();
    this->direction = (tip - base_center).normalize();
}
void ConicalFace::scale(Matrix matrix){
    double r_factor;
    double h_factor;

    cout << "Insert the radius multiplier: " << endl;
    cin >> r_factor;

    cout << "Insert the height multiplier: " << endl;
    cin >> h_factor;
    
    this->base_center = matrix * base_center;
    this->radius *= r_factor;
    this->height *= h_factor;
    this->tip = base_center + (direction * height);
}