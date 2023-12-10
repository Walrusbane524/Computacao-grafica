#pragma once
#include <optional>
#include "point.h"
#include "color.h"
#include "object.h"
#include "ray.h"

class Sphere : public Object{
    public:
        Point center;
        double radius;

        Sphere();
        Sphere(Point center, double radius);
        Sphere(Point center, double radius, Material material);
        optional<LitPoint> colide(Ray ray) const override;
        void transform(Matrix transformation_matrix);

        void info() override;
        void translate() override;
        void rotate() override;
        void scale() override;

    private:
        Vector get_normal(Point p) const;
};
