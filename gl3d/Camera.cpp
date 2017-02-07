#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Input.h"
#include <GLFW/glfw3.h>
#include "Time.h"

Camera::Camera() {
}


Camera::~Camera() {
}

void Camera::update(GLFWwindow* window) {
    auto actualSpeed = speed * Time::delta();
    fprintf(stdout, "%f %f %f\n", actualSpeed, speed, Time::delta());
    view = glm::lookAt(position, position + front, up);
    if(Input::isPressed(window, GLFW_KEY_W)) { position += actualSpeed  * front; }
    if(Input::isPressed(window, GLFW_KEY_S)) { position -= actualSpeed  * front; }
    if(Input::isPressed(window, GLFW_KEY_A)) { position -= glm::normalize(glm::cross(front, up)) * actualSpeed; }
    if(Input::isPressed(window, GLFW_KEY_D)) { position += glm::normalize(glm::cross(front, up)) * actualSpeed; }
}
