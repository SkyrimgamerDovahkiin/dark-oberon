#include "dovbo.hpp"

VertexBufferObject::VertexBufferObject()
{
}

VertexBufferObject::~VertexBufferObject()
{
}

/**
 *  Creates the Vertex Buffer Object.
 */
void VertexBufferObject::Create()
{
    glGenBuffers(1, &VBO);
}

/**
 *  Binds the Vertex Buffer Object.
 */
void VertexBufferObject::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

/**
 *  Unbinds the Vertex Buffer Object.
 */
void VertexBufferObject::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/**
 *  Buffers data.
 *
 *  @param size      Size of the data to buffer.
 *  @param data      The data to Buffer.
 */
void VertexBufferObject::BufferData(GLsizeiptr size, const void *data)
{
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

/**
 *  Sets the Attribute Pointers.
 */
void VertexBufferObject::SetAttribPointers()
{
    // set vertex attribute pointers
    // TODO: have attributes set via function arguments later

    // positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}
