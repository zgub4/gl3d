#pragma once

#include <GL/glew.h>

#include <string>
#include <glm/glm.hpp>

class Texture
{
public:
    Texture();
    ~Texture();

    void load(const std::string& imagePath);
    void use() const;
    glm::vec2 getResolution() const;

private:
    GLuint id;
    int width;
    int height;
};
