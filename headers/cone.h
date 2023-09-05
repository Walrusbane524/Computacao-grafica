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
        Cone(Point base_center, Point tip, double radius, Color color);
        Cone(Point base_center, Point tip, double radius, Color color, Vec roughness, Vec shine);
        Cone(Point base_center, Vector direction, double radius, double height, Color color);
        Cone(Point base_center, Vector direction, double radius, double height, Color color, Vec roughness, Vec shine);
    
    private:

        Vector get_normal(Point p) const override;
};

#endif