#ifndef CANVAS
#define CANVAS

#include "color.h"

class Canvas{
    public:
        Color** matrix;
        int rows;
        int columns;

        Canvas();
        
        Canvas(int n_l, int n_c);

        //~Canvas();

        void resize(int width, int height);
};

#endif