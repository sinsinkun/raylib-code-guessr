#include <vector>
#include <raylib.h>
#include "button.hpp"
#include "answer.hpp"

namespace App {
  enum AssetType {
    ANone,
    AButton,
    AAnsBox,
  };
  struct Asset {
    AssetType type = AssetType::ANone;
    Button* btn;
    AnswerBox* ansBox;
  };

  class EventLoop {
    public:
      // global states
      Font font;
      int screenW = 0;
      int screenH = 0;
      Vector2 screenCenter = { 0.0, 0.0 };
      int fps = 0;
      float deltaTime = 0.0f;
      double elapsed = 0.0;
      Vector2 mousePos = { 0.0, 0.0 };
      // memory
      int score = 0;
      int inputc = 0;
      int input[4] = {0, 0, 0, 0};
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