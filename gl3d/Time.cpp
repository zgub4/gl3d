#include "Time.h"
#include <GLFW/glfw3.h>

float Time::deltaTime = 0.0f;
float Time::frameTime = 0.0f;

void Time::begin()
{
    frameTime = glfwGetTime();
}

void Time::end()
{
    deltaTime = glfwGetTime() - deltaTime;
}

float Time::delta()
{
    return deltaTime / 1000.0f;
}
