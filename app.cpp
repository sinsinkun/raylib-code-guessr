#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>
#include "app.hpp"
#include "button.hpp"

using namespace App;

void EventLoop::init() {
  // initialize font
  font = LoadFontEx("assets/roboto.ttf", 60, 0, 0);
  // Generate mipmap levels to use bi/trilinear filtering
  GenTextureMipmaps(&font.texture);
  SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

  // initialize button 1 
  Asset a1;
  a1.type = AssetType::AButton;
  a1.btn = new Button{1, screenCenter.x - 73.0f, screenCenter.y - 40.0f};
  a1.btn->text = "1";
  assets.push_back(a1);

  // initialize button 2
  Asset a2;
  a2.type = AssetType::AButton;
  a2.btn = new Button{2, screenCenter.x + 13.0f, screenCenter.y - 40.0f};
  a2.btn->text = "2";
  assets.push_back(a2);
}

void EventLoop::update() {
  _updateSystem();
  // take inputs
  int mouseHoverCount = 0;
  bool mouseClicked = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
  // update assets
  for (Asset a: assets) {
    switch (a.type) {
      case AssetType::AButton:
        if (a.btn->id == 1) a.btn->updatePos((Vector2){screenCenter.x - 73.0f, screenCenter.y - 40.0f});
        else if (a.btn->id == 2) a.btn->updatePos((Vector2){screenCenter.x + 13.0f, screenCenter.y - 40.0f});
        a.btn->updateState(mousePos, mouseClicked, mouseHoverCount);
        if (a.btn->state == ButtonState::Just_Clicked) {
          std::cout << "Clicked button " << a.btn->id << std::endl;
        }
        break;
      case AssetType::ANone:
      default:
        break;
    }
  }
  // update mouse state
  if (mouseHoverCount > 0) SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
  else SetMouseCursor(MOUSE_CURSOR_ARROW);
}

void EventLoop::render() {
  BeginDrawing();
    ClearBackground(BLACK);
    if (IsWindowFocused()) {
      // draw background
      DrawRectangle(0, 0, screenW, screenH, (Color){80, 120, 120, 255});

      // draw assets
      for (Asset a: assets) {
        switch (a.type) {
          case AssetType::AButton:
            a.btn->render();
            break;
          case AssetType::ANone:
          default:
            break;
        }
      }
    } else {
      DrawText("Pay Attention to me", screenCenter.x - 200, screenCenter.y - 40, 40, RED);
    }
    // draw FPS overlay
    _drawFps();
  EndDrawing();
}

void EventLoop::cleanup() {
  // destroy assets
  for (Asset a: assets) {
    switch (a.type) {
      case AssetType::AButton:
        delete a.btn;
        break;
      case AssetType::ANone:
      default:
        break;
    }
  }
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
