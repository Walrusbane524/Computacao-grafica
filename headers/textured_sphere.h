#pragma once
#include "texture.h"
#include "sphere.h"
#include "matrix.h"

class TexturedSphere : public Object{
    public:

    Sphere sphere;
    Texture* texture;
    Matrix* rotation_matrix;


    TexturedSphere(Sphere shere, Texture* texture);

    optional<LitPoint> colide(Ray ray) const override;

    void info() override;

    private:
    
    Color calculate_color(Point p) const;
};