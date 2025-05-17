#include "dotexture.hpp"

Texture::Texture()
{
}

/**
 *  The Destructor also deletes the Texture.
 */
Texture::~Texture()
{
    glDeleteTextures(1, &texID);
}

/**
 *  Creates the Texture.
 *  @param filename  the filename of the texture
 */
void Texture::Create(char* filename)
{
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    // set the texture wrapping parameters
    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);

    if (data)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        Error("Failed to load texture!");
    }
    stbi_image_free(data);
}

/**
 *  Binds the Texture.
 *  @param textureSlot  which texture slot the texture should be bound to. Default = 0
 */
void Texture::Bind(int textureSlot)
{
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, texID);
}

/**
 *  Unbinds the Texture.
 */
void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    // glDeleteTextures(1, &texID);
}