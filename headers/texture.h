#pragma once
#include <vector>
#include <string>
#include "color.h"
#include "point.h"

using namespace std;

class Texture{
    public:
        vector<vector<Color>> image;
        int width;
        int height;
        string path;

        Texture();
        Texture(const char* filePath);

        void readFromFile(const char* filePath);
        Color sample(Point p);
};