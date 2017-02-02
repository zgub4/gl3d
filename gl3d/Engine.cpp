#include "Engine.h"

#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

GLfloat vertices[] {
    // Position         // Color            // Texture coords
    .5f, .5f, 0.f,      1.f, 0.f, 0.f,      1.f, 1.f, // Top right
    .5f, -.5f, 0.f,     0.f, 1.f, 0.f,      1.f, 0.f, // Bot right
    -.5f, -.5f, 0.f,    0.f, 0.f, 1.f,      0.f, 0.f, // Bot left
    -.5f, .5f, 0.f,     1.f, 1.f, 0.f,      0.f, 1.f // Top left
};

GLuint indices[]{
    0, 1, 3,
    1, 2, 3
};

Engine::Engine() {}

Engine::~Engine() {
    terminate();
}

void Engine::run() {
    init();
    loop();
    terminate();
}

void Engine::init() {
    if(glfwInit() == GLFW_FALSE) {
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast <GLvoid*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast <GLvoid*>(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    texture.load("textures/tentacool.png");

    baseShader.create("shaders/basic.vs", "shaders/basic.fs");

    GLint numberOfAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numberOfAttributes);
    fprintf(stdout, "Maximum number of vertex attributes supported: %d\n", numberOfAttributes);
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}

void Engine::loop() {
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.8f, 0.8f, 0.8f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        baseShader.use();
        
        texture.use();

        glm::mat4 transRotate;
        transRotate = glm::translate(transRotate, glm::vec3(0.5f, -0.5f, 0.0f));
        transRotate = glm::rotate(transRotate, GLfloat(glfwGetTime()) * glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        GLuint transformLocation = glGetUniformLocation(baseShader.getShaderId(), "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transRotate));

        glm::mat4 transScale;
        transScale = glm::translate(transScale, glm::vec3(-0.5f, 0.5f, 0.0f));
        GLfloat scaleFactor = (std::sin(glfwGetTime()) / 2.0f) + 0.5f;
        transScale = glm::scale(transScale, glm::vec3(scaleFactor, scaleFactor, 1.0f));
        
        glBindVertexArray(vao);
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transRotate));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transScale));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }
}

void Engine::terminate() {
    glfwTerminate();
}

void Engine::createWindow() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(width, height, "gl3d", nullptr, nullptr);
    if(window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("failed to create window!");
    }
}

void Engine::createContext() {
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    glewExperimental = GL_TRUE;
    auto glewResult = glewInit();
    if(glewResult != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glewResult));
        throw std::runtime_error("failed to initialize glew!");
    }
    glViewport(0, 0, width, height);
}