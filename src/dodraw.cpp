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
 *  @file dodraw.cpp
 *
 *  Drawing functions.
 *
 *  @author Peter Knut
 *  @author Marian Cerny
 *  @author Fabian Rubin
 *
 *  @date 2003, 2025
 */

// TODO: change later to use config again
// #include "doconfig.h"
#include "dodraw.h"
// #include "domap.h"
// #include "doplayers.h"
// #include "doraces.h"
// #include "domouse.h"
// #include "doselection.h"

//=========================================================================
// Global Variables
//=========================================================================

TFPS fps;           //!< Variable to compute count of frames per second.
TFPS fps_of_update; //!< Variable to compute count of frames per second of UpdateFunction().

/** On screen text. Shows text messages in the left corner of the screen. If
 *  #LOG_TO_OST is @c 1, log messages are also displayed. */
TOST *ost = NULL;

TGUI *gui = NULL; //!< Main gui node.

ImGuiIO *io = nullptr;              //!< ImGui IO
GLFWwindow *mBeronWindow = nullptr; //!< The Window

T_BYTE view_segment = DrawSettings::AllSegments; //!< Which segment is actually seen.

TPROJECTION projection;       //!< Actual projection.
bool reduced_drawing = false; //!< Reduced drawing for higher FPS. Usefull for testing network features on slow computers.
bool show_all = false;        //!< Displays whole map without warfog and unvisible areas.

VertexArrayObject vao;
VertexBufferObject vbo;
ElementBufferObject ebo;
Shader shader;
Texture texture;
Camera camera;

// float vertices[] = {
//     // positions          // colors           // texture coords
//     0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
//     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
//     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
//     -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
// };

// float vertices[] = {
//     // First quad
//     // positions           // colors           // texCoords
//      0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
//      0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//     -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//     -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // top left

//     // Second quad (x + 1.0f)
//      1.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
//      1.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//      0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//      0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
// };

std::vector<float> vertices;
std::vector<unsigned int> indices;

// unsigned int indices[] = {
//     // note that we start from 0!
//     0, 1, 3, // first triangle
//     1, 2, 3, // second triangle

//     // Second quad
//     4, 5, 7, // triangle 1
//     5, 6, 7  // triangle 2
// };

float texCoords[] = {
    0.0f, 0.0f, // lower-left corner
    1.0f, 0.0f, // lower-right corner
    0.5f, 1.0f  // top-center corner
};

glm::mat4 modelMatrix = glm::mat4(1.0f);
// glm::mat4 viewMatrix = glm::mat4(1.0f);
// glm::mat4 projectionMatrix;

//=========================================================================
// TPROJECTION
//=========================================================================

/**
 *  Changes projection type.
 *
 *  @param projection  Either #PRO_GAME or #PRO_MENU.
 */
void TPROJECTION::SetProjection(TPROJECTION_TYPE projection)
{
  // TODO: repurpose this later if a menu is added

  // GLfloat zoom = 1.0f;
  // GLfloat dx;

  // type = projection;

  // switch (type)
  // {
  // case PRO_MENU:
  //   // right = (GLfloat)config.scr_width;
  //   right = 1920.0f;
  //   left = 0.0;

  //   // top = (GLfloat)config.scr_height;
  //   top = 1080.0f;
  //   bottom = 0.0;

  //   width = right;
  //   height = top;
  //   break;

  // case PRO_GAME:
  //   // zoom = map.GetZoom();
  //   // TODO: change later to use map zoom

  //   right = ProjectionSettings::defaultWidth * zoom / 2;
  //   left = -right;

  //   top = ProjectionSettings::defaultHeight * zoom / 2;
  //   bottom = -top;

  //   width = ProjectionSettings::defaultWidth * zoom;
  //   height = ProjectionSettings::defaultHeight * zoom;
  //   break;

  // case PRO_RENDER_RADAR:
  //   // dx = ((GLfloat)(map.height) * DrawSettings::RadarTexSize) / (map.height + map.width);

  //   // TODO: rewrite later
  //   float widthMap = 800.0f;
  //   float heightMap = 800.0f;

  //   dx = ((GLfloat)(heightMap)*DrawSettings::RadarTexSize) / (heightMap + widthMap);
  //   zoom = DAT_MAPEL_DIAGONAL_SIZE * heightMap / dx;

  //   left = -dx * zoom;
  //   // right = (config.scr_width) * zoom + left;
  //   right = 1920.0f * zoom + left;

  //   // top = config.scr_height * zoom / 2;
  //   top = 1080.0f * zoom / 2;
  //   bottom = 0;

  //   // width = config.scr_width * zoom;
  //   // height = config.scr_height * zoom / 2;

  //   width = 1920.0f * zoom;
  //   height = 1080.0f * zoom / 2;
  //   break;
  // }

  // Update();

  // // set projection
  // glMatrixMode(GL_PROJECTION);
  // glLoadIdentity();

  // gluOrtho2D(left, right, bottom, top); // orthographic projection
  // // glViewport(0, 0, config.scr_width, config.scr_height);
  // glViewport(0, 0, 1920.0f, 1080.0f);

  // if (type == PRO_GAME)
  // {
  //   float dxMap = 0.0f;
  //   float dyMap = 0.0f;

  //   // glTranslated(map.dx, map.dy, 0.0);
  //   glTranslated(dxMap, dyMap, 0.0);
  // }

  // // reset model settings
  // glMatrixMode(GL_MODELVIEW);
  // glLoadIdentity();
}

