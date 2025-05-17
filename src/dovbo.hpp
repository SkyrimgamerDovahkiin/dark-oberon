#pragma once

#include <glad/glad.h>
#include <glfw3.h>

class VertexBufferObject
{
public:
    VertexBufferObject();
    ~VertexBufferObject();
    void Create();
    void Bind();
    void Unbind();

    void BufferData(GLsizeiptr size, const void *data);

    void SetAttribPointers();

private:
    unsigned int VBO;
};