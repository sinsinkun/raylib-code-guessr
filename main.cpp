#include <iostream>
#include <raylib.h>
#include "app.hpp"

#define GLSL_VERSION 330

/// @brief Entry point
/// @param argc arguments count
/// @param argv arguments array
/// @return exit code
int main(int argc, char* argv[]) {
  // --- INITIALIZATION ---
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(400, 600, "Code Guessr");
  // InitAudioDevice();
  SetWindowMinSize(400, 300);
  Image icon = LoadImage("assets/logo.png");
  SetWindowIcon(icon);
  SetTargetFPS(120);
  // SetMasterVolume(0.2);

  App::EventLoop e;
  e.init();

  // --- EVENT LOOP ---
  std::cout << "Starting..." << std::endl;
  while (!WindowShouldClose()) {
    e.update();
    e.render();
  }
  std::cout << "Exiting..." << std::endl;

  // --- CLEAN UP ---
  // CloseAudioDevice();
  e.cleanup();
  CloseWindow();
}
