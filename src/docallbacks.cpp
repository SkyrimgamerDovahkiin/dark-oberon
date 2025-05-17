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
 *  @file docallbacks.cpp
 *
 *  contains the GLFW callbacks for now, later they should be in the engine
 *
 *  @author Fabian Rubin
 *
 *  @date 2025
 */

#include "docallbacks.h"

//========================================================================
// GLFW Size Callback
//========================================================================

/**
 *  GLFW window size callback function. This function is called by GLFW every
 *  time the window size is changed.
 *
 *  @param w New width of the window.
 *  @param h New height of the window.
 */
void SizeCallback(GLFWwindow *window, int w, int h)
{
    //   config.scr_width = w;
    //   config.scr_height = h;

    glViewport(0, 0, w, h);

    // TODO: find out what that is
    //   glfSetFontDisplayMode(font0, w, h);
}

//========================================================================
// GLFW Key Callback
//========================================================================

/**
 *  GLFW key callback function. This function is called every time a key is
 *  pressed or released.
 *
 *  @param key    A key identifier (uppercase ASCII or a special key
 *                identifier).
 *  @param action Either GLWF_PRESS or GLFW_RELEASE.
 */
void KeyCallback(int key, int scancode, int action, int mods)
{

    // if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    // {
    //     // TODO: quit
    //     glfwSetWindowShouldClose(window, GLFW_TRUE);
    // }

    // switch (action)
    // {
    // case GLFW_PRESS:
    // {
    //     KeyPressedEvent event(key);
    //     data.EventCallback(event);
    //     break;
    // }
    // case GLFW_RELEASE:
    // {
    //     // TODO: release event
    //     break;
    // }
    // case GLFW_REPEAT:
    // {
    //     // TODO: repeat event (if needed at all)
    //     break;
    // }
    // }

    // if (key == GLFW_KEY_M && action == GLFW_PRESS)
    // {
    //     // TODO: mute music
    // }
    //   need_redraw->SetTrue ();

    //   switch (state) {
    //   case ST_MAIN_MENU:
    //   case ST_VIDEO_MENU:
    //   case ST_PLAY_MENU:
    //     if (action == GLFW_PRESS) MenuOnKeyDown(key);
    //     break;

    //   case ST_GAME:
    //     if (action == GLFW_PRESS) GameOnKeyDown(key);
    //     else GameOnKeyUp(key);
    //     break;

    //   case ST_QUIT:
    //   default:
    //     break;
    //   }
    // TODO: define custom stuff that should happen here
}

//========================================================================
// GLFW Mouse Callbacks
//========================================================================

/**
 *  GLFW mouse button callback function. This function is called every time a
 *  mouse button is pressed or released.
 *
 *  @param button  A mouse button identifier (one of
 *                 GLFW_MOUSE_BUTTON_{LEFT|MIDDLE|RIGHT}).
 *  @param action  Either GLFW_PRESS or GLFW_RELEASE.
 */
void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    // TODO: define custom stuff here

    // need_redraw->SetTrue();

    // if (action == GLFW_PRESS)
    // {
    //     gui->MouseDown(GLfloat(mouse.x), GLfloat(mouse.y), button);
    // }
    // else
    // {
    //     gui->MouseUp(GLfloat(mouse.x), GLfloat(mouse.y), button);
    // }
}

/**
 *  GLFW mouse position callback function. This function is called every time a
 *  mouse has changed position.
 *
 *  @param x  X coordinate.
 *  @param y  Y coordinate.
 */
void MousePosCallback(GLFWwindow *window, double x, double y)
{
    //   need_redraw->SetTrue ();

    //   y = config.scr_height - y;

    //   int dx = x - mouse.rx;
    //   int dy = y - mouse.ry;

    //   if (state == ST_GAME && map.mouse_moving)
    //   {
    //     map.Move(-dx * projection.game_h_coef, -dy * projection.game_v_coef);
    //   }
    //   else {
    //     int last_x = mouse.x;
    //     int last_y = mouse.y;

    //     mouse.x += dx;
    //     mouse.y += dy;
    //     if (mouse.x < 0) mouse.x = 0;
    //     if (mouse.y < 0) mouse.y = 0;
    //     if (mouse.x >= config.scr_width) mouse.x = config.scr_width - 1;
    //     if (mouse.y >= config.scr_height) mouse.y = config.scr_height - 1;

    //     if (state == ST_GAME && map.drag_moving) {
    //       map.Move((mouse.x - last_x) * projection.game_h_coef, (mouse.y - last_y) * projection.game_v_coef);
    //     }
    //   }

    //   mouse.rx = x;
    //   mouse.ry = y;

    //   gui->MouseMove(GLfloat(mouse.x), GLfloat(mouse.y));

    // TODO: define custom stuff here
}

/**
 *  GLFW mouse wheel callback function. This function is called every time a
 *  mouse wheel changes position.
 *
 *  @param pos Actual wheel position.
 */
void MouseWheelCallback(GLFWwindow *window, double xoffset, double yoffset)
{
    //   need_redraw->SetTrue ();

    //   static int last_pos;

    //   switch (state) {
    //   case ST_GAME:
    //     map.Zoom(pos - last_pos);

    //   default: break;
    //   }

    //   last_pos = pos;

    // TODO: define custom stuff here
}

/**
 *  GLFW window refresh callback function. This function is called every time
 *  part of the window client area needs to be repainted - for instance when
 *  another window lying on top of our window has changed its position.
 */
void WindowRefreshCallback(GLFWwindow *window)
{
    //   need_redraw->SetTrue ();
    // TODO: define custom stuff here
}

/**
 *  GLFW framebuffer size callback function. This function sets the framebuffer
 *  resize callback of the specified window, which is called when the framebuffer
 *  of the specified window is resized.
 */
void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void SetCallbacks(GLFWwindow *window)
{
    glfwSetWindowSizeCallback(window, SizeCallback);
    // glfwSetKeyCallback(window, KeyCallback);

    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
                       {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action)
        {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(key, 0);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
              // TODO: release event
                break;
            }
            case GLFW_REPEAT:
            {
                // TODO: repeat event (if needed at all)
                KeyPressedEvent event(key, 1);
                data.EventCallback(event);
                break;
            }
        } });

    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, MousePosCallback);
    // glfwSetScrollCallback(window, MouseWheelCallback);

    glfwSetScrollCallback(window, [](GLFWwindow *window, double xOffset, double yOffset)
                          {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallback(event); });

    glfwSetWindowRefreshCallback(window, WindowRefreshCallback);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
}
