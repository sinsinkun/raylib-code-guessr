#include <vector>
#include <raylib.h>
#include "button.hpp"

namespace App {
  enum AssetType {
    ANone,
    AButton,
    ATexture,
  };
  struct Asset {
    AssetType type = AssetType::ANone;
    Button* btn;
  };

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
      // memory
      std::vector<Asset> assets;
      // methods
      void init();
      void update();
      void render();
      void cleanup();
    private:
      void _updateSystem();
      void _drawFps();
  };
}