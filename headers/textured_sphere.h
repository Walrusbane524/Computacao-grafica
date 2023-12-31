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
    
    void translate() override;
    void rotate() override;
    void scale() override;

    void translate(Matrix matrix) override;
    void rotate(Matrix matrix) override;
    void scale(Matrix matrix) override;

    private:
    
    Color calculate_color(Point p) const;
};