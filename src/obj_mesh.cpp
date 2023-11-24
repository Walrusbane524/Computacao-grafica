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
        } else if (type == "vn") {
            double u, v, w;
            iss >> u >> v >> w;
            this->addNormal(u, v, w);
        } else if (type == "f") {
            string vertex;
            vector<int> vertexIndices;
            vector<int> uvIndices;
            vector<int> normalIndices; // Add normal indices vector

            while (iss >> vertex) {
                size_t pos1 = vertex.find('/');
                size_t pos2 = vertex.find('/', pos1 + 1);

                int index = stoi(vertex.substr(0, pos1));
                // Convert to 0-based index
                index = (index > 0) ? index - 1 : this->points.size() + index;
                vertexIndices.push_back(index);

                // Check if UV coordinate is present
                if (pos1 != string::npos) {
                    int uvIndex = stoi(vertex.substr(pos1 + 1, pos2 - pos1 - 1));
                    // Convert to 0-based UV index
                    uvIndex = (uvIndex > 0) ? uvIndex - 1 : this->uv_points.size() + uvIndex;
                    uvIndices.push_back(uvIndex);
                }

                // Check if normal index is present
                if (pos2 != string::npos) {
                    int normalIndex = stoi(vertex.substr(pos2 + 1));
                    // Convert to 0-based normal index
                    normalIndex = (normalIndex > 0) ? normalIndex - 1 : this->normals.size() + normalIndex;
                    normalIndices.push_back(normalIndex);
                }
            }

            this->addTriangle(vertexIndices, uvIndices, normalIndices);

            if (vertexIndices.size() > 3) {
                vector<int> face2Indexes = {vertexIndices[0], vertexIndices[2], vertexIndices[3]};
                vector<int> face2UVIndexes = {uvIndices[0], uvIndices[2], uvIndices[3]};
                vector<int> face2NormalIndexes = {normalIndices[0], normalIndices[2], normalIndices[3]};
                this->addTriangle(face2Indexes, face2UVIndexes, face2NormalIndexes);
            }
        }
    }

    file.close();
}

ObjMesh::ObjMesh(vector<Point> points, vector<vector<int>> faces, vector<Triangle> triangles, vector<Point> uv_points, Texture* texture) : Mesh(points, faces, triangles, uv_points, texture){}

ObjMesh::ObjMesh(vector<Point> points, vector<vector<int>> faces, vector<Triangle> triangles, vector<Point> uv_points, vector<Vector> normals, Texture* texture) : Mesh(points, faces, triangles, uv_points, normals, texture){}