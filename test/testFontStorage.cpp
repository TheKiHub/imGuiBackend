//
// Created by kim on 2/9/21.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <imGuiCustom.h>
#include "fontStorage.hpp"

TEST_CASE("Load all fonts")
{
    imGuiCustom backend;
    backend.fullscreen = false;
    backend.createWindow();

    SUBCASE("robotoBold")
    {
    fontStorage::addFont(fontStorage::robotoBold);
    }

    SUBCASE("MillesHandwriting")
    {
    fontStorage::addFont(fontStorage::millesHandwriting);
    }

    SUBCASE("rabbitHighwaySignBoldCaps")
    {
    fontStorage::addFont(fontStorage::rabbitHighwaySignBoldCaps);
    }

    SUBCASE("check font scale")
    {
      fontStorage::addFont(fontStorage::robotoBold);
      imGuiCustom::createFrame();
      fontStorage::setFontSmall();
      auto beforeWidth = ImGui::GetFontSize();
      fontStorage::setFontNormal();
      CHECK(beforeWidth < ImGui::GetFontSize());
      beforeWidth = ImGui::GetFontSize();
      fontStorage::setFontBig();
      CHECK(beforeWidth < ImGui::GetFontSize());
      beforeWidth = ImGui::GetFontSize();
      fontStorage::setFontHuge();
      CHECK(beforeWidth < ImGui::GetFontSize());
    }

    backend.destroyWindow();
}