/**
 *  Update projection.
 */
void TPROJECTION::Update()
{
  // TODO: rewrite later to use config, ignore for now
  // update game coefs
  // game_h_coef = (ProjectionSettings::defaultWidth * map.GetZoom()) / config.scr_width;
  // game_v_coef = (ProjectionSettings::defaultHeight * map.GetZoom()) / config.scr_height;
  // game_h_coef = (ProjectionSettings::defaultWidth * 1.0f) / 1920.0f;
  // game_v_coef = (ProjectionSettings::defaultHeight * 1.0f) / 1080.0f;

  game_h_coef = (ProjectionSettings::defaultWidth * 1.0f) / (480.0f * 2.0f);
  game_v_coef = (ProjectionSettings::defaultHeight * 1.0f) / (20.0f * 2.0f);
}

//=========================================================================
// TFPS
//=========================================================================

/**
 *  Computes new fps value.
 *  This computation is done only after standart time shift stored in DRW_FPS_DELAY.
 *
 *  @param time_shift  Time shift from the last update.
 */
void TFPS::Update(double time_shift)
{
  frames_count++;
  shift_time += time_shift;

  if (shift_time >= DrawSettings::FPSDelay)
  { // fps is drawed every DrawSettings::FPSDelay seconds
    // calculate FPS
    fps = (int)ceil(frames_count / shift_time - 0.49);

    // reset counters
    shift_time = 0.0;
    frames_count = 0;
  }
}

/**
 *  Resets fps information.
 */
void TFPS::Reset(void)
{
  fps = 0;
  shift_time = 0.0;
  frames_count = 0;
}

//=========================================================================
// Drawing
//=========================================================================

/**
 *  Inits basic OpenGL settings.
 */
void InitOpenGL(void)
{
  // glShadeModel(GL_FLAT);    // enable flat shading
  // glDisable(GL_DEPTH_TEST); // disable depth testing
  // glEnable(GL_TEXTURE_2D);  // enable textures

  // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // type of blending
  // glEnable(GL_BLEND);                                // enable blending

  // glReadBuffer(GL_BACK); // reading is set to read from back buffer

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // light grayish-blueish color
  // glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // black background
  // glClearDepth(1.0f);                   // default depth
}

/**
 *   Inits imgui.
 */
void InitImGui()
{
  // int width, height;
  // glfwGetWindowSize(mBeronWindow, &width, &height);

  // std::string s = std::to_string(width);
  // std::string s2 = std::to_string(height);

  // Debug((char *)s.c_str());
  // Debug((char *)s2.c_str());

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  // ImGuiIO &io = ImGui::GetIO();
  io = &ImGui::GetIO();
  io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

  // Setup Platform/Renderer backends
  // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
  ImGui_ImplGlfw_InitForOpenGL(mBeronWindow, true);
  ImGui_ImplOpenGL3_Init();
  // ImGui_ImplOpenGL3_Init("#version 410");
}

