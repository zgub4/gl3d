#pragma once

#include <GL/glew.h>

#include <string>

class Texture
{
public:
    Texture();
    ~Texture();

    void load(const std::string& imagePath);
    void use() const;

private:
    GLuint id;
    int width;
    int height;
};

