#include <raylib.h>
#include "button.hpp"

using namespace App;

void Button::update(Vector2 mousePos, bool mouseClicked, int& mouseHoverCount) {
  // determine hover state
  bool xin = (mousePos.x > pos.x) && (mousePos.x < pos.x + size.x);
  bool yin = (mousePos.y > pos.y) && (mousePos.y < pos.y + size.y);
  if (xin && yin) {
    _isHovered = true;
    mouseHoverCount++;
  }
  else _isHovered = false;

  // determine click state
  if (_isHovered && !_isClicked && mouseClicked) {
    state = ButtonState::Just_Clicked;
    _isClicked = true;
  }
  else if (_isHovered && _isClicked && mouseClicked) state = ButtonState::Clicking;
  else if (_isHovered && _isClicked && !mouseClicked) {
    state = ButtonState::Just_Released;
    _isClicked = false;
  }
  else if (_isHovered) state = ButtonState::Hover;
  else state = ButtonState::None;
}

void Button::render() {
  // switch button color based on state
  Color bgColor;
  switch (state) {
    case ButtonState::Hover:
    case ButtonState::Just_Released:
      bgColor = cbgHover;
      break;
    case ButtonState::Just_Clicked:
    case ButtonState::Clicking:
      bgColor = cbgClick;
      break;
    case ButtonState::None:
    default:
      bgColor = cbgNone;
      break;
  }
  
  // define button size/position
  Rectangle rect = {pos.x, pos.y, size.x, size.y};
  Rectangle rectShadow = {pos.x + 2.0f, pos.y, size.x + 2.0f, size.y + 5.0f};

  // render to screen
  DrawRectangleRounded(rectShadow, 0.5, 8, cShadow);
  DrawRectangleRounded(rect, 0.5, 8, bgColor);

  // draw text
  DrawText("Button", pos.x + 14.0f, pos.y + 10.0f, 22, cText);
}