#include "Engine.h"

#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "Time.h"
#include "Input.h"

GLfloat vertices[] {
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
};

GLuint indices[] {
    0, 1, 3,
    1, 2, 3
};

Engine::Engine()
{
}

Engine::~Engine()
{
    terminate();
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

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast <GLvoid*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    texture.load("textures/tentacool.png");

    baseShader.create("shaders/basic.vs", "shaders/basic.fs");

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

        texture.use();

        GLfloat lightning = (glm::sin(glfwGetTime()) + 1) / 2;
        GLuint lightningLocation = glGetUniformLocation(baseShader.getShaderId(), "lightning");

        glBindVertexArray(vao);
        
        glUniform1f(lightningLocation, lightning);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        glBindVertexArray(0);

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
