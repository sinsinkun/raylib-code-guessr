#include <iostream>
#include <string>
#include <raylib.h>
#include "answer.hpp"

using namespace App;

void AnswerBox::update(const Vector2& screenCenter, int& inputc, int (&input)[4]) {
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
    if (_framec == 0) {
      std::cout << "TODO: compare input to answer" << std::endl;
      // TODO: change bg to RED for incorrect, GREEN for correct
      bg = {200, 80, 80, 255};
      _framec++;
    } else if (_framec == 60) {
      // clear input
      inputc = 0;
      // reset
      _framec = 0;
      bg = {100, 100, 100, 255};
    } else {
      // delay
      _framec++;
    }
  }
}

void AnswerBox::render() {
  DrawRectangle(pos.x + 5, pos.y + 5, size.x, size.y, shadow);
  DrawRectangle(pos.x, pos.y, size.x, size.y, bg);
  DrawText(inputDisplay.c_str(), pos.x + 35, pos.y + 5, 55, WHITE);
}