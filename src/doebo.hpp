#pragma once

#include <glad/glad.h>
#include <glfw3.h>

class ElementBufferObject
{
public:
    ElementBufferObject();
    ~ElementBufferObject();
    void Create();
    void Bind();
    void Unbind();
    void BufferData(GLsizeiptr size, const void *data);
    // void SetAttribPointers();

private:
    unsigned int EBO;
};