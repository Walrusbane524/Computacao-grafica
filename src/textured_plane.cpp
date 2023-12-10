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

void TexturedPlane::translate(){
    Vector vector;
    cout << "Insert the displacement values: " << endl;
    cout << "x = ";
    cin >> vector.x;
    cout << "y = ";
    cin >> vector.y;
    cout << "z = ";
    cin >> vector.z;

    TranslationMatrix matrix = TranslationMatrix(vector);
    this->plane.center = matrix * plane.center;
}

void TexturedPlane::rotate(){
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
    this->plane.normal = matrix * this->plane.normal;
}
void TexturedPlane::scale(){
    double factor;
    cout << "Insert the texture scale multiplier:" << endl;
    cin >> factor;

    this->scale_factor *= factor;
}