#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>
#include "app.hpp"

using namespace App;

#pragma region Box
void Box::update(Vector2 pos, float rot) {
  position = pos;
  rotation = rot;
  body.x = pos.x - size.x/2 * std::cos(rot * DEG2RAD) + size.y/2 * std::sin(rot * DEG2RAD);
  body.y = pos.y - size.x/2 * std::sin(rot * DEG2RAD) - size.y/2 * std::cos(rot * DEG2RAD);
}

void Box::render() {
  DrawRectanglePro(body, (Vector2){0, 0}, rotation, color);
}
#pragma endregion Box


#pragma region Light
void Light::update(Vector2 pos) {
  position = pos;
}

void Light::render() {
  DrawCircle(position.x, position.y, 4.0f, color);
  DrawCircleLines(position.x, position.y, radius, (Color){color.r, color.g, color.b, 100});
}
#pragma endregion Light


#pragma region EventLoop
void EventLoop::init() {
  // initialize font
  font = LoadFontEx("assets/roboto.ttf", 60, 0, 0);
  // Generate mipmap levels to use bi/trilinear filtering
  GenTextureMipmaps(&font.texture);
  SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

  // initialize assets
  Box box1 = {1, (Vector2){400.0f, 100.0f}, (Vector2){200.0f, 100.0f}, RED};
  boxes.push_back(box1);
  Box box2 = {2, (Vector2){200.0f, 400.0f}, (Vector2){100.0f, 50.0f}, BLUE, 10.0f};
  boxes.push_back(box2);
  Box box3 = {3, (Vector2){600.0f, 400.0f}, (Vector2){100.0f, 50.0f}, GREEN, -10.0f};
  boxes.push_back(box3);

  Light light1 = {1, (Vector2){300.0f, 300.0f}, 300.0f, BLUE};
  lights.push_back(light1);
}

void EventLoop::update() {
  _updateSystem();
  // take inputs
  int mouseHoverCount = 0;
  bool mouseClicked = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
  // update assets
  // for (Box& b: boxes) {
  //   b.update();
  // }
  // for (Light& l: lights) {
  //   l.update();
  // }

  // update mouse state
  if (mouseHoverCount > 0) SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
  else SetMouseCursor(MOUSE_CURSOR_ARROW);
}

void EventLoop::render() {
  // TODO: color buffer
  // TODO: light buffer/normal buffer
  BeginDrawing();
    ClearBackground(BLACK);

    // draw assets
    for (Box& b: boxes) {
      b.render();
    }
    for (Light& l: lights) {
      l.render();
    }
    
    // draw FPS overlay
    _drawFps();
  EndDrawing();
}

void EventLoop::cleanup() {
  // destroy assets
}

void EventLoop::_updateSystem() {
  fps = GetFPS();
  screenW = GetScreenWidth();
  screenH = GetScreenHeight();
  elapsed = GetTime();
  screenCenter = { (float)screenW/2, (float)screenH/2 };
  mousePos = GetMousePosition();
  deltaTime = GetFrameTime();
}

void EventLoop::_drawFps() {
  std::string fpst = std::to_string(fps);
  std::string fpstxt = "FPS: ";
  fpstxt.append(fpst);
  DrawTextEx(font, fpstxt.c_str(), (Vector2){2.0, 2.0}, 20, 0, GREEN);
}
#pragma endregion EventLoop
