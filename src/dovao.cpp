#include "dovao.hpp"

VertexArrayObject::VertexArrayObject()
{
}

VertexArrayObject::~VertexArrayObject()
{
}

/**
 *  Creates the Vertex Array Object.
 */
void VertexArrayObject::Create()
{
    glGenVertexArrays(1, &VAO);
}

/**
 *  Binds the Vertex Array Object.
 */
void VertexArrayObject::Bind()
{
    glBindVertexArray(VAO);
}

/**
 *  Unbinds the Vertex Array Object.
 */
void VertexArrayObject::Unbind()
{
    glBindVertexArray(0);
}