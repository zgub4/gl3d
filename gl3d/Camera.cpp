#include "Camera.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Input.h"
#include "Time.h"

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::update()
{
    auto actualSpeed = cameraSpeed * Time::delta();
    front = calculateNewFront();
    view = glm::lookAt(position, position + front, up);
    if(Input::isKeyPressed(GLFW_KEY_W)) { position += actualSpeed * front; }
    if(Input::isKeyPressed(GLFW_KEY_S)) { position -= actualSpeed * front; }
    if(Input::isKeyPressed(GLFW_KEY_A)) { position -= glm::normalize(glm::cross(front, up)) * actualSpeed; }
    if(Input::isKeyPressed(GLFW_KEY_D)) { position += glm::normalize(glm::cross(front, up)) * actualSpeed; }
}

glm::mat4 Camera::getView() const
{
    return view;
}

glm::vec3 Camera::calculateNewFront()
{
    auto euler = Input::getMouseDelta();
    yaw += euler.x * mouseSpeed;
    yaw = glm::mod(yaw, 360.0f);
    pitch += euler.y * mouseSpeed;

    if(pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    if(pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    glm::vec3 front;
    front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    front.y = glm::sin(glm::radians(pitch));
    front.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    return glm::normalize(front);
}
