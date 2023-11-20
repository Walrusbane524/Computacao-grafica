#pragma once
#include "triangle.h"
#include "texture.h"
#include <vector>

class Mesh : public Object{
    public:
        vector<Point> points;
        vector<vector<int>> faces;
        vector<Triangle> triangles;
        vector<Point> uv_points;
        Texture* texture;

        Mesh();
        Mesh(vector<Point> points, vector<vector<int>> faces);
        Mesh(vector<Point> points, vector<vector<int>> faces, vector<Triangle> triangles, vector<Point> uv_points, Texture* texture);

        virtual optional<LitPoint> colide(Ray ray) const override;

        Mesh addVertex(double x, double y, double z);
        Mesh addTriangle(vector<int> indexes, vector<int> uv_indexes);
        Mesh addUVPoints(double u, double v, double w);

        Mesh transform(Matrix matrix);

    private:

        Vector get_normal(Point p) const;
};