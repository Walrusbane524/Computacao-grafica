#include "../headers/mesh.h"

Mesh::Mesh(){}

Mesh::Mesh(vector<Point> points, vector<vector<int>> faces){
    this->points = points;
    this->faces = faces;

    for(vector<int> face : faces){
        this->triangles.push_back(Triangle(points[face[0]], points[face[1]], points[face[2]], Material()));
    }
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

Mesh Mesh::addTriangle(vector<int> indices){
    this->faces.push_back(indices);
    this->triangles.push_back(Triangle(points[indices[0]], points[indices[1]], points[indices[2]], Material()));
    return *this;
}

void Mesh::transform(Matrix matrix){
    for(long unsigned int i = 0; i < this->points.size(); i++)
        this->points[i] = this->points[i].transform(matrix);

    this->triangles.clear();

    for(vector<int> face : faces){
        this->triangles.push_back(Triangle(points[face[0]], points[face[1]], points[face[2]], Material()));
    }
}

Vector Mesh::get_normal(Point p) const{
    return Vector();
}