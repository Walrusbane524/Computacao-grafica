#include "../headers/obj_mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>

ObjMesh::ObjMesh() : Mesh(){}

ObjMesh::ObjMesh(const string& filepath, Texture* texture_ptr){
    this->texture = texture_ptr;
    this->material = Material();

    ifstream file(filepath);
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

            this->addTriangle(vertexIndices, uvIndices);

            if (vertexIndices.size() > 3) {
                vector<int> face2Indexes = {vertexIndices[0], vertexIndices[2], vertexIndices[3]};
                vector<int> face2UVIndexes = {uvIndices[0], uvIndices[2], uvIndices[3]};
                this->addTriangle(face2Indexes, face2UVIndexes);
            }
        }
    }

    file.close();
}

ObjMesh::ObjMesh(vector<Point> points, vector<vector<int>> faces, vector<Triangle> triangles, vector<Point> uv_points, Texture* texture) : Mesh(points, faces, triangles, uv_points, texture){}