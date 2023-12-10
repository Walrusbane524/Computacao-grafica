#pragma once

#include "ray.h"
#include "color.h"
#include "lit_point.h"
#include "material.h"
#include "rotation_matrix_u_axis.h"
#include "rotation_matrix_x_axis.h"
#include "rotation_matrix_y_axis.h"
#include "rotation_matrix_z_axis.h"
#include "translation_matrix.h"
#include "scale_matrix.h"
#include <optional>
#include <string>
#include <iostream>

using namespace std;

class Object{
    public:

        Material material;

        virtual optional<LitPoint> colide(Ray ray) const = 0;
        
        virtual void info() = 0;
        virtual void translate() = 0;
        virtual void rotate() = 0;
        virtual void scale() = 0;
        virtual void translate(Matrix matrix) = 0;
        virtual void rotate(Matrix matrix) = 0;
        virtual void scale(Matrix matrix) = 0;
};