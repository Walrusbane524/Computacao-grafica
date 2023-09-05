#ifndef CONICAL_FACE
#define CONICAL_FACE

#include "object.h"

class ConicalFace : public Object{
    public:

        Point base_center;
        Point tip;
        Vector direction;
        double radius;
        double height;

        virtual optional<LitPoint> colide(Ray ray) const override;

        ConicalFace();
        ConicalFace(Point base_center, Point tip, double radius, Color color);
        ConicalFace(Point base_center, Point tip, double radius, Color color, Vec roughness, Vec shine);
        ConicalFace(Point base_center, Vector direction, double radius, double height, Color color);
        ConicalFace(Point base_center, Vector direction, double radius, double height, Color color, Vec roughness, Vec shine);
    
    private:
        Vector get_normal(Point p) const override;
};

#endif