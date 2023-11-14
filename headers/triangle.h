#pragma once

#include <optional>
#include "plane.h"
#include "matrix.h"
#include "point.h"

class Triangle : public Object{
    public:
        Plane plane;
        Point p1;
        Point p2;
        Point p3;

        Triangle();
        Triangle(Vector normal, Point p1, Point p2, Point p3, Material material);
        Triangle(Point p1, Point p2, Point p3, Material material);
        virtual optional<LitPoint> colide(Ray ray) const override;

        void transform(Matrix matrix);

    private:
        Vector get_normal(Point p) const override;
};
