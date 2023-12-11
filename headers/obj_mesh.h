#pragma once
#include "mesh.h"
#include <vector>
#include <string>

using namespace std;

class ObjMesh : public Mesh{
    public:

        ObjMesh();
        ObjMesh(const string& filepath, Texture* texture_ptr, Material material);
        ObjMesh(vector<Point> points, vector<vector<int>> faces, vector<Triangle> triangles, vector<Point> uv_points, Material material, Texture* texture);
        ObjMesh(vector<Point> points, vector<vector<int>> faces, vector<Triangle> triangles, vector<Point> uv_points, vector<Vector> normals, Material material, Texture* texture);
};