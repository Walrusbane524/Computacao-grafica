#pragma once
#include "obj_mesh.h"
#include "textured_object.h"

class TexturedMesh : public ObjMesh, TexturedObject{
    public:

        TexturedMesh(const char* obj_path, const char* texture_path);

        Mesh addTexturedTriangle(vector<int> indexes, vector<int> uv_indexes);
        Mesh addUVPoints(double u, double v, double w);
        Point get_uv(Point p) const override;

        virtual optional<LitPoint> colide(Ray ray) const override;
};