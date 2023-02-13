//
// Created by Kim Huber on 11/28/22.
//

#include "openglTextureStorage.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// define the global textureStorage
std::vector<ImTexture> openglTextureStorage::textures{};

openglTextureStorage::~openglTextureStorage() {
    for (auto texture: textures) {
        glDeleteTextures(1, reinterpret_cast<const GLuint *>(texture.TextureID));
    }
}

ImTextureID openglTextureStorage::loadTextureFromFile(const char *filename) {
// Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char *image_data = stbi_load(filename, &image_width, &image_height, nullptr, 4);
    if (image_data == nullptr)
        return nullptr;

// Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

// Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

// Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    ImTexture tex;
    tex.TextureID = reinterpret_cast<ImTextureID>(image_texture);
    tex.Width = image_width;
    tex.Height = image_height;
    textures.emplace_back(tex);
    return reinterpret_cast<ImTextureID>(image_texture);
}
std::vector<ImTexture>::iterator openglTextureStorage::findTexture(ImTextureID id) {
    return std::find_if(textures.begin(), textures.end(), [id](ImTexture &texture) {
      return texture.TextureID == id;
    });
}
void openglTextureStorage::destroyTexture(ImTextureID texture) {
    auto textureIt = findTexture(texture);
    if (textureIt == textures.end())
        return;

    glDeleteTextures(1, reinterpret_cast<const GLuint *>(&textureIt->TextureID));

    textures.erase(textureIt);
}

int openglTextureStorage::getTextureWidth(ImTextureID texture) {
    auto textureIt = findTexture(texture);
    if (textureIt != textures.end())
        return textureIt->Width;
    return 0;
}

int openglTextureStorage::getTextureHeight(ImTextureID texture) {
    auto textureIt = findTexture(texture);
    if (textureIt != textures.end())
        return textureIt->Height;
    return 0;
}
