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
        ConicalFace(Point base_center, Point tip, double radius);
        ConicalFace(Point base_center, Point tip, double radius, Material material);
        ConicalFace(Point base_center, Vector direction, double radius, double height);
        ConicalFace(Point base_center, Vector direction, double radius, double height, Material material);
    
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