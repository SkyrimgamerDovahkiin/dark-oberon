/*
 * -------------
 *  Dark Oberon
 * -------------
 *
 * An advanced strategy game.
 *
 * Copyright (C) 2002 - 2005 Valeria Sventova, Jiri Krejsa, Peter Knut,
 *                           Martin Kosalko, Marian Cerny, Michal Kral
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License (see docs/gpl.txt) as
 * published by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 */

/**
 *  @file dodraw.h
 *
 *  Vertex Array Object declarations and methods.
 *
 *  @author Fabian Rubin
 *
 *  @date 2025
 */

#pragma once

//=========================================================================
// Included files
//=========================================================================

#include <glad/glad.h>
#include <glfw3.h>

//=========================================================================
// Classes
//=========================================================================

class VertexArrayObject
{
public:
    VertexArrayObject();
    ~VertexArrayObject();
    void Create();
    void Bind();
    void Unbind();

private:
    unsigned int VAO;
};