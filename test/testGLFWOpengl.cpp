#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <imGuiCustom.h>

TEST_CASE("Create Context")
{
    imGuiCustom backend;
    backend.fullscreen = false;
    backend.createWindow();

    SUBCASE("Create/destroy Window and check control values")
    {
        CHECK(backend.checkWindow() == true);
        backend.destroyWindow();
        CHECK(backend.checkWindow() == false);
        backend.createWindow();
        CHECK(backend.checkWindow() == true);
    }

    SUBCASE("Check standard rendering")
    {
      imGuiCustom::createFrame();
      ImGui::Begin("Hello, world!");
      ImGui::Text("This is some useful text.");
      ImGui::End();
      backend.renderFrame();
    }
}
