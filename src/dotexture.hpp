#pragma once

#include <glad/glad.h>
#include <glfw3.h>

// stb_image
#include "stb_image.h"

#include "dologs.h"

class Texture
{
public:
    Texture();
    ~Texture();
    void Create(char* filename);
    void Bind(int textureSlot = 0);
    void Unbind();
private:
    unsigned int texID;
};