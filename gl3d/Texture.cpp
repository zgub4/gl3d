#include "Texture.h"

#include <SOIL.h>

Texture::Texture() {
}


Texture::~Texture() {
}

void Texture::load(const std::string& imagePath) {
    auto image = SOIL_load_image(imagePath.c_str(), &width, &height, nullptr, SOIL_LOAD_RGBA);
    if(image == nullptr) {
        fprintf(stderr, "failed to load image: %s", imagePath.c_str());
        return;
    }
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
}

void Texture::use() const {
    glBindTexture(GL_TEXTURE_2D, id);
}
