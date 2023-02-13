/**
@file imGuiCustom.h
@brief The file contains the implementation of a custom imGui window.
The imGuiCustom class provides the functionality to create and render a custom imGui window.
 It uses GLFW and OpenGL for creating a window and rendering. It also uses the Dear ImGui library for creating UI elements.
 The class provides methods for creating a window, rendering a frame, and destroying the window.
@author Kim Huber
*/

#ifndef IMGUICUSTOM_H
#define IMGUICUSTOM_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cstdio>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>
#include <memory>

class imGuiCustom {
  GLFWwindow *m_window = nullptr;
  bool m_created = false;

 public:
  imGuiCustom() = default;
  ~imGuiCustom();

  // must be public for reflection system
  const char *programName = "window";
  int windowWidth = 1920;
  int windowHeight = 1080;
  ImVec4 clear_color;
  bool docking = false;
  bool fullscreen = false;

  /**
   * @brief   Creates the GLFW context and the opengl window. After the call we got an empty window which can be
   *          filled. The function is guarded and will not create a second window if there is already one.
   * @return  error code 0=everything ok, -1 = error while creating the window
   */
  int createWindow();

  /**
   * @brief   Clears the opengl window and GLFW context. With this function we can clear the window without
   *          stopping the program. Is also called by the destructor. The function is guarded and will not cause an
   *          error if there is no window to destroy.
   */
  void destroyWindow();

  /**
   * @brief   Creates a new frame which ImGui can fill. Must be called at the beginning of each frame.
   */
  static void createFrame();

  /**
   * @brief   Renders the filled frame. Also clears the frame afterwards so we must call create frame again.
   */
  void renderFrame();

  /**
   * @brief   Checks if a window exists.
   * @return  True if the window exists otherwise false.
   */
  [[nodiscard]] bool checkWindow() const;

};

// for my reflection pipeline
#ifdef WITH_PIPELINE_GENERATOR
#include "string"
#include "pipelineGenerator.hpp"
inline bool parseBool(int i){
  return i;
}

inline const char* parseStringToC(const std::string& str){
  return str.c_str();
}

REFL_AUTO(
    type(imGuiCustom),
    field(programName, instanceProperty(instancePropertyType::STRING, &parseStringToC)),
    field(windowWidth, instanceProperty(instancePropertyType::INT, &basicParser::parse_integer)),
    field(windowHeight, instanceProperty(instancePropertyType::INT, &basicParser::parse_integer)),
    field(docking, instanceProperty(instancePropertyType::INT, &parseBool))
)
#endif //WITH_PIPELINE_GENERATOR

#endif //IMGUICUSTOM_H
