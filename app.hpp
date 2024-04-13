#include <iostream>
#include <vector>
#include <raylib.h>

namespace App {
  class EventLoop {
    public:
      // global states
      Font font;
      int screenW = 0;
      int screenH = 0;
      Vector2 screenCenter = { 0.0, 0.0 };
      int fps = 0;
      double elapsed = 0.0;
      Vector2 mousePos = { 0.0, 0.0 };
      // methods
      void update();
      void render();
    private:
      void _updateSystem();
      void _drawFps();
  };
}