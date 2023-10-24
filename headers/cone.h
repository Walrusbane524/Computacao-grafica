#ifndef CONE
#define CONE

#include "point.h"
#include "compound_object.h"

class Cone : public CompoundObject{
    public:

        Point base_center;
        double radius;

        optional<LitPoint> colide(Ray ray) const override;

        Cone();
        Cone(Point base_center, Point tip, double radius);
        Cone(Point base_center, Point tip, double radius, Material material);
        Cone(Point base_center, Vector direction, double radius, double height);
        Cone(Point base_center, Vector direction, double radius, double height, Material material);
    
    private:

        Vector get_normal(Point p) const override;
};

#endif