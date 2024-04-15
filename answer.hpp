#pragma once
#include <string>
#include <raylib.h>

namespace App {
  class AnswerBox {
    public:
      // constructors
      AnswerBox(float x, float y) {
        pos = (Vector2){x, y};
      };
      // state
      Vector2 pos = {5, 5};
      Vector2 size = {260, 60};
      Color bg = {100, 100, 100, 255};
      Color shadow = {0, 0, 0, 255};
      int ans[4] = {0, 0, 0, 0};
      std::string inputDisplay = "";
      // methods
      void update(const Vector2& screenCenter, int& inputc, int (&input)[4]);
      void render();
    private:
      int _framec = 0;
  };
}