#include <vector>
#include <math.h>
#include <raylib.h>

namespace App {

  class Box {
    public:
      Box(int iid, Vector2 ipos, Vector2 isize, Color icolor);
      Box(int iid, Vector2 ipos, Vector2 isize, Color icolor, float irot);
      int id;
      Vector2 position;
      Vector2 size;
      Rectangle body;
      float rotation = 0.0f;
      Color color;
      void update(Vector2 pos, float rot);
      void updateTexture();
      void render();
      void renderNormal();
      void cleanup();
    private:
      Shader shader;
      RenderTexture2D target;
  };

  class Light {
    public:
      Light(int iid, Vector2 ipos, float iradius, Color icolor, float iintensity);
      int id;
      Vector2 position;
      Color color;
      float intensity = 1.0f;
      float radius;
      void update(Vector2 pos);
      void updateShader(int screenW, int screenH);
      void render();
      void cleanup();
      Shader shader;
      int shaderLoc[5];
      RenderTexture2D lightBuffer;
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
      std::vector<Box> boxes;
      std::vector<Light> lights;
      RenderTexture2D gBufferColor;
      RenderTexture2D gBufferNormal;
      // methods
      void init();
      void update();
      void render();
      void cleanup();
    private:
      void _updateSystem();
      void _drawFps();
      void _drawDebug();
  };
}