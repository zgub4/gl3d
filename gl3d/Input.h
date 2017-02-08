#pragma once

#include <vector>
#include <glm/glm.hpp>

struct GLFWwindow;

class Input
{
public:

    static void init(GLFWwindow* window);
    static void update();

    static bool isKeyPressed(int key);
    static glm::vec2 getMouseDelta();

private:
    static void updateMousePosition();

    static glm::vec2 currentPosition;
    static glm::vec2 lastPosition;
    static GLFWwindow* window;

    Input() = delete;
    Input(Input const&) = delete;
    void operator=(Input const&) = delete;
};
