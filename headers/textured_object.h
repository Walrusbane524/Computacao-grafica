#pragma once
#include "point.h"
#include "texture.h"
#include <vector>

using namespace std;

class TexturedObject{
    public:
        vector<Point> uv_points;
        Texture* texture;

    private:
        virtual Point get_uv(Point p) const = 0;
};