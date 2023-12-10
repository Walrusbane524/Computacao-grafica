#ifndef CONE
#define CONE

#include "point.h"
#include "compound_object.h"

class Cone : public CompoundObject{
    public:

        Point base_center;
        Vector direction;
        double radius;
        double height;

        optional<LitPoint> colide(Ray ray) const override;

        Cone();
        Cone(Point base_center, Point tip, double radius);
        Cone(Point base_center, Point tip, double radius, Material material);
        Cone(Point base_center, Vector direction, double radius, double height);
        Cone(Point base_center, Vector direction, double radius, double height, Material material);

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

#endif