#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

struct GLFWwindow;

class Camera
{
public:
    Camera();
    ~Camera();

    void update(GLFWwindow* window);
    glm::mat4 getView() const { return view; }

private:
    glm::vec3 position{ 0.0f, 0.0f, 3.0f };
    glm::vec3 front{ 0.0f, 0.0f, -1.0f };
    glm::vec3 up{ 0.0f, 1.0f, 0.0f };
    const GLfloat speed{ 3.0f };

    glm::mat4 view;
};