/**
 *   Inits basic VBO, IBO, VAO and Shader to test draw a triangle for now.
 *   Also binds everything for testing so it should be called
 *   AFTER all the OpenGL stuff is initialized
 */
void InitDrawingStuff()
{
  // first quad
  vertices.insert(vertices.end(), {0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f});   // top right
  vertices.insert(vertices.end(), {0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f});  // bottom right
  vertices.insert(vertices.end(), {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f}); // bottom left
  vertices.insert(vertices.end(), {-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f});  // top left

  // first quad
  indices.insert(indices.end(), {0, 1, 3}); // first triangle
  indices.insert(indices.end(), {1, 2, 3}); // second triangle

  AddQuad(vertices, glm::vec2(1.0f, 0.0f));
  AddQuad(vertices, glm::vec2(0.0f, 1.0f));
  AddQuad(vertices, glm::vec2(-1.0f, 0.0f));
  AddQuad(vertices, glm::vec2(0.0f, -1.0f));

  //      0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
  //      0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
  //     -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
  //     -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // top left

  //     // Second quad (x + 1.0f)
  //      1.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
  //      1.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
  //      0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
  //      0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left

  // generate and bind Vertex Array Object
  vao.Create();
  vao.Bind();

  // generate, bind and fill Vertex Buffer
  vbo.Create();
  vbo.Bind();

  vbo.BufferData(vertices.size() * sizeof(float), vertices.data());

  ebo.Create();
  ebo.Bind();
  ebo.BufferData(indices.size() * sizeof(unsigned int), indices.data());

  vbo.SetAttribPointers();

  // create shader
  shader.Create("src/shaders/tex_vert.glsl", "src/shaders/tex_frag.glsl");

  // create texture
  texture.Create("test_assets/test_img.jpg");

  // bind shader
  shader.Bind();

  // sets the uniform for the texture
  shader.SetInt("texture1", 0);

  // create camera
  camera.Create();

  // Test
  // modelMatrix = glm::translate(modelMatrix, glm::vec3(10.0f));
  // modelMatrix = glm::scale(modelMatrix, glm::vec3(20.0f));
  // viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));

  // rotate by -90 degrees so the plane lies "on the floor"
  modelMatrix = glm::rotate(modelMatrix, glm::radians(-90.0f), glm::vec3(1, 0, 0));

  // viewMatrix = glm::rotate(viewMatrix, glm::radians(35.264f), glm::vec3(1, 0, 0)); // Rotate around X axis
  // viewMatrix = glm::rotate(viewMatrix, glm::radians(45.0f), glm::vec3(0, 1, 0));   // Then rotate around Y axis

  // camera.setCameraPos(glm::vec3(0.0f, 0.0f, 20.0f));

  // Then pull the camera back
  // viewMatrix = glm::translate(viewMatrix, -camera.getCameraPos());

  // projectionMatrix = glm::perspective(glm::radians(45.0f), (480.0f * 2.0f) / (420.0f * 2.0f), 0.1f, 100.0f);
  camera.SetProjection((480.0f * 2.0f), (420.0f * 2.0f));

  // TODO: do this inside draw
  shader.SetMatrix4f("model", modelMatrix);
  shader.SetMatrix4f("view", camera.GetView());
  shader.SetMatrix4f("projection", camera.GetProjection());

  // glm::mat4 trans = glm::mat4(1.0f);
  // trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
  // trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

  // shader.SetMatrix4f("transform", trans);
  // std::string s = "x: " + std::to_string(vec.x) + ", y: " + std::to_string(vec.y) + ", z: " + std::to_string(vec.z);
  // Info((char *)s.c_str());
}

/**
 *  Draws actual frames per second in left corner of the screen if @c show_fps
 *  is set in config file.
 */
void DrawFps(void)
{
  ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);

  // Create a window with no title bar, disabling resize and setting background color to transparent
  ImGui::Begin("FPS Window", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);

  ImGui::Text("FPS: %d", fps.fps);
  ImGui::End();
}

/**
 *  Draw game.
 */
