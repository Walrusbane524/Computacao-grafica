#include "../headers/translation_matrix.h"

TranslationMatrix::TranslationMatrix() : Matrix(){}

TranslationMatrix::TranslationMatrix(double** matrix) : Matrix(matrix){}

TranslationMatrix::TranslationMatrix(Vector v){
    this->matrix = new double* [4] {
        new double[4] {1, 0, 0, v.x},
        new double[4] {0, 1, 0, v.y},
        new double[4] {0, 0, 1, v.z},
        new double[4] {0, 0, 0,  1 }
    };
}