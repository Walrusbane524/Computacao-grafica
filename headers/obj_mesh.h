#pragma once
#include "mesh.h"
#include <vector>
#include <string>

using namespace std;

class ObjMesh : public Mesh{
    public:

        ObjMesh();
        ObjMesh(const string& filepath, Texture* texture_ptr);
};