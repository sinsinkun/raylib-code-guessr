#include <iostream>
#include <random>
#include <string>
#include <raylib.h>
#include "answer.hpp"

using namespace App;

void AnswerBox::init() {
  _generateAns();
}

void AnswerBox::update(const float dtime, const Vector2& screenCenter, int& inputc, int (&input)[4], int& score) {
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
      // debug: print answer
      std::cout << "Ans: [ ";
      for (int i=0; i<4; i++) {
        std::cout << input[i] << "/" << ans[i] << " ";
      }
      std::cout << "]" << std::endl;
      // calculate correctness
      _dt += dtime;
      _state = ABFlash;
      int correctness = 0;
      for (int i=0; i<4; i++) {
        if (input[i] == ans[i]) correctness++;
      }
      switch (correctness) {
        case 0:
          fcolor = AB_BG0;
          break;
        case 1:
          fcolor = AB_BG1;
          break;
        case 2:
          fcolor = AB_BG2;
          break;
        case 3:
          fcolor = AB_BG3;
          break;
        case 4:
          fcolor = AB_BG4;
          _generateAns();
          score++;
          break;
        default:
          fcolor = AB_BG;
          break;
      }
    } else if (_dt >= 1.1f) {
      // clear input
      inputc = 0;
      // reset
      _dt = 0.0f;
      _state = ABNone;
    } else {
      _dt += dtime;
    }
  }
}

void AnswerBox::render() {
  // switch color based on animation + time
  Color local = AB_BG;
  if (_state == ABFlash) {
    if (_dt >= 0.8) local = fcolor;
    else if (_dt >= 0.6) local = AB_BG;
    else if (_dt >= 0.4) local = fcolor;
    else if (_dt >= 0.2) local = AB_BG;
    else local = fcolor;
  }
  DrawRectangle(pos.x + 5, pos.y + 5, size.x, size.y, AB_SHADOW);
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
