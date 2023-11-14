#pragma once
#include "triangle.h"
#include "textured_object.h"
#include <string>
#include <vector>

using namespace std;

class TexturedTriangle : public Triangle, TexturedObject{
    public:

        TexturedTriangle(vector<Point> uv_points, Texture* texture_pointer);
        TexturedTriangle(Vector normal, Point p1, Point p2, Point p3, Material material, vector<Point> uv_points, Texture* texture_pointer);
        TexturedTriangle(Triangle triangle, vector<Point> uv_points, Texture* texture_pointer);
        TexturedTriangle(Point p1, Point p2, Point p3, Material material, vector<Point> uv_points, Texture* texture_pointer);

        virtual optional<LitPoint> colide(Ray ray) const override;

    private:
        Point get_uv(Point p) const override;
};