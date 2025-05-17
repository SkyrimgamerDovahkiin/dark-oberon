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
 *  @file doberon.cpp
 *
 *  Main module.
 *
 *  @author Peter Knut
 *  @author Marian Cerny
 *
 *  @date 2002, 2003, 2004
 */

/**
 *  @mainpage
 *
 *  An advanced strategy game.
 *
 *  @date Copyright 2002, 2003, 2004, 2005
 *
 *  @author Valeria Sventova    <liberty@matfyz.cz>
 *  @author Jiri Krejsa         <crazych@matfyz.cz>
 *  @author Peter Knut          <peterpp@matfyz.cz>
 *  @author Martin Kosalko      <cauchy@matfyz.cz>
 *  @author Marian Cerny        <jojo@matfyz.cz>
 *  @author Michal Kral         <index@matfyz.cz>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License (see docs/gpl.txt) as
 *  published by the Free Software Foundation; either version 2 of the License,
 *  or (at your option) any later version.
 *
 *  Powered by GLFW - an OpenGL framework <http://glfw.sourceforge.net/>
 */

// #include "cfg.h"
// #include "doalloc.h"

// NOTE: background music in gui file???
// NOTE: figure out how to load the background music

#include <ctime>
#include <stdlib.h>
#include <string>
#include <array>
#include <charconv>
#include <chrono>
#include <sstream>

// needs to be included before because this includes GLAD
#include "dodraw.h"

#include <glfw3.h>

// #include "doconfig.h"
// #include "doengine.h"
// #include "doipc.h"
// #include "domouse.h"
#include "dologs.h"
#include "dosound.h"
#include "docallbacks.h" // custom, for now

// #include "dodraw.h"
// #include "utils.h"

// imgui
// #include "imgui.h"
// #include "imgui_impl_glfw.h"
// #include "imgui_impl_opengl3.h"

using std::string;

// TODO: use another image in test assets

// TODO: dodraw (because i hate myself)

// - sounds done, at least for now
// - logs done, at least for now

// do here for now
// TODO: move to another file
// struct WindowData
// {
//   std::function<void(Event &)> EventCallback;

//   WindowData() = default;
//   WindowData(const WindowData &) = delete;
//   WindowData &operator=(const WindowData &) = delete;
// };

WindowData windowData;

//========================================================================
// Initializing & Destroying
//========================================================================

/**
 *   Closes the Window.
 */
bool Close(KeyPressedEvent &e)
{
  if (e.GetKeyCode() == GLFW_KEY_ESCAPE)
  {
    glfwSetWindowShouldClose(mBeronWindow, GLFW_TRUE);
  }

  return false;
}

/**
 *   Does the Event stuff.
 */
void OnEvent(Event &e)
{
  Debug((char *)e.ToString().c_str());
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<KeyPressedEvent>(std::bind(&Close, std::placeholders::_1));
  OnEventDraw(e);
}

/**
 *   Inits basic IO handling.
 */
void InitIO(void)
{
  glfwMakeContextCurrent(mBeronWindow);

  // init GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    Error("Failed to initialize GLAD");
    return;
  }

  // synchronize with monitor refresh rate
  // glfwSwapInterval(config.vert_sync ? 1 : 0);

  // lets use v-sync enabled for now
  glfwSwapInterval(1);

  // disable sticky input
  if (!mBeronWindow)
  {
    glfwSetInputMode(mBeronWindow, GLFW_STICKY_KEYS, GLFW_FALSE);
    glfwSetInputMode(mBeronWindow, GLFW_STICKY_MOUSE_BUTTONS, GLFW_FALSE);
  }

  // set callback functions
  if (mBeronWindow)
  {
    // glfwSetWindowSizeCallback(mBeronWindow, SizeCallback);
    // glfwSetKeyCallback(mBeronWindow, KeyCallback);

    // glfwSetKeyCallback(mBeronWindow, [](GLFWwindow *window, int key, int scancode, int action, int mods)
    //                    {
    //     WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

    //     switch (action)
    //     {
    //         case GLFW_PRESS:
    //         {
    //             KeyPressedEvent event(key);
    //             data.EventCallback(event);
    //             break;
    //         }
    //         case GLFW_RELEASE:
    //         {
    //           // TODO: release event
    //             break;
    //         }
    //         case GLFW_REPEAT:
    //         {
    //             // TODO: repeat event (if needed at all)
    //             break;
    //         }
    //     } });

    // glfwSetMouseButtonCallback(mBeronWindow, MouseButtonCallback);
    // glfwSetCursorPosCallback(mBeronWindow, MousePosCallback);
    // glfwSetScrollCallback(mBeronWindow, MouseWheelCallback);
    // glfwSetWindowRefreshCallback(mBeronWindow, WindowRefreshCallback);
    // glfwSetFramebufferSizeCallback(mBeronWindow, FramebufferSizeCallback);
    SetCallbacks(mBeronWindow);
  }

  // disable mouse cursor in window mode (TODO: later)
  // #ifdef NEW_GLFW3
  if (mBeronWindow)
  {
    // if (!config.fullscreen) glfwSetInputMode(mBeronWindow, GLFW_MOUSE_CURSOR, GLFW_FALSE);

    // TODO: later
    // if (!config.fullscreen)
    // {
    // glfwSetInputMode(mBeronWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    // }
    // windowData.EventCallback = std::bind(&OnEvent, std::placeholders::_1);
    windowData.EventCallback = OnEvent;
    glfwSetWindowUserPointer(mBeronWindow, &windowData);
  }
  // #else
  // 	if (!config.fullscreen) glfwDisable(GLFW_MOUSE_CURSOR);
  // #endif

  // glViewport(0, 0, 1920, 1080);
  glViewport(0, 0, 480 * 2, 420 * 2);
}

