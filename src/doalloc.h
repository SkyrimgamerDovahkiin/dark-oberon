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
 *  @file utils.h
 *
 *  XXX
 *
 *  @author Marian Cerny
 *
 *  @date 2004
 */

#pragma once

#include "cfg.h"

// #if DEBUG_MEMORY

// #include "dologs.h"
// #include <glfw3.h>
// #include <crtdbg.h>
// #include <malloc.h>

// #define NEW new (__FILE__, __LINE__)

// //========================================================================
// // Operators
// //========================================================================

// void *operator new(size_t size);
// void *operator new(size_t size, const char *file, int line);
// void *operator new[](size_t size);
// void *operator new[](size_t size, const char *file, int line);

// void operator delete(void *p);
// void operator delete(void *p, const char * /*file*/, int /*line*/);
// void operator delete[](void *p);
// void operator delete[](void *p, const char * /*file*/, int /*line*/);

// //========================================================================
// // Methods
// //========================================================================

// void InitMemorySestem(void);
// void DoneMemorySystem(void);
// void SetAllocLogging(bool log);

// #else // DEBUG_MEMORY

#define NEW new

// #endif // !DEBUG_MEMORY

//========================================================================
// New operator for GUI
//========================================================================

#ifdef GUI_NEW
#undef GUI_NEW
#endif
#define GUI_NEW NEW

//=========================================================================
// END
//=========================================================================
// vim:ts=2:sw=2:et:
