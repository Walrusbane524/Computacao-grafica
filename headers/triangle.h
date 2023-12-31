#pragma once

#include <optional>
#include "plane.h"
#include "matrix.h"
#include "point.h"
#include "texture.h"

class Triangle : public Object{
    public:
        Plane plane;
        Point p1;
        Point p2;
        Point p3;
        vector<Point> uv_points;
        vector<Vector> normals;
        Texture* texture;

        Triangle();
        Triangle(Vector normal, Point p1, Point p2, Point p3, Material material, vector<Point> uv_points, Texture* texture);
        Triangle(Point p1, Point p2, Point p3, Material material, vector<Point> uv_points, Texture* texture);
        Triangle(Point p1, Point p2, Point p3, Material material, vector<Point> uv_points, vector<Vector> normals, Texture* texture);
        virtual optional<LitPoint> colide(Ray ray) const override;

        void info();

        void transform(Matrix matrix);

        void translate() override;
        void rotate() override;
        void scale() override;

        void translate(Matrix matrix) override;
        void rotate(Matrix matrix) override;
        void scale(Matrix matrix) override;

    private:
        Vector get_normal(Point p) const;
        Point get_uv(Point p) const;
};
