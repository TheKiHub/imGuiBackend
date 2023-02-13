//
// Created by Kim Huber
//

/**
 * Tis is just a central class for controlling the fonts. Every module will use the functions and set their individual
 * size relative to the other modules. From this place we can then control the absolute values.
 * They are all loaded at a huge size and then are scaled down. This way we don't need anti aliasing.
 */

#ifndef GUIBACKEND_FONTHOLDER_HPP_
#define GUIBACKEND_FONTHOLDER_HPP_
#include "IconsFontAwesome5.h"
#include <imgui.h>

/**
 * Load a font for the application. Everything is static so you should never create an instance of this storage.
 */
namespace fontStorage{
  enum{
    rabbitHighwaySignBoldCaps,
    robotoBold,
    millesHandwriting
  };

  constexpr ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

  /**
   * Adds a font which are available can be seen in the repository readme.
   * @param number which font will be loaded, should be set with a config file
   */
  [[maybe_unused]] void static addFont(int number, float fontScale = 40.0f){

    // general needed stuff for loading fonts and icons
    auto& io = ImGui::GetIO();
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;

    switch(number){
      case rabbitHighwaySignBoldCaps:
        io.Fonts->Clear();
        io.Fonts->AddFontFromFileTTF("fonts/Rabbid-Highway-Sign-Bold-Caps.ttf", fontScale);
        io.Fonts->AddFontFromFileTTF( "fonts/fa-solid-900.ttf", fontScale, &icons_config, icons_ranges );
        break;
      case robotoBold:
        io.Fonts->Clear();
        io.Fonts->AddFontFromFileTTF("fonts/Roboto-Bold.ttf", fontScale);
        io.Fonts->AddFontFromFileTTF( "fonts/fa-solid-900.ttf", fontScale, &icons_config, icons_ranges );
        break;
      case millesHandwriting:
        io.Fonts->Clear();
        io.Fonts->AddFontFromFileTTF("fonts/Milles-Handwriting.ttf", fontScale);
        io.Fonts->AddFontFromFileTTF( "fonts/fa-solid-900.ttf", fontScale, &icons_config, icons_ranges );
        break;
      default: break;
    }
  }

  /**
   * changes the size to the maximum
   */
  [[maybe_unused]] void static setFontHuge(){
    ImGui::SetWindowFontScale(1.0f);
  }

  /**
   * changes the size to big
   */
  [[maybe_unused]] void static setFontBig(){
    ImGui::SetWindowFontScale(0.8f);
  }

  /**
   * changes the size to normal
   */
  [[maybe_unused]] void static setFontNormal(){
    ImGui::SetWindowFontScale(0.5f);
  }

  /**
   * changes the size to small
   */
  [[maybe_unused]] void static setFontSmall(){
    ImGui::SetWindowFontScale(0.2f);
  }
}

#endif //GUIBACKEND_FONTHOLDER_HPP_
