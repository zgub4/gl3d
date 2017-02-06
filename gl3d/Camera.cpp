#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Input.h"
#include <GLFW/glfw3.h>

Camera::Camera() {
}


Camera::~Camera() {
}

void Camera::update(GLFWwindow* window) {
    view = glm::lookAt(position, position + front, up);
    if(Input::isPressed(window, GLFW_KEY_W)) { position += speed * front; }
    if(Input::isPressed(window, GLFW_KEY_S)) { position -= speed * front; }
    if(Input::isPressed(window, GLFW_KEY_A)) { position -= glm::normalize(glm::cross(front, up)) * speed; }
    if(Input::isPressed(window, GLFW_KEY_D)) { position += glm::normalize(glm::cross(front, up)) * speed; }
}
