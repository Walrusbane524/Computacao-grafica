#include <optional>

#include "../headers/canvas.h"

Canvas::Canvas(){
    rows = 0;
    columns = 0;
    matrix = nullptr;
}

Canvas::Canvas(int n_l, int n_c){
    rows = n_l;
    columns = n_c;
    matrix = new Color*[n_l];
    for (int i = 0; i < n_l; i++)
        matrix[i] = new Color[n_c];
}

Canvas::~Canvas() {
    if (matrix != nullptr) {
        for (int i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}