void DrawGame(double deltaTime)
{
  camera.SetDeltaTime(deltaTime);

  glClear(GL_COLOR_BUFFER_BIT);
  // TODO: draw a single image

  // bind texture
  texture.Bind();

  // currently draws a quad
  shader.Bind();
  vao.Bind();

  // TODO: maybe pass clock into here for these calculations?

  // glm::mat4 trans = glm::mat4(1.0f);
  // trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
  // trans = glm::rotate(trans, (float)glfwGetTime() * 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));

  // shader.SetMatrix4f("transform", trans);
  // shader.SetMatrix4f("projection", camera.GetProjection());

  // viewMatrix = glm::translate(viewMatrix, -camera.getCameraPos());

  // viewMatrix = glm::lookAt(camera.getCameraPos(), camera.getCameraPos() + camera.getCameraFront(), camera.getUp());

  // camera.setCameraPos(glm::vec3(1.0f, 0.0f, 0.0f));

  shader.SetMatrix4f("view", camera.GetView());

  shader.SetMatrix4f("projection", camera.GetProjection());

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // enable wireframe
  glDrawElements(GL_TRIANGLES, 6 * 30, GL_UNSIGNED_INT, 0);
  // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // disable wireframe

  // texture.Unbind();
  // shader.Unbind();
  // vao.Unbind();

  // TODO: draw triangle

  // char txt[257];

  // clear buffers
  // glClear(GL_COLOR_BUFFER_BIT);

  // projection.SetProjection(PRO_GAME);

  if (!reduced_drawing)
  {
    // TODO: do later
    // map
    // map.Draw(); // calls glClear
    // selection->DrawUnitsLines();
    // mouse.DrawBuildMap();
  }

  // menu projection
  // projection.SetProjection(PRO_MENU);

  // draw on screen text
  ost->Draw(); // should work?

  DrawFps();

  // if (config.show_process_fps)
  // {
  // glColor3f(1.0f, 1.0f, 1.0f);
  // sprintf(txt, "Process FPS: %d", fps_of_update.fps);
  // glfPrint(font0, 10.0f, config.scr_height - 36.0f, txt, true);
  // glfPrint(font0, 10.0f, 1080.0f - 36.0f, txt, true);
  // }

  // mouse.DrawSelection();

#if DEBUG
  // TODO: later
  // mouse info
  // glColor3f(0.7f, 0.7f, 0.7f);
  // sprintf(txt, "Mouse: x: %d, y: %d", mouse.map_pos.x, mouse.map_pos.y);
  // glfPrint(font0, 10.0f, config.scr_height - 70.0f, txt, true);

  // units count
  // glColor3f(0.7f, 0.7f, 0.7f);
  // sprintf(txt, "Units count: %d", myself->GetPlayerUnitsCount());
  // glfPrint(font0, 10.0f, config.scr_height - 85.0f, txt, true);
#endif

  if (reduced_drawing)
  {
    // glColor3f(1.0f, 0.93f, 0.82f);
    // glfPrint(font0, GLfloat(config.scr_width / 2 - 50), GLfloat(config.scr_height / 2), const_cast<char *>("Low CPU mode"), false);

    // glfPrint(font0, GLfloat(1920.0f / 2 - 50), GLfloat(1080.0f / 2), const_cast<char *>("Low CPU mode"), false);
    // glColor3f(0.7f, 0.7f, 0.7f);
    // glfPrint(font0, GLfloat(1920.0f / 2 - 70), GLfloat(1080.0f / 2 - 15), const_cast<char *>("press 'G' for exit"), false);

    // struct timespec interval;
    // interval.tv_sec = 0;
    // interval.tv_nsec = 0.05;
    // thrd_sleep(&interval, NULL);
    // std::this_thread::sleep_for(std::chrono::duration<double>(0.05));
  }

  // draw gui
  // gui->Draw();

  // mouse cursor
  // mouse.Draw();
}

/**
 *  Logs a log message to #ost.
 *
 *  @param level  Log level.
 *  @param header Text description of the log level.
 *  @param msg    Log message itself.
 */
