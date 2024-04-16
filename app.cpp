#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>
#include "app.hpp"
#include "button.hpp"
#include "answer.hpp"

using namespace App;

void EventLoop::init() {
  // initialize font
  font = LoadFontEx("assets/roboto.ttf", 60, 0, 0);
  // Generate mipmap levels to use bi/trilinear filtering
  GenTextureMipmaps(&font.texture);
  SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

  // initialize buttons
  for (int i=1; i<10; i++) {
    std::cout << "instantiated button " << i << std::endl;
    int di = i - 1;
    int dj = i / 3;
    float dx = screenCenter.x - 105.0f + (float)(di%3) * 75.0f;
    float dy = screenCenter.y - 20.0f + (float)dj * 75.0f;
    Asset a;
    a.type = AssetType::AButton;
    a.btn = new Button{i, dx, dy };
    a.btn->text = std::to_string(i);
    assets.push_back(a);
  }

  // initialize answer box
  Asset ab;
  ab.type = AssetType::AAnsBox;
  ab.ansBox = new AnswerBox{0, 0};
  ab.ansBox->init();
  assets.push_back(ab);
}

void EventLoop::update() {
  _updateSystem();
  // take inputs
  int mouseHoverCount = 0;
  bool mouseClicked = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
  // update assets
  for (Asset a: assets) {
    switch (a.type) {
      case AssetType::AButton: {
        int di = a.btn->id - 1;
        int dj = di / 3;
        float dx = screenCenter.x - 105.0f + (float)(di%3) * 75.0f;
        float dy = screenCenter.y - 20.0f + (float)dj * 75.0f;
        a.btn->updatePos((Vector2){dx, dy});
        a.btn->updateState(mousePos, mouseClicked, mouseHoverCount);
        if (a.btn->state == ButtonState::Just_Clicked) {
          // update input
          if (inputc < 4) {
            input[inputc] = a.btn->id;
            inputc++;
          }
        }
        break;
      }
      case AssetType::AAnsBox:
        a.ansBox->update(deltaTime, screenCenter, inputc, input, score);
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
          case AssetType::AAnsBox:
            a.ansBox->render();
            break;
          case AssetType::ANone:
          default:
            break;
        }
      }
      
      // draw score
      std::string strscore = "Solved: ";
      std::string strscorenum = std::to_string(score);
      strscore.append(strscorenum);
      DrawTextEx(font, strscore.c_str(), (Vector2){screenCenter.x - 60, screenCenter.y - 200}, 34, 0, BLACK);

    } else {
      DrawText("Pay Attention to me", screenCenter.x - 170, screenCenter.y - 40, 34, RED);
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
      case AssetType::AAnsBox:
        delete a.ansBox;
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
  deltaTime = GetFrameTime();
}

void EventLoop::_drawFps() {
  std::string fpst = std::to_string(fps);
  std::string fpstxt = "FPS: ";
  fpstxt.append(fpst);
  DrawTextEx(font, fpstxt.c_str(), (Vector2){2.0, 2.0}, 20, 0, GREEN);
}
