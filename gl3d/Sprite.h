#pragma once

#include <glm/glm.hpp>
#include <string>
#include <array>
#include "Texture.h"
#include "Shader.h"

class Sprite
{
public:
    Sprite();

    void create(const std::string& texturePath, const glm::vec2& position);
    void create(const std::string& texturePath, const glm::vec2& position, const glm::vec2& resolution);
    void draw();

private:
    void setVertices();
    void createVao();

    Texture texture;
    GLuint vao;
    glm::vec2 position{ 0.0f, 0.0f };
    glm::vec2 resolution{ 0.0f, 0.0f };
    std::array <std::array <float, 5>, 4> vertices;
    const int indices[6]{ 0, 1, 3, 1, 2, 3 };
};