// void LogToOst(int level, const char *header, const char *msg)
void LogToOst(int level, const char *header, const char *msg, const char *file, int line)
{
  if (!ost)
    return;

  switch (level)
  {
  case LOG_DEBUG:
    ost->AddText(msg, LogColors::debugColorR, LogColors::debugColorG, LogColors::debugColorB);
    break;

  case LOG_INFO:
    ost->AddText(msg, LogColors::infoColorR, LogColors::infoColorG, LogColors::infoColorB);
    break;

  case LOG_WARNING:
    ost->AddText(msg, LogColors::warningColorR, LogColors::warningColorG, LogColors::warningColorB);
    break;

  case LOG_ERROR:
    ost->AddText(msg, LogColors::errorColorR, LogColors::errorColorG, LogColors::errorColorB);
    break;

  case LOG_CRITICAL:
    ost->AddText(msg, LogColors::criticalColorR, LogColors::criticalColorG, LogColors::criticalColorB);
    break;
  }
}

/**
 *   Shuts down imgui.
 */
void ShutdownImGui()
{
  // delete io;
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

/**
 *   Starts the Dear ImGui frame, call before rendering
 */
void StartImGuiFrame()
{

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

/**
 *   Renders ImGui stuff to the screen, call before glfwSwapBuffers but after rendering glfw stuff
 */
void RenderImGui()
{
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

/**
 *   Does the Event Stuff for the drawing (camera etc.)
 */
void OnEventDraw(Event &e)
{
  camera.OnEvent(e);
}

/**
 *   Adds a quad
 *  *  @param verts     the vertices.
 *  *  @param verts     the offset.
 */
void AddQuad(std::vector<float> &verts, glm::vec2 offset)
{
  float base[] = {
      // positions         // colors          // tex coords
      0.5f, 0.5f, 0.0f, 1, 0, 0, 1, 1,   // top right
      0.5f, -0.5f, 0.0f, 0, 1, 0, 1, 0,  // bottom right
      -0.5f, -0.5f, 0.0f, 0, 0, 1, 0, 0, // bottom left
      -0.5f, 0.5f, 0.0f, 1, 1, 0, 0, 1   // top left
  };

  for (int i = 0; i < 4; ++i)
  {
    vertices.push_back(base[i * 8 + 0] + offset.x); // x
    vertices.push_back(base[i * 8 + 1] + offset.y); // y
    for (int j = 2; j < 8; ++j)
      vertices.push_back(base[i * 8 + j]); // rest
  }

  // indices.insert(indices.end(), {0, 1, 3}); // first triangle
  // indices.insert(indices.end(), {1, 2, 3}); // second triangle

  int idx = indices.back();

  indices.push_back(idx + 1);
  indices.push_back(idx + 2);
  indices.push_back(idx + 4);
  indices.push_back(idx + 2);
  indices.push_back(idx + 3);
  indices.push_back(idx + 4);
}

// TOST seems to work 100%
//=========================================================================
// TOST
//=========================================================================

/**
 *  Constructor.
 *
 *  @warning Mutex is only created when constructor is called after glfwInit().
 */
TOST::TOST()
{
  count = 0;
  for (int i = 0; i < OnScreenTextSettings::maxLines; i++)
  {
    unused_texts_stack[i] = i;
  }
  first = last = OnScreenTextSettings::ostNull;

  // shouldn't be needed because mutexes are always initialized on creation
  // #ifdef NEW_GLFW3
  // if (mtx_init(&mutex, mtx_plain) == thrd_error)
  // {
  //   Critical("Mutex could not be created");
  // }
  // #else
  //   mutex = glfwCreateMutex();

  //   if (mutex == NULL)
  //     Critical("Mutex could not be created");
  // #endif
}

/**
 *  Destructor.
 */
TOST::~TOST()
{
  // should not be needed
  /* The mutex is destroyed, if it was created successfully. */
  // #ifdef NEW_GLFW3
  //   mtx_destroy(&mutex);
  // #else
  //   if (mutex)
  //     glfwDestroyMutex(mutex);
  // #endif
}

/**
 *  Adds a text with the time in seconds, how long should the text remain on
 *  the screen and the text color.
 *
 *  @param s        Text string to add.
 *  @param last_for Time in seconds this text should remain on the screen.
 *  @param red      Color of the text (red component).
 *  @param green    Color of the text (green component).
 *  @param blue     Color of the text (blue component).
 *
 *  @note This function is thread safe.
 */
void TOST::AddText(const char *s, double last_for, float red, float green, float blue)
{
  int new_text;

  /* Only one thread can access data. */
  bool res = mutex.try_lock();
  if (!res)
    return;

  // Finds the position in stack for the text.
  if (count == OnScreenTextSettings::maxLines)
  {
    new_text = first;
    first = text[first].next;
    if (first == OnScreenTextSettings::ostNull)
      last = OnScreenTextSettings::ostNull;
  }
  else
    new_text = unused_texts_stack[count++];

  // Adds the text.
  text[new_text].next = OnScreenTextSettings::ostNull;
  text[new_text].disappear_time = OnScreenTextSettings::ostNull;
  text[new_text].last_for = last_for;
  text[new_text].red = red;
  text[new_text].green = green;
  text[new_text].blue = blue;

  /* Makes a copy of the string s. The string will be always finished by '\0',
   * because text[].string[OST_MAX_TEXT_LENGTH] is initialized to '\0' in
   * constructor. */
  strncpy(text[new_text].string, s, OnScreenTextSettings::maxTextLength);

  // Adds the new text to linked list
  if (last == OnScreenTextSettings::ostNull)
    first = new_text;
  else
    text[last].next = new_text;

  last = new_text;
  // #ifdef NEW_GLFW3
  //   mtx_unlock(&mutex);
  // #else
  //   glfwUnlockMutex(mutex);
  // #endif
  mutex.unlock();
}

// seems to work
/**
 *  Removes texts, which are already on the screen for #last_for seconds.
 *
 *  @param actual_time  Time of last update.
 *
 *  @return @c true if some text was removed or new text added recently.
 *          If no change has been made, returns @c false.
 *
 *  @note This function is thread safe.
 */
bool TOST::Update(double actual_time)
{
  int p;
  int previous = OnScreenTextSettings::ostNull;

  bool any_change_made = false;

  /* Only one thread can access data. */
  // #ifdef NEW_GLFW3
  //   mtx_lock(&mutex);
  // #else
  //   glfwLockMutex(mutex);
  // #endif
  bool res = mutex.try_lock();
  if (!res)
    return false;

  /* Texts, which are displayed for too long are removed. */
  p = first;
  while (p != OnScreenTextSettings::ostNull)
  {
    if (text[p].disappear_time == OnScreenTextSettings::ostNull)
    {
      // If it is the first time this text p will be displayed, we count
      // disappear_time for it.
      text[p].disappear_time = actual_time + text[p].last_for;

      any_change_made = true;
    }
    else if (text[p].disappear_time <= actual_time)
    {
      // If the text is too long on the screen, it is removed.
      unused_texts_stack[--count] = p;

      // Removes p from linked list
      if (p == first)
        first = text[p].next;
      else
        text[previous].next = text[p].next;

      if (p == last)
        last = previous;

      if (previous != OnScreenTextSettings::ostNull)
        text[previous].next = text[p].next;

      any_change_made = true;
    }
    else
      previous = p;

    p = text[p].next;
  }

  mutex.unlock();

  return any_change_made;
}

// seems to work
/**
 *  Draws the all texts to the screen.
 *
 *  @note This function is thread safe.
 */
void TOST::Draw()
{
  int p;

  /* Only one thread can access data. */
  bool res = mutex.try_lock();
  if (!res)
    return;

  // Should work with the text array

  /* Displays all texts. */
  int i;

  ImGui::SetNextWindowPos(ImVec2(0.0f, 20.0f), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(1080.0f, 200.0f), ImGuiCond_Always);
  ImGui::Begin("Window", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);

  for (p = first, i = 0; p != OnScreenTextSettings::ostNull; p = text[p].next, i++)
  {
    // glColor3f(text[p].red, text[p].green, text[p].blue);
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(text[p].red * 255, text[p].blue * 255, text[p].green * 255, 255));
    ImGui::Text(text[p].string);
    ImGui::PopStyleColor();

    // glfPrint(font0, 10.0f, ((GLfloat)OnScreenTextSettings::maxLines - i + 1) * 13, text[p].string, true);
  }

  ImGui::End();

  mutex.unlock();
}

//=========================================================================
// END
//=========================================================================
// vim:ts=2:sw=2:et: