#include <optional>
#include <iostream>

#include "../headers/canvas.h"

using std::cout;
using std::endl;
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
/*
Canvas::~Canvas() {
    cout << "Desconstruindo Canva" << endl;
    if (matrix != nullptr) {
        for (int i = 0; i < rows; ++i) {
            if(matrix[i] != nullptr)
                delete[] matrix[i];
        }
        cout << "Desconstruindo Canva2" << endl;
        delete[] matrix;
    }
}
*/

void Canvas::resize(int width, int height){
    if(this->matrix != nullptr){
        for (int i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    this->rows = height;
    this->columns = width;
    matrix = new Color*[height];
    for (int i = 0; i < height; i++)
        matrix[i] = new Color[width];
}
