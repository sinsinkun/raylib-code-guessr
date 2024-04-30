#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>
#include <raymath.h>
#include "app.hpp"

using namespace App;

#pragma region Box
Box::Box(int iid, Vector2 ipos, Vector2 isize, Color icolor) {
  id = iid;
  position = ipos;
  size = isize;
  color = icolor;
  body = { ipos.x - isize.x/2, ipos.y - isize.y/2, isize.x, isize.y };
  shader = LoadShader("assets/box.vs", "assets/box.fs");
  target = LoadRenderTexture(isize.x, isize.y);
}

Box::Box(int iid, Vector2 ipos, Vector2 isize, Color icolor, float irot) {
  id = iid;
  position = ipos;
  size = isize;
  rotation = irot;
  color = icolor;
  body = {
    ipos.x - isize.x/2 * std::cos(irot * DEG2RAD) + isize.y/2 * std::sin(irot * DEG2RAD),
    ipos.y - isize.x/2 * std::sin(irot * DEG2RAD) - isize.y/2 * std::cos(irot * DEG2RAD),
    isize.x,
    isize.y
  };
  shader = LoadShader("assets/box.vs", "assets/box.fs");
  target = LoadRenderTexture(isize.x, isize.y);
}

void Box::update(Vector2 pos, float rot) {
  position = pos;
  rotation = rot;
  body.x = pos.x - size.x/2 * std::cos(rot * DEG2RAD) + size.y/2 * std::sin(rot * DEG2RAD);
  body.y = pos.y - size.x/2 * std::sin(rot * DEG2RAD) - size.y/2 * std::cos(rot * DEG2RAD);
}

void Box::updateTexture() {
  BeginTextureMode(target);
    BeginShaderMode(shader);
      DrawRectangle(0, 0, size.x, size.y, color);
    EndShaderMode();
  EndTextureMode();
}

void Box::render() {
  DrawRectanglePro(body, (Vector2){0, 0}, rotation, color);
}

void Box::renderNormal() {
  Rectangle source = {0.0f, 0.0f, size.x, size.y};
  DrawTexturePro(target.texture, source, body, (Vector2){0.0f, 0.0f}, rotation, WHITE);
}

void Box::cleanup() {
  UnloadShader(shader);
  UnloadRenderTexture(target);
}
#pragma endregion Box


#pragma region Light
Light::Light(int iid, Vector2 ipos, float iradius, Color icolor) {
  id = iid;
  position = ipos;
  radius = iradius;
  color = icolor;
}

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
  Box box2 = {2, (Vector2){200.0f, 400.0f}, (Vector2){160.0f, 80.0f}, BLUE, 10.0f};
  boxes.push_back(box2);
  Box box3 = {3, (Vector2){600.0f, 400.0f}, (Vector2){160.0f, 80.0f}, GREEN, -10.0f};
  boxes.push_back(box3);

  Light light1 = {1, (Vector2){300.0f, 300.0f}, 300.0f, PURPLE};
  lights.push_back(light1);
}

void EventLoop::update() {
  _updateSystem();
  // take inputs
  int mouseHoverCount = 0;
  bool mouseClicked = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

  Vector2 move = {0.0f, 0.0f};
  if (IsKeyDown(KEY_A)) move.x -= 1.0f;
  if (IsKeyDown(KEY_D)) move.x += 1.0f;
  if (IsKeyDown(KEY_W)) move.y -= 1.0f;
  if (IsKeyDown(KEY_S)) move.y += 1.0f;

  // update assets
  for (Box& b: boxes) {
    b.updateTexture();
  }
  for (Light& l: lights) {
    Vector2 abs = { l.position.x + move.x, l.position.y + move.y };
    l.update(abs);
  }

  // update mouse state
  if (mouseHoverCount > 0) SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
  else SetMouseCursor(MOUSE_CURSOR_ARROW);
}

void EventLoop::render() {
  // TODO: color buffer
  // TODO: light buffer/normal buffer
  BeginDrawing();
    ClearBackground(BLACK);
    // draw background/ambient light
    DrawRectangle(0, 0, screenW, screenH, (Color){20,10,20,255});

    // draw assets
    for (Box& b: boxes) {
      b.renderNormal();
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
  for (Box& b: boxes) {
    b.cleanup();
  }
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
