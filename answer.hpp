#pragma once
#include <string>
#include <raylib.h>

namespace App {

  enum AnswerBoxAnimationState {
    ABNone,
    ABRight,
    ABWrong,
  };

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
      Color bgRed = {200, 80, 80, 255};
      Color bgGreen = {80, 200, 80, 255};
      Color shadow = {0, 0, 0, 255};
      int ans[4] = {2, 1, 1, 4};
      std::string inputDisplay = "";
      // methods
      void init();
      void update(const float dtime, const Vector2& screenCenter, int& inputc, int (&input)[4]);
      void render();
    private:
      float _dt = 0.0f;
      AnswerBoxAnimationState _anim = ABNone;
      int animFrame = 0;
      void _generateAns();
  };
}