#include <iostream>
#include <random>
#include <string>
#include <raylib.h>
#include "answer.hpp"

using namespace App;

void AnswerBox::init() {
  _generateAns();
}

void AnswerBox::update(const float dtime, const Vector2& screenCenter, int& inputc, int (&input)[4]) {
  // update position
  pos.x = screenCenter.x - 130;
  pos.y = screenCenter.y - 130;
  // update text
  std::string is = "";
  for (int i=0; i<inputc; i++) {
    is.append("* ");
  }
  inputDisplay = is;
  
  if (inputc == 4) {
    if (_dt == 0.0f) {
      _dt += dtime;
      bool correct = true;
      for (int i=0; i<4; i++) {
        if (input[i] != ans[i]) correct = false;
      }
      if (correct) {
        _anim = ABRight;
        _generateAns();
      } else _anim = ABWrong;
    } else if (_dt >= 1.1f) {
      // clear input
      inputc = 0;
      // reset
      _dt = 0.0f;
      _anim = ABNone;
    } else {
      _dt += dtime;
    }
  }
}

void AnswerBox::render() {
  // switch color based on animation + time
  Color local = bg;
  if (_anim == ABRight) {
    if (_dt >= 0.8) local = bgGreen;
    else if (_dt >= 0.6) local = bg;
    else if (_dt >= 0.4) local = bgGreen;
    else if (_dt >= 0.2) local = bg;
    else local = bgGreen;
  }
  if (_anim == ABWrong) {
    if (_dt >= 0.8) local = bgRed;
    else if (_dt >= 0.6) local = bg;
    else if (_dt >= 0.4) local = bgRed;
    else if (_dt >= 0.2) local = bg;
    else local = bgRed;
  }
  DrawRectangle(pos.x + 5, pos.y + 5, size.x, size.y, shadow);
  DrawRectangle(pos.x, pos.y, size.x, size.y, local);
  DrawText(inputDisplay.c_str(), pos.x + 35, pos.y + 5, 55, WHITE);
}

void AnswerBox::_generateAns() {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(1, 9);
  for (int i=0; i<4; i++) {
    ans[i] = dist(rng);
  }
}