/**
 *   Inits everything on game start. Returns true if successful.
 */
bool InitAll(void)
{
  srand((unsigned)time(NULL)); // initializing of random generator

  // initialize log files, should work?
  if (!OpenLogFiles())
  {
    Warning("Log files were not opened");
  }

  // initialize GLFW
  if (!glfwInit())
  {
    Critical("Can not initialize GLFW library");
    return false;
  }

  // Initialize network on Windows.
  // Network stuff disabled for now
  // init_sockets ();

  // pool_net_messages = NEW TPOOL<TNET_MESSAGE>(1000, 0, 100);

  // initialize memory checking system
  // must be called after initializing log files and GLWF
  // #if DEBUG_MEMORY
  //   InitMemorySestem();
  // #endif

  // initialize SDL2 Mixer
#if SOUND
  if (SDL_Init(SDL_INIT_AUDIO) < 0)
  {
    // std::cerr << "SDL init error: " << SDL_GetError() << std::endl;
    Error((char *)SDL_GetError());
    // return 1;
  }

  if (!InitSound(MIX_INIT_MP3))
    Error("Can not initialize sound");
#endif

  // configuration
  // LoadConfig(); // load configuration from file, disabled for now

  // #ifdef NEW_GLFW3
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

  // always create "fullscreen" window for now
  // mBeronWindow = glfwCreateWindow(1920, 1080, "Dark Oberon", glfwGetPrimaryMonitor(), NULL);

  mBeronWindow = glfwCreateWindow(480.0f * 2.0f, 420.0f * 2.0f, "Dark Oberon", NULL, NULL);

  // switch (config.pr_wnd_mode)
  // {
  // case OBERON_WINDOW:
  //   mBeronWindow = glfwCreateWindow(config.scr_width, config.scr_height, "Dark Oberon", NULL, NULL);
  //   break;
  // case OBERON_FULLSCREEN:
  //   mBeronWindow = glfwCreateWindow(config.scr_width, config.scr_height, "Dark Oberon", glfwGetPrimaryMonitor(), NULL);
  //   break;
  // default:
  //   mBeronWindow = glfwCreateWindow(config.scr_width, config.scr_height, "Dark Oberon", NULL, NULL);
  // }

  if (!mBeronWindow)
  {
    // Window or OpenGL context creation failed
    Critical("Can not open OpenGL window");
    glfwTerminate();
    return false;
  }

  if (mBeronWindow)
  {
    // Doesn't get logged to OST because OST is initialized later
    Debug("The Window is existent!");
  }

  // #else
  //   // open OpenGL window
  //   if (!glfwOpenWindow(config.scr_width, config.scr_height, // width, height
  //                       8, 8, 8,                             // bit per red, green, blue
  //                       0, 8, 0,                             // alfa, depth, stencil
  //                       config.pr_wnd_mode))
  //   { // window mode
  //     Critical("Can not open OpenGL window");
  //     glfwTerminate();
  //     return false;
  //   }
  //   glfwSetWindowTitle("Dark Oberon"); // set window title
  // #endif

  // load data, disabled for now
  // if (!LoadData())
  // {
  //   glfwTerminate();
  //   return false;
  // }

  // create fonts, disabled for now
  // if (!CreateFonts())
  // {
  //   glfwTerminate();
  //   DeleteData();
  //   return false;
  // }

  // gui = NEW TGUI();
  // gui->SetCursorHeight(DRW_CURSOR_HEIGHT);

  /* This section MUST be called after glfwInit(). */
  ost = NEW TOST; // Initialise On Screen Text.
  // Registers function LogToOst() as log callback.
  RegisterLogCallback(LogToOst);

  // initialize player array
  // player_array.Initialise();

  /* Init giant mutex. */
  // init_giant();
  // process_mutex = NEW TRECURSIVE_LOCK();

  // CreateLogMutex();

  /* MUST be called after glfwInit(), but before InitIO(). */
  // need_redraw = NEW TSAFE_BOOL_SWITCH(true);

  InitIO();

  Debug("Hello from OST!");
  Info("This is an Info text, also from OST");

  // does work here because we have set up OpenGL/GLAD and the creation
  // happens only inside InitDrawingStuff()
  InitOpenGL();
  InitDrawingStuff();
  InitImGui();
  // InitPositionChanges();
  // map.InitPools();

  // queue_events = NEW TQUEUE_EVENTS;
  // if (!queue_events)
  // {
  //   Critical("Could not create game structure queue_events");
  //   return false;
  // }

  // mouse.Center();
  return true;
}

