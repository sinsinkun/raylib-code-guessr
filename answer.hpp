#pragma once
#include <string>
#include <raylib.h>

namespace App {

  enum AnswerBoxState {
    ABNone,
    ABFlash
  };

  const Color AB_BG = {100, 100, 100, 255};
  const Color AB_BG0 = {200, 80, 80, 255};
  const Color AB_BG1 = {200, 100, 40, 255};
  const Color AB_BG2 = {200, 160, 40, 255};
  const Color AB_BG3 = {180, 200, 20, 255};
  const Color AB_BG4 = {80, 200, 80, 255};
  const Color AB_SHADOW = {0, 0, 0, 255};

  class AnswerBox {
    public:
      // constructors
      AnswerBox(float x, float y) {
        pos = (Vector2){x, y};
      };
      // state
      Vector2 pos = {5, 5};
      Vector2 size = {260, 60};
      Color fcolor = AB_BG;
      int ans[4] = {0, 0, 0, 0};
      std::string inputDisplay = "";
      // methods
      void init();
      void update(const float dtime, const Vector2& screenCenter, int& inputc, int (&input)[4], int& score);
      void render();
    private:
      float _dt = 0.0f;
      AnswerBoxState _state = ABNone;
      void _generateAns();
  };
}