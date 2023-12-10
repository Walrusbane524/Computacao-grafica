#include "../headers/cone.h"
#include "../headers/conical_face.h"
#include "../headers/plane.h"

Cone::Cone(){
    this->base_center = Point(0, 0, -100);
    this->radius = 10;
    this->material = Material();

    this->direction = Vector(0, 1, 0);
    this->height = 20;

    Vector inverse_direction = Vector(-direction.x, -direction.y, -direction.z);

    Plane* base_plane = new Plane(base_center, inverse_direction, this->material);
    ConicalFace* cone_face = new ConicalFace(base_center, direction, radius, height, this->material);

    sub_objects.push_back(base_plane);
    sub_objects.push_back(cone_face);
}

Cone::Cone(Point base_center, Point tip, double radius){
    this->base_center = base_center;
    this->radius = radius;
    this->height = (tip - base_center).magnitude();
    this->material = Material();
    this->direction = (tip - base_center).normalize();

    Plane* base_plane = new Plane(base_center, direction, this->material);
    ConicalFace* cone_face = new ConicalFace(base_center, tip, radius, this->material);

    sub_objects.push_back(base_plane);
    sub_objects.push_back(cone_face);
}

Cone::Cone(Point base_center, Point tip, double radius, Material material){
    this->base_center = base_center;
    this->radius = radius;
    this->material = material;
    this->height = (tip - base_center).magnitude();
    this->direction = (tip - base_center).normalize();

    Plane* base_plane = new Plane(base_center, direction, this->material);
    ConicalFace* cone_face = new ConicalFace(base_center, tip, radius, this->material);

    sub_objects.push_back(base_plane);
    sub_objects.push_back(cone_face);
}

Cone::Cone(Point base_center, Vector direction, double radius, double height){
    this->base_center = base_center;
    this->radius = radius;
    this->material = Material();
    this->height = height;
    this->direction = direction;

    Plane* base_plane = new Plane(base_center, direction, this->material);
    ConicalFace* cone_face = new ConicalFace(base_center, direction, radius, height, this->material);

    sub_objects.push_back(base_plane);
    sub_objects.push_back(cone_face);
}

Cone::Cone(Point base_center, Vector direction, double radius, double height, Material material){
    this->base_center = base_center;
    this->radius = radius;
    this->material = material;
    this->direction = direction;
    this->height = height;

    Plane* base_plane = new Plane(base_center, direction, this->material);
    ConicalFace* cone_face = new ConicalFace(base_center, direction, radius, height, this->material);

    sub_objects.push_back(base_plane);
    sub_objects.push_back(cone_face);
}

Vector Cone::get_normal(Point p) const{

    return Vector();
}

optional<LitPoint> Cone::colide(Ray ray) const{
    double smallest_root = numeric_limits<double>::infinity();
    LitPoint closest_point;

    optional<LitPoint> intersect_base = sub_objects[0]->colide(ray);
    optional<LitPoint> intersect_cone = sub_objects[1]->colide(ray);
                
    if (intersect_base.has_value() && intersect_base.value().t > 0){
        double t_base = intersect_base.value().t;
        
        Point p_intersect_base = Point(ray.p_inicial + ray.direction * t_base);
        if((p_intersect_base - base_center).magnitude() <= radius && t_base < smallest_root) {
            smallest_root = t_base; 
            closest_point = intersect_base.value();
        }
    }
    if (intersect_cone.has_value() && intersect_cone.value().t > 0){
        double t_cone = intersect_cone.value().t;
        if(t_cone < smallest_root) {
            smallest_root = t_cone;
            closest_point = intersect_cone.value();
        }
    }

    if (smallest_root != numeric_limits<double>::infinity()) return closest_point;
    return nullopt;
}

void Cone::info(){
    cout << "Cone = {" << endl;
    for(Object* o : sub_objects){
        o->info();
    }
    cout << "}" << endl;
}

void Cone::translate(){
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

void Cone::rotate(){
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
    this->rotate(matrix);
}

void Cone::scale(){
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

void Cone::translate(Matrix matrix){
    this->base_center = matrix * base_center;

    for(Object* obj_ptr : sub_objects)
        obj_ptr->translate(matrix);
}

void Cone::rotate(Matrix matrix){
    this->base_center = matrix * base_center;

    for(Object* obj_ptr : sub_objects)
        obj_ptr->rotate(matrix);
}

void Cone::scale(Matrix matrix){
    double r_factor;
    double h_factor;

    cout << "Insert the radius multiplier: " << endl;
    cin >> r_factor;

    cout << "Insert the height multiplier: " << endl;
    cin >> h_factor;

    this->radius *= r_factor;
    this->height *= h_factor;

    this->base_center = matrix * base_center;
    
    sub_objects.clear();

    Vector inverse_direction = Vector(-direction.x, -direction.y, -direction.z);

    Plane* base_plane = new Plane(base_center, inverse_direction, this->material);
    ConicalFace* cone_face = new ConicalFace(base_center, direction, radius, height, this->material);

    sub_objects.push_back(base_plane);
    sub_objects.push_back(cone_face);
}
