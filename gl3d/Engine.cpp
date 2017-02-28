#include "Engine.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "Time.h"
#include "Input.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::run()
{
    init();
    loop();
    terminate();
}

void Engine::init()
{
    if(glfwInit() == GLFW_FALSE)
    {
        throw std::runtime_error("failed to initialize glfw!");
    }

    createWindow();
    createContext();

    sprite.create("textures/tentacool.png", glm::vec2(0.0f, 0.0f), glm::vec2(200.0f, 200.0f));
    baseShader.create("shaders/basic.vs", "shaders/basic.fs");

    orthoMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height);

    GLint numberOfAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numberOfAttributes);
    fprintf(stdout, "Maximum number of vertex attributes supported: %d\n", numberOfAttributes);
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}

void Engine::loop()
{
    while(!glfwWindowShouldClose(window))
    {
        Time::begin();
        Input::update();

#ifdef _DEBUG
        if(Input::isKeyPressed(GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window, true);
        }
#endif

        glClearColor(0.8f, 0.8f, 0.8f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.update();
        baseShader.use();

        GLuint projectionLocation = glGetUniformLocation(baseShader.getShaderId(), "projection");
        glm::mat4 cameraMatrix;
        cameraMatrix = glm::translate(orthoMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(cameraMatrix));

        sprite.draw();

        glfwSwapBuffers(window);

        Time::end();
    }
}

void Engine::terminate()
{
    glfwTerminate();
}

void Engine::createWindow()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(width, height, "gl3d", nullptr, nullptr);
    if(window == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("failed to create window!");
    }
    Input::init(window);
}

void Engine::createContext()
{
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    auto glewResult = glewInit();
    if(glewResult != GLEW_OK)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glewResult));
        throw std::runtime_error("failed to initialize glew!");
    }
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
