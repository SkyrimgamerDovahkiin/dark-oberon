/*
 * -------------
 *  Dark Oberon
 * -------------
 *
 * An advanced strategy game.
 *
 * Original Copyright (C) 2002 - 2005 Valeria Sventova, Jiri Krejsa, Peter Knut,
 *                                    Martin Kosalko, Marian Cerny, Michal Kral
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License (see docs/gpl.txt) as
 * published by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 */

/**
 *  @file docallbacks.h
 *
 *  contains the GLFW callbacks for now, later they should be in the engine
 *
 *  @author Fabian Rubin
 *
 *  @date 2025
 */

#pragma once

#include <glfw3.h>

#include "do_key_event.hpp"
#include "do_mouse_event.hpp"

// extern WindowData windowData;

struct WindowData
{
  std::function<void(Event &)> EventCallback;

  WindowData() = default;
  WindowData(const WindowData &) = delete;
  WindowData &operator=(const WindowData &) = delete;
};

void SizeCallback(GLFWwindow* window, int w, int h);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void MousePosCallback(GLFWwindow* window, double x, double y);
void MouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset);
void WindowRefreshCallback (GLFWwindow* window);
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void SetCallbacks(GLFWwindow* window);
