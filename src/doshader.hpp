#pragma once

#include <string>
#include <fstream>

#include <glad/glad.h>
#include <glfw3.h>

#include "dologs.h"

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    Shader();
    ~Shader();
    void Create(std::string vertFilename, std::string fragFilename);
    void Bind();
    void Unbind();
    void SetInt(const char *uniformLocation, int value);
    void SetMatrix4f(const char *uniformLocation, glm::mat4 mat);
    int GetUniform(const char *uniformLocation);

    // void BufferData(GLsizeiptr size, const void *data);
    // void SetAttribPointers();

private:
    unsigned int vertexShaderID;
    unsigned int fragmentShaderID;
    unsigned int shaderProgramID;
};