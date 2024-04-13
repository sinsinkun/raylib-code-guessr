#pragma once
#include <raylib.h>

namespace App {
  enum ButtonState {
    None,
    Hover,
    Just_Clicked,
    Clicking,
    Just_Released
  };

  class Button {
    public:
      // constructors
      Button(int iid) {
        id = iid;
      };
      Button(int iid, float posx, float posy) {
        id = iid;
        pos = (Vector2){ posx, posy };
      }
      Button(int iid, float posx, float posy, float sizex, float sizey) {
        id = iid;
        pos = (Vector2){ posx, posy };
        size = (Vector2){ sizex, sizey };
      }
      // state
      int id = 0;
      Vector2 size = {100.0, 40.0};
      Vector2 pos = {0.0, 0.0};
      ButtonState state = ButtonState::None;
      bool drawShadow = true;
      Color cbgNone = {200, 200, 200, 255};
      Color cbgHover = {190, 190, 220, 255};
      Color cbgClick = {160, 160, 220, 255};
      Color cShadow = {0, 0, 0, 255};
      Color cText = {0, 0, 0, 255};
      // methods
      void update(Vector2 mousePos, bool mouseClicked, int& mouseHoverCount);
      void render();
    private:
      // helper states
      bool _isHovered = false;
      bool _isClicked = false;
  };
}