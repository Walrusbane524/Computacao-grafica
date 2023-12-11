#include "../headers/mesh.h"
#include <iostream>

Mesh::Mesh(){}

Mesh::Mesh(vector<Point> points, vector<vector<int>> faces){
    this->points = points;
    this->faces = faces;
    vector<Point> uv_points;

    for(vector<int> face : faces){
        this->triangles.push_back(Triangle(points[face[0]], points[face[1]], points[face[2]], Material(), uv_points, this->texture));
    }
}

Mesh::Mesh(vector<Point> points, vector<vector<int>> faces, vector<Triangle> triangles, vector<Point> uv_points, Material material, Texture* texture){
    this->points = points;
    this->faces = faces;
    this->triangles = triangles;
    this->uv_points = uv_points;
    this->material = material;
    this->texture = texture;
}

Mesh::Mesh(vector<Point> points, vector<vector<int>> faces, vector<Triangle> triangles, vector<Point> uv_points, vector<Vector> normals, Material material, Texture* texture){
    this->points = points;
    this->faces = faces;
    this->triangles = triangles;
    this->uv_points = uv_points;
    this->normals = normals;
    this->material = material;
    this->texture = texture;
}

optional<LitPoint> Mesh::colide(Ray ray) const{

    double smallest_distance = numeric_limits<double>::infinity();
    LitPoint closest_point;
    bool intersected;

    for (Triangle triangle : this->triangles){
        optional<LitPoint> intersect = triangle.colide(ray);

        if (intersect.has_value() && intersect.value().t > 0){
            if(intersect.value().t < smallest_distance){
                smallest_distance = intersect.value().t;
                closest_point = intersect.value();
                intersected = true;
            }
        }
    }

    if(intersected) return closest_point;
    return nullopt;
}

Mesh Mesh::addVertex(double x, double y, double z){
    this->points.push_back(Point(x, y, z));
    return *this;
}

Mesh Mesh::addTriangle(vector<int> indexes, vector<int> uv_indexes){
    this->faces.push_back(indexes);

    vector<Point> uvs;
    uvs.push_back(uv_points[uv_indexes[0]]);
    uvs.push_back(uv_points[uv_indexes[1]]);
    uvs.push_back(uv_points[uv_indexes[2]]);

    this->triangles.push_back(
        Triangle(points[indexes[0]], points[indexes[1]], points[indexes[2]], this->material, uvs, this->texture)
    );

    //cout << "Textured triangle inserted." << endl;

    return *this;
}

Mesh Mesh::addUVPoints(double u, double v, double w){
    this->uv_points.push_back(Point(u, v, w));
    return *this;
}

Mesh Mesh::addNormal(double u, double v, double w){
    this->normals.push_back(Vector(u, v, w));
    return *this;
}

Mesh Mesh::transform(Matrix matrix){
    for(long unsigned int i = 0; i < this->points.size(); i++)
        this->points[i] = this->points[i].transform(matrix);

    vector<Triangle> triangle_aux;

    for(int i = 0; i < faces.size() ; i++){
        triangle_aux.push_back(Triangle(points[faces[i][0]], points[faces[i][1]], points[faces[i][2]], Material(), triangles[i].uv_points, triangles[i].normals, this->texture));
    }
    this->triangles = triangle_aux;

    return *this;
}

void Mesh::translate(){
    Vector vector;
    cout << "Insert the displacement values: " << endl;
    cout << "x = ";
    cin >> vector.x;
    cout << "y = ";
    cin >> vector.y;
    cout << "z = ";
    cin >> vector.z;

    TranslationMatrix matrix = TranslationMatrix(vector);
    this->transform(matrix);
}

void Mesh::rotate(){
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
    this->transform(matrix);
}

void Mesh::scale(){
    Vector vector;
    cout << "Insert the scaling values: " << endl;
    cout << "x = ";
    cin >> vector.x;
    cout << "y = ";
    cin >> vector.y;
    cout << "z = ";
    cin >> vector.z;

    TranslationMatrix matrix = TranslationMatrix(vector);
    this->transform(matrix);
}

void Mesh::translate(Matrix matrix){
    this->transform(matrix);
}

void Mesh::rotate(Matrix matrix){
    this->transform(matrix);
}

void Mesh::scale(Matrix matrix){
    this->transform(matrix);
}


Vector Mesh::get_normal(Point p) const{
    return Vector();
}

Mesh Mesh::addTriangle(vector<int> indexes, vector<int> uv_indexes, vector<int> normal_indexes){
    this->faces.push_back(indexes);

    vector<Point> uvs;
    uvs.push_back(uv_points[uv_indexes[0]]);
    uvs.push_back(uv_points[uv_indexes[1]]);
    uvs.push_back(uv_points[uv_indexes[2]]);

    if(normal_indexes.empty()){
        this->triangles.push_back(
            Triangle(points[indexes[0]], points[indexes[1]], points[indexes[2]], this->material, uvs, this->texture)
        );
    }
    else{
        vector<Vector> normal_points;
        
        normal_points.push_back(normals[normal_indexes[0]]);
        normal_points.push_back(normals[normal_indexes[1]]);
        normal_points.push_back(normals[normal_indexes[2]]);

        this->triangles.push_back(
            Triangle(points[indexes[0]], points[indexes[1]], points[indexes[2]], this->material, uvs, normal_points, this->texture)
        );
    }
    //cout << "Textured triangle inserted." << endl;

    return *this;
}

void Mesh::info(){
    cout << "Mesh = {" << endl;
    cout << " - Vertices       = " << points.size() << endl;
    cout << " - Vertex normals = " << normals.size() << endl;
    cout << " - Faces          = " << faces.size() << endl;
    cout << " - Material       = {";
    cout << "       Kd = (" << material.roughness.x << ", " << material.roughness.y << ", " << material.roughness.z << ")" << endl;
    cout << "       Ke = (" << material.shine.x << ", " << material.shine.y << ", " << material.shine.z << ")" << endl;
    cout << "       Ka = (" << material.ambient.x << ", " << material.ambient.y << ", " << material.ambient.z << ")" << endl;
    cout << "       m  = " << material.reflectivity << endl;
    cout << "   }" << endl;
    cout << " - Texture        = " << texture->path << endl;
    cout << "}" << endl;
}