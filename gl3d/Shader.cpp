#include "Shader.h"

#include <stdexcept>
#include <iostream>
#include <vector>

Shader::Shader() {
    
}

Shader::~Shader() {
}

void Shader::create(const std::string& vertexSourcePath, const std::string& fragmentSourcePath) {
    std::ifstream vertexShaderFile(vertexSourcePath);
    std::ifstream fragmentShaderFile(fragmentSourcePath);
    if(vertexShaderFile.fail() || fragmentShaderFile.fail()) {
        fprintf(stderr, "failed to open shaders file!\n");
        throw std::runtime_error("failed to open shaders file!");
    }
    std::stringstream vertexStream, fragmentStream;
    vertexStream << vertexShaderFile.rdbuf();
    fragmentStream << fragmentShaderFile.rdbuf();
    std::string vertexCodeString = vertexStream.str();
    std::string fragmentCodeString = fragmentStream.str();

    auto vertexCode = vertexCodeString.c_str();
    auto fragmentCode = fragmentCodeString.c_str();

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE) {
        GLint length = 0;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
        std::vector<GLchar> errorLog(length);
        glGetShaderInfoLog(vertex, length, &length, &errorLog[0]);
        fprintf(stderr, &errorLog[0]);
        glDeleteShader(vertex);
        throw std::runtime_error("failed to compile vertex shader!");
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE) {
        GLint length = 0;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
        std::vector<GLchar> errorLog(length);
        glGetShaderInfoLog(fragment, length, &length, &errorLog[0]);
        fprintf(stderr, &errorLog[0]);
        glDeleteShader(fragment);
        throw std::runtime_error("failed to compile fragment shader!");
    }

    programId = glCreateProgram();
    glAttachShader(programId, vertex);
    glAttachShader(programId, fragment);
    glLinkProgram(programId);
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if(success == GL_FALSE) {
        GLint length = 0;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
        std::vector<GLchar> errorLog(length);
        glGetShaderInfoLog(fragment, length, &length, &errorLog[0]);
        fprintf(stderr, &errorLog[0]);

        glDeleteProgram(programId);
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        throw std::runtime_error("failed to link shaders!");
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() const {
    glUseProgram(programId);
}
