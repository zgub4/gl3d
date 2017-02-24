#pragma once

#include <GL/glew.h>

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

struct GLFWwindow;

class Engine
{
public:
    Engine();
    ~Engine();

    void run();

private:
    void init();
    void loop();
    void terminate();

    void createWindow();
    void createContext();

    GLFWwindow* window = nullptr;
    const GLsizei width = 800;
    const GLsizei height = 600;
    GLuint vao;
    Texture texture;
    Shader baseShader;
    Camera camera;
};
