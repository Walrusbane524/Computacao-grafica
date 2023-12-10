#pragma once

#include "compound_object.h"

class Cylinder : public CompoundObject{
    public:

        Point base_center;
        Point top_center;
        double radius;

        optional<LitPoint> colide(Ray ray) const override;

        Cylinder(Point base_center, Point top_center, double radius);
        Cylinder(Point base_center, Point top_center, double radius, Material material);
        Cylinder(Point base_center, Vector direction, double radius, double height);
        Cylinder(Point base_center, Vector direction, double radius, double height, Material material);
    
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
