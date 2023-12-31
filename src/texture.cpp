#include "../headers/texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../headers/stb_image.h"
#include <iostream>

Texture::Texture(){}

Texture::Texture(const char* filePath) : Texture(){
    readFromFile(filePath);
    this->path = filePath;
}

void Texture::readFromFile(const char* filePath){
    this->path = filePath;
    int width, height, channels;
    unsigned char* data = stbi_load(filePath, &width, &height, &channels, 0);

    if (data) {
        image.resize(height, std::vector<Color>(width));

        // Assuming the texture has 3 channels (RGB)
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int index = (y * width + x) * 3;
                image[y][x] = Color(
                    data[index],      // Red
                    data[index + 1],  // Green
                    data[index + 2]   // Blue
                );
            }
        }

        this->width = width;
        this->height = height;
    } else {
        // Handle error loading texture
        // For example, print an error message or throw an exception
    }

    stbi_image_free(data);
}

Color Texture::sample(Point p){

    int x = abs(static_cast<int> (p.x * width) % width);
    int y = abs(static_cast<int> (p.y * height) % height);

    /*
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    cout << "Color:" << endl;
    cout << "r = " << image[y][x].r << endl;
    cout << "g = " << image[y][x].g << endl;
    cout << "b = " << image[y][x].b << endl;
    */

    return image[y][x];
}