#include <iostream>
#include <raylib.h>

#define GLSL_VERSION 330

enum Scene {
  menu,
  game,
};

struct EventLoop {
  public:
    // assets
    Scene scene = Scene::menu;
    // global state
    int screenW = 0;
    int screenH = 0;
    Vector2 screenCenter = { 0.0, 0.0 };
    int fps = 0;
    double elapsed = 0.0;
    Vector2 mousePos = { 0.0, 0.0 };
    // scene declarations
    void root(); // root event loop
    void menu();
    void game();
} eventLoop;

void EventLoop::root() {
  // --- UPDATE GLOBAL STATE ---
  eventLoop.screenW = GetScreenWidth();
  eventLoop.screenH = GetScreenHeight();
  eventLoop.fps = GetFPS();
  eventLoop.elapsed = GetTime();
  eventLoop.mousePos = GetMousePosition();
  eventLoop.screenCenter = { (float)eventLoop.screenW/2, (float)eventLoop.screenH/2 };

  switch(scene) {
    case Scene::game:
      game();
      break;
    case Scene::menu:
    default:
      menu();
      break;
  }
}

void EventLoop::menu() {
  // --- UPDATE STATE ---
  // show cursor
  if (IsCursorHidden()) {
    ShowCursor();
  }

  // --- DRAW TO SCREEN ---
  BeginDrawing();
    ClearBackground(BLACK);
    if (IsWindowFocused()) {
      // draw background
      DrawRectangle(0, 0, eventLoop.screenW, eventLoop.screenH, BLUE);
      // draw text overlay
      DrawText("Hello there", 10, 10, 20, GREEN);
    } else {
      DrawText("Pay Attention to me", 10, 10, 20, RED);
    }
  EndDrawing();

}

void EventLoop::game() {
  // TODO
  // --- DRAW TO SCREEN ---
  BeginDrawing();
    ClearBackground(BLACK);
  EndDrawing();
}

/// @brief Entry point
/// @param argc arguments count
/// @param argv arguments array
/// @return exit code
int main(int argc, char* argv[]) {
  // --- INITIALIZATION ---
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(800, 600, "Test Title Please Ignore");
  // InitAudioDevice();
  SetWindowMinSize(400, 300);
  SetTargetFPS(60);
  // SetMasterVolume(0.2);

  // --- EVENT LOOP ---
  std::cout << "Starting..." << std::endl;
  while (!WindowShouldClose()) {
    eventLoop.root();
  }
  std::cout << "Exiting..." << std::endl;

  // --- CLEAN UP ---
  // CloseAudioDevice();
  CloseWindow();
}
