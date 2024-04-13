#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>
#include "app.hpp"

using namespace App;

void EventLoop::update() {
  _updateSystem();
}

void EventLoop::render() {
  BeginDrawing();
    ClearBackground(BLACK);
    if (IsWindowFocused()) {
      // draw background
      float delta = fps%255;
      DrawRectangle(0, 0, screenW, screenH, (Color){ 55, 55, 120, 255 });
    } else {
      DrawText("Pay Attention to me", 10, screenH - 30, 20, RED);
    }
    // draw FPS overlay
    std::string fpst = std::to_string(fps);
    std::string fpstxt = "FPS: ";
    fpstxt.append(fpst);
    DrawTextEx(font, fpstxt.c_str(), (Vector2){10.0, 10.0}, 20, 0, GREEN);
  EndDrawing();
}

void EventLoop::_updateSystem() {
  fps = GetFPS();
  screenW = GetScreenWidth();
  screenH = GetScreenHeight();
  elapsed = GetTime();
  screenCenter = { (float)screenW/2, (float)screenH/2 };
  mousePos = GetMousePosition();
}
