//
// Created by kim on 2/8/21.
//

#include "benchmark/benchmark.h"
#include <imGuiCustom.h>
#include "fontStorage.hpp"

static void BM_createDestroy(benchmark::State& state) {
  // Perform setup here
  imGuiCustom backend;
  backend.fullscreen = false;
  for (auto _ : state) {
    // This code gets timed
    backend.createWindow();
    backend.destroyWindow();
  }
}

static void BM_emptyRenderWindowed(benchmark::State& state) {
  // Perform setup here
  imGuiCustom backend;
  backend.fullscreen = false;
  backend.createWindow();
  for (auto _ : state) {
    // This code gets timed
    imGuiCustom::createFrame();
    ImGui::Begin("Hello, world!");
    ImGui::End();
    backend.renderFrame();
  }
  backend.destroyWindow();
}

static void BM_emptyRenderFullscreen(benchmark::State& state) {
  // Perform setup here
  imGuiCustom backend;
  backend.fullscreen = true;
  backend.createWindow();
  for (auto _ : state) {
    // This code gets timed
    imGuiCustom::createFrame();
    ImGui::Begin("Hello, world!");
    ImGui::End();
    backend.renderFrame();
  }
  backend.destroyWindow();
}

static void BM_renderText(benchmark::State& state) {
  // Perform setup here
  imGuiCustom backend;
  backend.fullscreen = false;
  backend.createWindow();
  for (auto _ : state) {
    // This code gets timed
    imGuiCustom::createFrame();
    ImGui::Begin("Hello, world!");
    ImGui::Text("This is some useful text.");
    ImGui::End();
    backend.renderFrame();
  }
  backend.destroyWindow();
}

static void BM_renderTextWithFontChange(benchmark::State& state) {
  // Perform setup here
  imGuiCustom backend;
  backend.fullscreen = false;
  backend.createWindow();
  for (auto _ : state) {
    // This code gets timed
    imGuiCustom::createFrame();
    ImGui::Begin("Hello, world!");
    fontStorage::setFontNormal();
    ImGui::Text("This is some useful text.");
    fontStorage::setFontSmall();
    ImGui::End();
    backend.renderFrame();
  }
  backend.destroyWindow();
}


// Register the function as a benchmark
BENCHMARK(BM_createDestroy);
BENCHMARK(BM_emptyRenderWindowed);
BENCHMARK(BM_emptyRenderFullscreen);
BENCHMARK(BM_renderText);
BENCHMARK(BM_renderTextWithFontChange);
// Run the benchmark
BENCHMARK_MAIN();