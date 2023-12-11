#include "../headers/cylinder.h"
#include "../headers/cylindrical_face.h"
#include "../headers/plane.h"

Cylinder::Cylinder(Point base_center, Point top_center, double radius){
    
    this->height = (top_center - base_center).magnitude();
    this->direction = (top_center - base_center).normalize();
    Vector inverse_direction = Vector(-direction.x, -direction.y, -direction.z);

    this->radius = radius;
    this->base_center = base_center;
    this->top_center = top_center;
    this->material = Material();

    Plane* base_plane = new Plane(base_center, inverse_direction, this->material);
    Plane* top_plane = new Plane(top_center, direction, this->material);
    CylindricalFace* cylinder_body = new CylindricalFace(base_center, this->direction, radius, this->height, this->material);

    this->sub_objects.push_back(base_plane);
    this->sub_objects.push_back(top_plane);
    this->sub_objects.push_back(cylinder_body);
}

Cylinder::Cylinder(Point base_center, Point top_center, double radius, Material material){
    
    this->height = (top_center - base_center).magnitude();
    this->direction = (top_center - base_center).normalize();
    Vector inverse_direction = Vector(-direction.x, -direction.y, -direction.z);

    this->radius = radius;
    this->base_center = base_center;
    this->top_center = top_center;
    this->material = material;

    Plane* base_plane = new Plane(base_center, inverse_direction, this->material);
    Plane* top_plane = new Plane(top_center, direction, this->material);
    CylindricalFace* cylinder_body = new CylindricalFace(base_center, direction, radius, height, this->material);

    this->sub_objects.push_back(base_plane);
    this->sub_objects.push_back(top_plane);
    this->sub_objects.push_back(cylinder_body);
}

Cylinder::Cylinder(Point base_center, Vector direction, double radius, double height){
    
    Point top_center = Point(base_center + (direction * height));

    this->radius = radius;
    this->base_center = base_center;
    this->top_center = top_center;
    this->material = Material();
    this->direction = direction;
    this->height = height;
    this->radius = radius;

    Vector inverse_direction = Vector(-direction.x, -direction.y, -direction.z);

    Plane* base_plane = new Plane(base_center, inverse_direction, this->material);
    Plane* top_plane = new Plane(top_center, direction, this->material);
    CylindricalFace* cylinder_body = new CylindricalFace(base_center, direction, radius, height, this->material);

    this->sub_objects.push_back(base_plane);
    this->sub_objects.push_back(top_plane);
    this->sub_objects.push_back(cylinder_body);
}

Cylinder::Cylinder(Point base_center, Vector direction, double radius, double height, Material material){
    
    Point top_center = Point(base_center + (direction * height));

    this->radius = radius;
    this->base_center = base_center;
    this->top_center = top_center;
    this->material = material;
    this->height = height;
    this->direction = direction;

    Plane* base_plane = new Plane(base_center, direction, this->material);
    Plane* top_plane = new Plane(top_center, direction, this->material);
    CylindricalFace* cylinder_body = new CylindricalFace(base_center, direction, radius, height, this->material);

    this->sub_objects.push_back(base_plane);
    this->sub_objects.push_back(top_plane);
    this->sub_objects.push_back(cylinder_body);
}

Vector Cylinder::get_normal(Point p) const {
    return Vector();
}

optional<LitPoint> Cylinder::colide(Ray ray) const{

    double smallest_t = numeric_limits<double>::infinity();
    LitPoint closest_point;

    int cont = 0;
    for(Object* o : this->sub_objects){
        optional<LitPoint> intersect = o->colide(ray);
                
        if (intersect.has_value() && intersect.value().t > 0){
            double t = intersect.value().t;
            Point intersect_point = Point(intersect.value().x, intersect.value().y, intersect.value().z);
            
            if(cont == 0){
                if((intersect_point - base_center).magnitude() <= radius && t < smallest_t) {
                    smallest_t = t;
                    closest_point = intersect.value();
                }
            }
            else if (cont == 1){
                if((intersect_point - top_center).magnitude() <= radius && t < smallest_t) {
                    smallest_t = t;
                    closest_point = intersect.value();
                }
            }
            else if(t < smallest_t) {
                smallest_t = t;
                closest_point = intersect.value();
            }
        }
        cont++;
    }

    if (smallest_t != numeric_limits<double>::infinity()) return closest_point;
    return nullopt;
}

void Cylinder::info(){
    cout << "Cylinder = {" << endl;
    for(Object* o : sub_objects){
        o->info();
    }
    cout << "}" << endl;
}

void Cylinder::translate(){
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

void Cylinder::rotate(){
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
    double angle;
    Matrix matrix;
    cout << "Insert the angle (degrees):" << endl;
    cin >> angle;
    switch(type){
        case 1:
            matrix = RotationMatrixXAxis(angle);
        break;
        case 2:
            matrix = RotationMatrixYAxis(angle);
        break;
        case 3:
            matrix = RotationMatrixZAxis(angle);
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
            
            matrix = RotationMatrixUAxis(vector, angle);
        break;
    }
}

void Cylinder::scale(){
    Vector vector;
    cout << "Insert the scaling values: " << endl;
    cout << "x = ";
    cin >> vector.x;
    cout << "y = ";
    cin >> vector.y;
    cout << "z = ";
    cin >> vector.z;

    ScaleMatrix matrix = ScaleMatrix(vector);

    this->scale(matrix);
}

void Cylinder::translate(Matrix matrix){
    this->top_center = matrix * top_center;
    this->base_center = matrix * base_center;

    for(Object* obj_ptr : sub_objects)
        obj_ptr->translate(matrix);
}
void Cylinder::rotate(Matrix matrix){
    this->base_center = matrix * base_center;
    this->top_center = matrix * top_center;

    for(Object* obj_ptr : sub_objects)
        obj_ptr->rotate(matrix);
}
void Cylinder::scale(Matrix matrix){
    double r_factor;
    double h_factor;

    cout << "Insert the radius multiplier: " << endl;
    cin >> r_factor;

    cout << "Insert the height multiplier: " << endl;
    cin >> h_factor;
    
    this->radius *= r_factor;
    this->height *= h_factor;

    this->base_center = matrix * base_center;
    this->top_center = base_center + (direction * height);

    Vector inverse_direction = Vector(-direction.x, -direction.y, -direction.z);

    Plane* new_base_plane = new Plane(base_center, inverse_direction, this->material);
    Plane* new_top_plane = new Plane(top_center, direction, this->material);
    CylindricalFace* new_cylinder_body = new CylindricalFace(base_center, this->direction, this->radius, this->height, this->material);

    sub_objects.clear();

    sub_objects.push_back(new_base_plane);
    sub_objects.push_back(new_top_plane);
    sub_objects.push_back(new_cylinder_body);

    //sub_objects[2]->info();
}