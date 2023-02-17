#include "imGuiCustom.h"
#include "fontStorage.hpp"
#include "openglTextureStorage.hpp"

// needed states for the windows
bool show_another_window = true;

ImTextureID t;

// just for testing purpose
void showDemo() {
    // Show a simple window that we create ourselves. We use Begin/End pair to create a named window.
    {
      static float f = 0.0f;
      static int counter = 0;
      ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
      ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
      ImGui::Checkbox("Another Window", &show_another_window);
      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
      if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                  static_cast<double>(1000.0f / ImGui::GetIO().Framerate),
                  static_cast<double>(ImGui::GetIO().Framerate));
      ImGui::Image(t, ImVec2(static_cast<float>(openglTextureStorage::getTextureWidth(t)),
                                              static_cast<float>(openglTextureStorage::getTextureHeight(t))));
      ImGui::End();
    }
    // 3. Show another simple window.
    if (show_another_window)
    {
      ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
      fontStorage::setFontNormal();
      ImGui::Text("Hello from another window!");
      ImGui::Text( ICON_FA_PAINT_BRUSH "  Paint" );
      if (ImGui::Button("Close Me"))
        show_another_window = false;
      ImGui::End();
    }
  }


int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    imGuiCustom gui;
    gui.docking = true;
    gui.createWindow();
    t = openglTextureStorage::loadTextureFromFile("testImage.jpg");
    fontStorage::addFont(0);

    while(gui.checkWindow())
    {
      imGuiCustom::createFrame();
      showDemo();
      gui.renderFrame();
    }

    return 0;
}