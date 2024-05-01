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
  SetTextureWrap(target.texture, TEXTURE_WRAP_CLAMP);
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
  SetTextureWrap(target.texture, TEXTURE_WRAP_CLAMP);
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
Light::Light(int iid, Vector2 ipos, float iradius, Color icolor, float iintensity) {
  id = iid;
  position = ipos;
  radius = iradius;
  color = icolor;
  intensity = iintensity;
  // load shader
  shader = LoadShader("assets/light.vs", "assets/light.fs");
  shaderLoc[0] = GetShaderLocation(shader, "lightPos");
  shaderLoc[1] = GetShaderLocation(shader, "lightIntensity");
  shaderLoc[2] = GetShaderLocation(shader, "lightRadius");
  shaderLoc[3] = GetShaderLocation(shader, "lightColor");
  // load buffer
  lightBuffer = LoadRenderTexture(800, 600);
  SetTextureWrap(lightBuffer.texture, TEXTURE_WRAP_CLAMP);
}

void Light::update(Vector2 pos) {
  position = pos;
}

void Light::updateShader(int screenW, int screenH) {
  // update render textures
  if (lightBuffer.texture.width != screenW || lightBuffer.texture.height != screenH) {
    UnloadRenderTexture(lightBuffer);
    lightBuffer = LoadRenderTexture(screenW, screenH);
    SetTextureWrap(lightBuffer.texture, TEXTURE_WRAP_CLAMP);
  }
  float pos[2] = { position.x, (float)screenH - position.y };
  float clr[3] = { (float)color.r / 255, (float)color.g / 255, (float)color.b / 255 };
  SetShaderValue(shader, shaderLoc[0], pos, SHADER_UNIFORM_VEC2);
  SetShaderValue(shader, shaderLoc[1], &intensity, SHADER_UNIFORM_FLOAT);
  SetShaderValue(shader, shaderLoc[2], &radius, SHADER_UNIFORM_FLOAT);
  SetShaderValue(shader, shaderLoc[3], clr, SHADER_UNIFORM_VEC3);
}

void Light::render() {
  DrawCircle(position.x, position.y, 4.0f, color);
  DrawCircleLines(position.x, position.y, radius, (Color){color.r, color.g, color.b, 50});
}

void Light::cleanup() {
  UnloadShader(shader);
  UnloadRenderTexture(lightBuffer);
}
#pragma endregion Light


#pragma region EventLoop
void EventLoop::init() {
  // initialize font
  font = LoadFontEx("assets/roboto.ttf", 60, 0, 0);
  // Generate mipmap levels to use bi/trilinear filtering
  GenTextureMipmaps(&font.texture);
  SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

  // initialize g-buffer
  gBufferColor = LoadRenderTexture(800, 600);
  SetTextureWrap(gBufferColor.texture, TEXTURE_WRAP_CLAMP);
  gBufferNormal = LoadRenderTexture(800, 600);
  SetTextureWrap(gBufferNormal.texture, TEXTURE_WRAP_CLAMP);

  // initialize assets
  Box box1 = {1, (Vector2){400.0f, 100.0f}, (Vector2){200.0f, 100.0f}, RED};
  boxes.push_back(box1);
  Box box2 = {2, (Vector2){200.0f, 400.0f}, (Vector2){160.0f, 80.0f}, BLUE, 10.0f};
  boxes.push_back(box2);
  Box box3 = {3, (Vector2){600.0f, 400.0f}, (Vector2){160.0f, 80.0f}, GREEN, -10.0f};
  boxes.push_back(box3);

  Light light1 = {1, (Vector2){300.0f, 200.0f}, 300.0f, WHITE, 0.5};
  lights.push_back(light1);
  Light light2 = {2, (Vector2){500.0f, 500.0f}, 100.0f, YELLOW, 0.8};
  lights.push_back(light2);
  Light light3 = {2, (Vector2){100.0f, 500.0f}, 200.0f, PURPLE, 0.5};
  lights.push_back(light3);
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
    Vector2 absPos = { l.position.x + move.x, l.position.y + move.y };
    l.update(absPos);
    l.updateShader(screenW, screenH);
  }

  // update render textures
  if (gBufferColor.texture.width != screenW || gBufferColor.texture.height != screenH) {
    UnloadRenderTexture(gBufferColor);
    gBufferColor = LoadRenderTexture(screenW, screenH);
    SetTextureWrap(gBufferColor.texture, TEXTURE_WRAP_CLAMP);
    UnloadRenderTexture(gBufferNormal);
    gBufferNormal = LoadRenderTexture(screenW, screenH);
    SetTextureWrap(gBufferNormal.texture, TEXTURE_WRAP_CLAMP);
  }

  // update mouse state
  if (mouseHoverCount > 0) SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
  else SetMouseCursor(MOUSE_CURSOR_ARROW);
}

void EventLoop::render() {
  Rectangle src = {0, 0, (float)gBufferColor.texture.width, -(float)gBufferColor.texture.height};
  Rectangle dest = {0, 0, (float)screenW, (float)screenH};
  // color buffer
  BeginTextureMode(gBufferColor);
    ClearBackground(BLACK);
    // draw background/ambient light
    DrawRectangle(0, 0, screenW, screenH, (Color){200,100,100,255});
    for (Box& b: boxes) {
      b.render();
    }
  EndTextureMode();
  // normal buffer
  BeginTextureMode(gBufferNormal);
    ClearBackground(BLACK);
    for (Box& b: boxes) {
      b.renderNormal();
    }
  EndTextureMode();
  // generate light buffers
  for (Light& l: lights) {
    BeginTextureMode(l.lightBuffer);
      BeginShaderMode(l.shader);
        DrawTexturePro(gBufferNormal.texture, src, dest, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
      EndShaderMode();
    EndTextureMode();
  }
  // add all light buffers together
  BeginTextureMode(gBufferNormal);
    ClearBackground(BLACK);
  EndTextureMode();
  for (Light& l: lights) {
    BeginTextureMode(gBufferNormal);
      DrawTexturePro(gBufferNormal.texture, src, dest, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
      BeginBlendMode(BLEND_ADDITIVE);
        DrawTexturePro(l.lightBuffer.texture, src, dest, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
      EndBlendMode();
    EndTextureMode();
  }

  BeginDrawing();
    ClearBackground(BLACK);
    // draw color texture
    DrawTexturePro(gBufferColor.texture, src, dest, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
    // multiply by light
    BeginBlendMode(BLEND_MULTIPLIED);
      DrawTexturePro(gBufferNormal.texture, src, dest, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
    EndBlendMode();

    // draw lights
    for (Light& l: lights) {
      l.render();
    }
    // _drawDebug();
    // draw FPS overlay
    _drawFps();
  EndDrawing();
}

void EventLoop::cleanup() {
  // destroy assets
  for (Box& b: boxes) {
    b.cleanup();
  }
  for (Light& l: lights) {
    l.cleanup();
  }
  UnloadRenderTexture(gBufferColor);
  UnloadRenderTexture(gBufferNormal);
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

void EventLoop::_drawDebug() {
  Rectangle src = {0, 0, (float)gBufferColor.texture.width, -(float)gBufferColor.texture.height};
  Rectangle dest = {0, 0, (float)screenW/4, (float)screenH/4};
  DrawTexturePro(gBufferNormal.texture, src, dest, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
}
#pragma endregion EventLoop