/**
 *   Destroys everything and free memory on game end.
 */
void DestroyAll(void)
{
  // if (queue_events)
  //   delete queue_events;

  // save configuration
  // SaveConfig();

  // destroy structures
  // DestroyFonts();
  // DeleteData();

  // destroy OST
  // if (ost)
  //   delete ost;
  // RegisterLogCallback(NULL);
  // delete need_redraw;

  // destroy gui
  // if (gui)
  //   delete gui;

  // DestroyLogMutex();
  // delete process_mutex;

#if SOUND
  Mix_CloseAudio();
  Mix_Quit();
  SDL_Quit();
#endif

  // stop memory checking system
  // must be called before closing log files
#if DEBUG_MEMORY
  DoneMemorySystem();
#endif

  // TODO: move to draw later
  ShutdownImGui();

  // close OpenGL window
  glfwTerminate();

  // Initialize network on Windows.
  // end_sockets();

  // end logging
  CloseLogFiles();
}

//========================================================================
// Main Function
//========================================================================

// test

/**
 *   Program's main().
 *
 *   @returns @c EXIT_SUCCESS on successful end, otherwise @c EXIT_FAILURE.
 */
int main(int argc, char *argv[])
{
  auto interval = std::chrono::seconds(1);
  auto startTime = std::chrono::steady_clock::now();
  auto lastTime = startTime;

  // Info("This is a test!");
  // Warning("This is a test!");
  // Error("This is a test!");
  // Critical("This is a test!");
  // Debug("This is a test!");

  // char *home = getenv("HOME");
  // if (!home)
  //   home = "/tmp";

  // user_dir = string (home) + "/.dark-oberon/";
  // do_mkdir (user_dir);

  if (!InitAll())
  {
    return EXIT_FAILURE;
  }

  TSTREAM stream;
  bool res = stream.Load("test_assets/game_music.mp3");

  if (!res)
  {
    std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
    return 1;
  }

  // Mix_PlayMusic(music, -1);
  stream.Play();
  stream.SetLoop(0);

  // delete this line to play the music
  stream.SetVolume(0);

  // SDL_Event event;
  bool quit = false;
  bool is_playing = true;

  // init clock
  TTIME clock;

  // fps stuff
  // double time_actual = glfwGetTime();
  // double time_shift = 0.0;
  fps.Reset();

  // test texts
  // ost->AddText("txt", 1.0f, 0.0f, 0.0f);

  // TODO: temporary now, replace later
  // Drawing drawing;
  // InitDrawingStuff();

  while (!glfwWindowShouldClose(mBeronWindow))
  {
    auto now = std::chrono::steady_clock::now();
    clock.Update();

    glfwPollEvents();

    fps.Update(clock.GetShift());
    // don't do for now
    // ost->Update(time_actual);

    StartImGuiFrame();

    // draws the Game stuff
    DrawGame(clock.GetShift());

    // TODO: draw all other shit

    // if (stream.IsPlaying() && (now - lastTime >= interval))
    // {

    //   std::ostringstream oss;
    //   oss << std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
    //   std::string msgTime = oss.str();

    //   std::string msg = "Song is still playing, elapsed time: " + msgTime + " seconds";
    //   Debug((char *)msg.c_str());

    //   lastTime = now;
    // }

    RenderImGui();

    glfwSwapBuffers(mBeronWindow);
  }

  // // main loop
  // while (state != ST_QUIT)
  // {
  //   switch (state)
  //   {
  //   case ST_MAIN_MENU:
  //   case ST_VIDEO_MENU:
  //   case ST_PLAY_MENU:  Menu(); break;
  //   case ST_GAME:       Game(); break;

  //   default: break;
  //   }
  // }

  DestroyAll();

  return EXIT_SUCCESS;
}

//=========================================================================
// END
//=========================================================================
// vim:ts=2:sw=2:et:
