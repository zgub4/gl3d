#include "Input.h"

#include <algorithm>
#include <iostream>
#include <GLFW/glfw3.h>

Input::Input() {
}


Input::~Input() {
}

bool Input::isPressed(GLFWwindow* window, int key) {
    return glfwGetKey(window, key);
}
