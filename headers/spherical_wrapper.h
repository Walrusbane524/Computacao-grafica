#pragma once
#include "object.h"
#include "sphere.h"
#include "obj_mesh.h"
#include <vector>

class SphericalWrapper : public Object{
    public:
        Sphere sphere;
        vector<Object*> objects;
        ObjMesh* mesh;
        int depth;

        SphericalWrapper();
        SphericalWrapper(ObjMesh* mesh, int depth);
        SphericalWrapper(Sphere sphere, vector<Object*> objects);

        static bool compareTriangles(const Triangle& a, const Triangle& b);
        static Point averagePoint(const Triangle& triangle);

        optional<LitPoint> colide(Ray ray) const override;

        void info();
        void transform(Matrix matrix);
        
        void translate() override;
        void rotate() override;
        void scale() override;

        void translate(Matrix matrix) override;
        void rotate(Matrix matrix) override;
        void scale(Matrix matrix) override;
};