#pragma once
#include "plane.h"
#include "texture.h"

class TexturedPlane : public Object{
    public:
    Plane plane;
    Texture* texture;
    Vector vx;
    Vector vy;
    double scale_factor;

    TexturedPlane(Plane plane, Vector vector, Texture* texture, double scale_factor);

    optional<LitPoint> colide(Ray ray) const override;

    void info() override;
    void translate() override;
    void rotate() override;
    void scale() override;

    private:
    
    Color calculate_color(Point p) const;
};