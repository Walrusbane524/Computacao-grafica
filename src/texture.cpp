#include "../headers/texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../headers/stb_image.h"

Texture::Texture(){}

Texture::Texture(const char* filePath) : Texture(){
    readFromFile(filePath);
}

void Texture::readFromFile(const char* filePath){
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

    int x = static_cast<int> (p.x * width) % width; 
    int y = static_cast<int> (p.y * height) % height;

    return image[y][x];
}