#include "doebo.hpp"

ElementBufferObject::ElementBufferObject()
{
}

ElementBufferObject::~ElementBufferObject()
{
}

/**
 *  Creates the Element Buffer Object.
 */
void ElementBufferObject::Create()
{
    glGenBuffers(1, &EBO);
}

/**
 *  Binds the Element Buffer Object.
 */
void ElementBufferObject::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

/**
 *  Unbinds the Element Buffer Object.
 */
void ElementBufferObject::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/**
 *  Buffers data.
 *
 *  @param size      Size of the data to buffer.
 *  @param data      The data to Buffer.
 */
void ElementBufferObject::BufferData(GLsizeiptr size, const void *data)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

/**
 *  Sets the Attribute Pointers.
 */
// void ElementBufferObject::SetAttribPointers()
// {
//     // set vertex attribute pointers
//     // TODO: have attributes set via function arguments later
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
//     glEnableVertexAttribArray(0);
// }
