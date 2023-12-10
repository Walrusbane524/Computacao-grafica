#pragma once

#include "object.h"

class CylindricalFace : public Object{
    public:
        Point base_center;
        Vector direction;
        double radius;
        double height;

        CylindricalFace();
        CylindricalFace(Point center, Vector direction, double radius, double height);
        CylindricalFace(Point center, Vector direction, double radius, double height, Material material);

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
