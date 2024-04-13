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
      DrawRectangle(0, 0, screenW, screenH, (Color){ 55, 55, 120, 255 });

      // draw button
      Rectangle rect = {50.0, 50.0, 120.0, 60.0};
      Rectangle rectShadow = {52.0, 50.0, 122.0, 65.0};
      DrawRectangleRounded(rectShadow, 0.5, 8, BLACK);
      DrawRectangleRounded(rect, 0.5, 8, RED);
      DrawText("Button", 65.0, 65.0, 28, WHITE);
    } else {
      DrawText("Pay Attention to me", screenCenter.x - 200, screenCenter.y - 40, 40, RED);
    }
    // draw FPS overlay
    _drawFps();
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

void EventLoop::_drawFps() {
  std::string fpst = std::to_string(fps);
  std::string fpstxt = "FPS: ";
  fpstxt.append(fpst);
  DrawTextEx(font, fpstxt.c_str(), (Vector2){10.0, 10.0}, 20, 0, GREEN);
}
