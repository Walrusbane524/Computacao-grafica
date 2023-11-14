#pragma once
#include "triangle.h"
#include <vector>

class Mesh : public Object{
    public:
        vector<Point> points;
        vector<vector<int>> faces;
        vector<Triangle> triangles;

        Mesh();
        Mesh(vector<Point> points, vector<vector<int>> faces);

        virtual optional<LitPoint> colide(Ray ray) const override;

        Mesh addVertex(double x, double y, double z);
        Mesh addTriangle(vector<int> indices);

        void transform(Matrix matrix);

    private:

        Vector get_normal(Point p) const override;
};