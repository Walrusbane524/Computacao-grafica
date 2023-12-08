#pragma once
#include "plane.h"
#include "texture.h"

class TexturedPlane : public Object{
    public:
    Plane plane;
    Texture* texture;
    Vector vx;
    Vector vy;

    TexturedPlane(Plane plane, Vector vector, Texture* texture);

    optional<LitPoint> colide(Ray ray) const override;

    void info() override;

    private:
    
    Color calculate_color(Point p) const;
};