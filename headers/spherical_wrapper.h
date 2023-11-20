#pragma once
#include "object.h"
#include "sphere.h"
#include "obj_mesh.h"
#include <vector>

class SphericalWrapper : public Object{
    public:
        Sphere sphere;
        vector<Object*> objects;

        SphericalWrapper();
        SphericalWrapper(ObjMesh* mesh, int depth);
        SphericalWrapper(Sphere sphere, vector<Object*> objects);

        optional<LitPoint> colide(Ray ray) const override;
};