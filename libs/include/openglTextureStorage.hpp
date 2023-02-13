//
// Created by Kim Huber on 3/28/21.
//


#ifndef GUIBACKEND_LIBS_SRC_TEXTURESTORAGE_HPP
#define GUIBACKEND_LIBS_SRC_TEXTURESTORAGE_HPP
#include <vector>
#include <cstdint>
#include <algorithm>
#include <GL/gl.h>
#include <imgui.h>

struct ImTexture {
  ImTextureID TextureID = nullptr;
  int Width = 0;
  int Height = 0;
};

struct openglTextureStorage {
  ~openglTextureStorage();

  // Simple helper function to load an image into a OpenGL texture with common settings
  static ImTextureID loadTextureFromFile(const char *filename);

  static std::vector<ImTexture>::iterator findTexture(ImTextureID id);

  static void destroyTexture(ImTextureID texture);

  static int getTextureWidth(ImTextureID texture);

  static int getTextureHeight(ImTextureID texture);

 private:
  static std::vector<ImTexture> textures;
};

#endif //GUIBACKEND_LIBS_SRC_TEXTURESTORAGE_HPP