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

Mesh::Mesh(vector<Point> points, vector<vector<int>> faces, vector<Triangle> triangles, vector<Point> uv_points, Texture* texture){
    this->points = points;
    this->faces = faces;
    this->triangles = triangles;
    this->uv_points = uv_points;
    this->texture = texture;
}

Mesh::Mesh(vector<Point> points, vector<vector<int>> faces, vector<Triangle> triangles, vector<Point> uv_points, vector<Vector> normals, Texture* texture){
    this->points = points;
    this->faces = faces;
    this->triangles = triangles;
    this->uv_points = uv_points;
    this->texture = texture;
    this->normals = normals;
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
        triangle_aux.push_back(Triangle(points[faces[i][0]], points[faces[i][1]], points[faces[i][2]], Material(), triangles[i].uv_points, this->texture));
    }
    this->triangles = triangle_aux;

    return *this;
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

    if(normal_indexes.empty())
        this->triangles.push_back(
            Triangle(points[indexes[0]], points[indexes[1]], points[indexes[2]], this->material, uvs, this->texture)
        );
    else
        this->triangles.push_back(
            Triangle(points[indexes[0]], points[indexes[1]], points[indexes[2]], this->material, uvs, this->texture)
        );

    //cout << "Textured triangle inserted." << endl;

    return *this;
}