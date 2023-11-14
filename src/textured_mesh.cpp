#include "../headers/textured_mesh.h"
#include "../headers/textured_triangle.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

TexturedMesh::TexturedMesh(const char* obj_path, const char* texture_path){
    this->texture = new Texture(texture_path);
    this->material = Material();

    ifstream file(obj_path);
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string type;
        iss >> type;

        //cout << "type = " << type << endl;
        
        if (type == "v") {
            double x, y, z;
            iss >> x >> y >> z;
            this->addVertex(x, y, z);
        } else if (type == "vt") {
            double u, v;
            iss >> u >> v;
            this->addUVPoints(u, v, 0.0);
        } else if (type == "f") {
            string vertex;
            vector<int> vertexIndices;
            vector<int> uvIndices;

            while (iss >> vertex) {
                size_t pos = vertex.find('/');
                int index = stoi(vertex.substr(0, pos));

                // Convert to 0-based index
                index = (index > 0) ? index - 1 : this->points.size() + index;
                vertexIndices.push_back(index);

                // Check if UV coordinate is present
                if (pos != string::npos) {
                    int uvIndex = stoi(vertex.substr(pos + 1));
                    // Convert to 0-based UV index
                    uvIndex = (uvIndex > 0) ? uvIndex - 1 : this->uv_points.size() + uvIndex;
                    uvIndices.push_back(uvIndex);
                }
            }

            this->addTexturedTriangle(vertexIndices, uvIndices);

            if (vertexIndices.size() > 3) {
                vector<int> face2Indexes = {vertexIndices[0], vertexIndices[2], vertexIndices[3]};
                vector<int> face2UVIndexes = {uvIndices[0], uvIndices[2], uvIndices[3]};
                this->addTexturedTriangle(face2Indexes, face2UVIndexes);
            }
        }
    }

    file.close();
}

Mesh TexturedMesh::addTexturedTriangle(vector<int> indexes, vector<int> uv_indexes){
    this->faces.push_back(indexes);

    vector<Point> uvs;
    uvs.push_back(uv_points[0]);
    uvs.push_back(uv_points[1]);
    uvs.push_back(uv_points[2]);

    this->triangles.push_back(
        TexturedTriangle(Triangle(points[indexes[0]], points[indexes[1]], points[indexes[2]], this->material),
                         uvs,
                         this->texture
        )
    );

    //cout << "Textured triangle inserted." << endl;

    return *this;
}

Mesh TexturedMesh::addUVPoints(double u, double v, double w){
    this->uv_points.push_back(Point(u, v, w));
    return *this;
}

Point TexturedMesh::get_uv(Point p) const{
    return Point();
}

optional<LitPoint> TexturedMesh::colide(Ray ray) const {

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