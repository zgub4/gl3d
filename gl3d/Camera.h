#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

struct GLFWwindow;

class Camera {
public:
    Camera();
    ~Camera();

    void update();
    glm::mat4 getView() const;

private:

    glm::vec3 calculateNewFront();

    glm::vec3 position{ 0.0f, 0.0f, 3.0f };
    glm::vec3 front{ 0.0f, 0.0f, -1.0f };
    glm::vec3 up{ 0.0f, 1.0f, 0.0f };
    const GLfloat cameraSpeed{ 0.5f };
    const GLfloat mouseSpeed{0.1f};

    glm::mat4 view;
    GLfloat yaw;
    GLfloat pitch;
};
