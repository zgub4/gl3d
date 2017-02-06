#pragma once

#include <vector>

struct GLFWwindow;

class Input
{
public:
    Input();
    ~Input();

//    void init(GLFWwindow* window);
    static bool isPressed(GLFWwindow* window, int key);

//private:
//    GLFWwindow* window;
};

