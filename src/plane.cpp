#include <optional>
#include "../headers/plane.h"

Plane::Plane(){
    this->center = Point(0, -10, 0);
    this->normal = Vector(0, 1, 0);
    this->material = Material();
};

Plane::Plane(Point center, Vector normal){
    this->center = center;
    this->normal = normal;
    this->material = Material();
}
Plane::Plane(Point center, Vector normal, Material material){
    this->center = center;
    this->normal = normal;
    this->material = material;
}

optional<LitPoint> Plane::colide(Ray ray) const {
    double divisor = normal.dot(ray.direction);

    if(divisor == 0.0) return nullopt;

    Vector w = ray.p_inicial - center;

    double t = -(normal.dot(w)/divisor);

    Point p_intersect = ray.p_inicial + (ray.direction * t);

    return LitPoint(p_intersect, t, this->normal, this->material);
};

Vector Plane::get_normal(Point p) const{
    return this->normal;
}

void Plane::info(){
    cout << "Plane:" << endl;
    cout << " - Point  = " << "(" << center.x << ", " << center.y << ", " << center.z << ")" << endl;
    cout << " - Normal = " << "(" << normal.x << ", " << normal.y << ", " << normal.z << ")" << endl;
    cout << " - Material    = {";
    cout << "       Kd = (" << material.roughness.x << ", " << material.roughness.y << ", " << material.roughness.z << ")" << endl;
    cout << "       Ke = (" << material.shine.x << ", " << material.shine.y << ", " << material.shine.z << ")" << endl;
    cout << "       Ka = (" << material.ambient.x << ", " << material.ambient.y << ", " << material.ambient.z << ")" << endl;
    cout << "       m  = " << material.reflectivity << endl;
    cout << "   }" << endl;
}

void Plane::translate(){
    Vector vector;
    cout << "Insert the displacement values: " << endl;
    cout << "x = ";
    cin >> vector.x;
    cout << "y = ";
    cin >> vector.y;
    cout << "z = ";
    cin >> vector.z;

    TranslationMatrix matrix = TranslationMatrix(vector);
    this->center = matrix * center;
}

void Plane::rotate(){
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
    switch(type){
        case 1:
            cout << "Insert the angle (radians):" << endl;
            cin >> radians;
            matrix = RotationMatrixXAxis(radians);
        case 2:
            cout << "Insert the angle (radians):" << endl;
            cin >> radians;
            matrix = RotationMatrixYAxis(radians);
        case 3:
            cout << "Insert the angle (radians):" << endl;
            cin >> radians;
            matrix = RotationMatrixZAxis(radians);
        case 4:
            cout << "Insert the angle (radians):" << endl;
            cin >> radians;
            cout << "Insert the u vector values: " << endl;
            cout << "x = ";
            cin >> vector.x;
            cout << "y = ";
            cin >> vector.y;
            cout << "z = ";
            cin >> vector.z;

            Vector vector;
            
            matrix = RotationMatrixUAxis(vector, radians);
    }
    this->normal = matrix * this->normal;
}
void Plane::scale(){
    cout << "You cant scale a plane." << endl;
}