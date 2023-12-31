#pragma once

#include <optional>
#include "point.h"
#include "color.h"
#include "object.h"
#include "ray.h"

class Plane : public Object{
    public:
        Point center;
        Vector normal;

        Plane();
        Plane(Point center, Vector normal);
        Plane(Point center, Vector normal, Material material);
        optional<LitPoint> colide(Ray ray) const override;

        void info() override;
        
        void translate() override;
        void rotate() override;
        void scale() override;

        void translate(Matrix matrix) override;
        void rotate(Matrix matrix) override;
        void scale(Matrix matrix) override;

    private:
        Vector get_normal(Point p) const;
};
