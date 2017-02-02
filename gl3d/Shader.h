#pragma once

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>

class Shader
{
public:
    Shader();
    ~Shader();

    void create(const std::string& vertexSourcePath, const std::string& fragmentSourcePath);
    void use() const;
    GLuint getShaderId() const { return programId; }

private:
    GLuint programId;
};

