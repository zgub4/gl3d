#include "Input.h"
#include <GLFW/glfw3.h>

GLFWwindow* Input::window = nullptr;
glm::vec2 Input::currentPosition {0.0f, 0.0f};
glm::vec2 Input::lastPosition {0.0f, 0.0f};

void Input::init(GLFWwindow* window)
{
    Input::window = window;
}

void Input::update()
{
    glfwPollEvents();
    updateMousePosition();
}

bool Input::isKeyPressed(int key)
{
    return glfwGetKey(window, key);
}

glm::vec2 Input::getMouseDelta()
{
    glm::vec2 delta(currentPosition.x - lastPosition.x, lastPosition.y - currentPosition.y);
    lastPosition = currentPosition;
    return delta;
}

void Input::updateMousePosition()
{
    static double x, y;
    glfwGetCursorPos(window, &x, &y);
    currentPosition = glm::vec2(x, y);
}
