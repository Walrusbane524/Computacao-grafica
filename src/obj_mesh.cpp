#include "../headers/obj_mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>

ObjMesh::ObjMesh() : Mesh(){}

ObjMesh::ObjMesh(const string& filepath){
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
        } else if (type == "f") {
            string vertex;
            vector<int> faceIndices;

            while (iss >> vertex) {
                size_t pos = vertex.find('/');
                if (pos != string::npos) {
                    vertex = vertex.substr(0, pos); // Extract characters before '/'
                }
                int index = stoi(vertex); // Convert to integer and adjust to be 0-based

                index = (index > 0) ? index - 1 : this->points.size() + index;
 
                faceIndices.push_back(index);
            }
            /*
            cout << "points.size() = " << this->points.size() << endl;
            cout << "Face indices: ";
            for (int index : faceIndices) {
                cout << index << " ";
            }
            cout << endl;
            */

            this->addTriangle(faceIndices);

            if(faceIndices.size() > 3){
                vector<int> face2Indexes = {faceIndices[0], faceIndices[2], faceIndices[3]};
                this->addTriangle(face2Indexes);
            }
        }
    }

    file.close();
}