#include "Sprite.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sprite::Sprite()
{
}

void Sprite::create(const std::string& texturePath, const glm::vec2& position)
{
    this->position = position;
    texture.load(texturePath);
    resolution = texture.getResolution();
    setVertices();
    createVao();
}

void Sprite::create(const std::string& texturePath, const glm::vec2& position, const glm::vec2& resolution)
{
    this->position = position;
    this->resolution = resolution;
    texture.load(texturePath);
    setVertices();
    createVao();
}

void Sprite::draw()
{
    glBindVertexArray(vao);
    texture.use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}


void Sprite::setVertices()
{
    vertices[0] = { position.x, position.y, 1.0f, 0.0f, 0.0f };
    vertices[1] = { position.x + resolution.x, position.y, 1.0f, 1.0f, 0.0f };
    vertices[2] = { position.x + resolution.x, position.y + resolution.y, 1.0f, 1.0f, 1.0f };
    vertices[3] = { position.x, position.y + resolution.y, 1.0f, 0.0f, 1.0f };
}

void Sprite::createVao()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}
